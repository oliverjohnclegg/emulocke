#include "application/Application.hpp"

#include "adapter/GameAdapter.hpp"
#include "emu/FileBytes.hpp"
#include "emu/GbaSession.hpp"
#include "emu/NdsSession.hpp"
#include "run/SavePeek.hpp"
#include "ui/MediaFetch.hpp"
#include "ui/PngCache.hpp"

#include <SDL3/SDL.h>
#include <cctype>
#include <cstdio>
#include <filesystem>

namespace emulocke {
namespace {

std::string lowerExt(const std::string& path) {
    std::string ext = std::filesystem::path(path).extension().string();
    for (char& c : ext) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return ext;
}

}  // namespace

void Application::startEmuThread() {
    if (emuThread_.joinable()) {
        return;
    }
    running_ = true;
    emuThread_ = std::thread([this] { emuLoop(); });
}

void Application::stopEmuThread() {
    running_ = false;
    if (emuThread_.joinable()) {
        emuThread_.join();
    }
}

void Application::emuLoop() {
    bool wasFast = false;
    while (running_) {
        const Uint64 start = SDL_GetTicksNS();
        const bool fast = speedUpOn_.load();
        const int mul = speedUp_.load();
        const int frames = (fast && mul > 1) ? mul : 1;
        if (fast && !wasFast) {
            audio_.clear();
        }
        wasFast = fast;
        audio_.setDropping(frames > 1);
        int queuedAfter = 0;
        bool ran = false;
        for (int i = 0; i < frames && running_; ++i) {
            std::lock_guard lock(sessionMutex_);
            if (!session_ || paused_) {
                break;
            }
            ran = true;
            session_->setButtons(buttons_);
            session_->setTouch(touchDown_, touchX_, touchY_);
            session_->runFrame();
            session_->drainAudio(audio_);
            queuedAfter = audio_.queuedBytes();
            if (adapter_ && session_->liveMemory()) {
                snapshot_ = adapter_->readLive(*session_->liveMemory());
                if ((!snapshot_.ok || snapshot_.party.count == 0) && !activeRunId_.empty()) {
                    const auto sav = readWholeFile(runStore_->batteryPath(activeRunId_).string());
                    if (!sav.empty()) {
                        snapshot_ = adapter_->readSave(sav);
                    }
                }
            }
        }
        if (ran) {
            const Uint64 origin = playOriginNs_.exchange(start);
            if (origin != 0) {
                pendingPlayNs_.fetch_add(start - origin);
            }
        } else {
            playOriginNs_.store(0);
        }
        const Uint64 frameNs = 16742706;
        const int cushion = 48000 * 4 / 15;
        const bool filling = queuedAfter > 0 && queuedAfter < cushion;
        const Uint64 elapsed = SDL_GetTicksNS() - start;
        if (!filling && elapsed < frameNs) {
            SDL_DelayNS(frameNs - elapsed);
        }
    }
}

void Application::bootRun(const Run& run) {
    stopEmuThread();
    harvestPlayOrigin();
    commitPlay();
    auto rom = romLibrary_->ensurePlayable(run.catalogUuid, run.patchOption);
    std::unique_ptr<EmuSession> next;
    if (rom) {
        const std::string ext = lowerExt(rom->string());
        const std::string save = runStore_->batteryPath(run.id).string();
        if (ext == ".gba") {
            next = GbaSession::open(rom->string(), save);
            status_ = next ? "Cart seated." : "Couldn't open that game.";
        } else if (ext == ".nds") {
            next = NdsSession::open(rom->string(), save);
            status_ = next ? "Cart seated." : "Couldn't open that game.";
        } else {
            status_ = "Need a Pokemon game (.gba or .nds).";
        }
    } else {
        status_ = romLibrary_->lastError();
    }
    {
        std::lock_guard lock(sessionMutex_);
        session_ = std::move(next);
        adapter_ = nullptr;
        snapshot_ = GameSnapshot{};
        paused_ = false;
        speedUpOn_ = false;
        if (session_ && session_->cartridge()) {
            adapter_ = adapterFor(*session_->cartridge());
        }
    }
    if (session_) {
        startEmuThread();
    }
    std::fprintf(stderr, "%s\n", status_.c_str());
}

void Application::closeRun() {
    stopEmuThread();
    harvestPlayOrigin();
    commitPlay();
    {
        std::lock_guard lock(sessionMutex_);
        session_.reset();
        adapter_ = nullptr;
        snapshot_ = GameSnapshot{};
        speedUpOn_ = false;
        activeRunId_.clear();
        lastPlayCommitNs_ = 0;
        status_ = "No cart.";
    }
    syncWindowTitle();
}

bool Application::copySnapshot(GameSnapshot& out) const {
    std::lock_guard lock(sessionMutex_);
    if (!snapshot_.ok) {
        return false;
    }
    out = snapshot_;
    return true;
}

void Application::resetSession() {
    std::lock_guard lock(sessionMutex_);
    if (session_) {
        session_->reset();
    }
}

void Application::shutdown() {
    stopEmuThread();
    harvestPlayOrigin();
    commitPlay();
    persistPrefs();
    session_.reset();
    if (gameArt_) {
        gameArt_->destroy();
        gameArt_.reset();
    }
    pngs_.reset();
    media_.reset();
    savePeek_.reset();
    audio_.close();
    host_.destroy();
    SDL_Quit();
}

}