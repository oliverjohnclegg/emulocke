#include "application/Application.hpp"

#include "adapter/GameAdapter.hpp"
#include "emu/GbaSession.hpp"
#include "emu/NdsSession.hpp"

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
        bool played = false;
        for (int i = 0; i < frames && running_; ++i) {
            std::lock_guard lock(sessionMutex_);
            if (!session_ || paused_) {
                playOriginNs_.store(0);
                break;
            }
            if (!played) {
                const Uint64 origin = playOriginNs_.load();
                if (origin != 0) {
                    pendingPlayNs_.fetch_add(start - origin);
                }
                playOriginNs_.store(start);
                played = true;
            }
            session_->setButtons(buttons_);
            session_->setTouch(touchDown_, touchX_, touchY_);
            session_->runFrame();
            session_->drainAudio(audio_);
            queuedAfter = audio_.queuedBytes();
            if (adapter_ && session_->liveMemory()) {
                snapshot_ = adapter_->readLive(*session_->liveMemory());
            }
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
    auto rom = romLibrary_->ensurePlayable(run.catalogUuid);
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
        uiSnap_ = {};
        uiSnapOk_ = false;
        uiAdapter_ = nullptr;
        paused_ = false;
        speedUpOn_ = false;
        if (session_ && session_->cartridge()) {
            adapter_ = adapterFor(*session_->cartridge());
            uiAdapter_ = adapter_;
        }
    }
    if (session_) {
        startEmuThread();
    }
    std::fprintf(stderr, "%s\n", status_.c_str());
}

void Application::closeRun() {
    persistTracker();
    stopEmuThread();
    harvestPlayOrigin();
    commitPlay();
    std::lock_guard lock(sessionMutex_);
    session_.reset();
    adapter_ = nullptr;
    snapshot_ = GameSnapshot{};
    uiSnap_ = {};
    uiSnapOk_ = false;
    uiAdapter_ = nullptr;
    speedUpOn_ = false;
    activeRunId_.clear();
    trackerLog_ = {};
    lastPlayCommitNs_ = 0;
    status_ = "No cart.";
    if (previewTracker_) {
        seedPreviewTracker();
    }
}

bool Application::copySnapshot(GameSnapshot& out) const {
    std::unique_lock lock(sessionMutex_, std::try_to_lock);
    if (lock.owns_lock()) {
        if (!snapshot_.ok) {
            uiSnapOk_ = false;
            return false;
        }
        uiSnap_ = snapshot_;
        uiAdapter_ = adapter_;
        uiSnapOk_ = true;
        out = uiSnap_;
        return true;
    }
    if (uiSnapOk_) {
        out = uiSnap_;
        return true;
    }
    return false;
}

void Application::resetSession() {
    std::lock_guard lock(sessionMutex_);
    if (session_) {
        session_->reset();
    }
}

void Application::shutdown() {
    destroyTracker();
    stopEmuThread();
    harvestPlayOrigin();
    commitPlay();
    persistPrefs();
    session_.reset();
    audio_.close();
    host_.destroy();
    SDL_Quit();
}

}