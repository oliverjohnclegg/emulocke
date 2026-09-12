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
    while (running_) {
        const Uint64 start = SDL_GetTicksNS();
        int queuedAfter = 0;
        {
            std::lock_guard lock(sessionMutex_);
            if (session_ && !paused_) {
                session_->setButtons(buttons_);
                session_->setTouch(touchDown_, touchX_, touchY_);
                session_->runFrame();
                session_->drainAudio(audio_);
                queuedAfter = audio_.queuedBytes();
                if (adapter_ && session_->liveMemory()) {
                    snapshot_ = adapter_->readLive(*session_->liveMemory());
                }
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

void Application::loadRom(const std::string& path) {
    stopEmuThread();
    std::unique_ptr<EmuSession> next;
    const std::string ext = lowerExt(path);
    if (ext == ".gba") {
        next = GbaSession::open(path);
        status_ = next ? "Cart seated." : "Couldn't open that game.";
    } else if (ext == ".nds") {
        next = NdsSession::open(path);
        status_ = next ? "Cart seated." : "Couldn't open that game.";
    } else {
        status_ = "Need a Pokemon game (.gba or .nds).";
    }
    {
        std::lock_guard lock(sessionMutex_);
        session_ = std::move(next);
        adapter_ = nullptr;
        snapshot_ = GameSnapshot{};
        paused_ = false;
        if (session_ && session_->cartridge()) {
            adapter_ = adapterFor(*session_->cartridge());
        }
    }
    if (session_) {
        startEmuThread();
    }
    std::fprintf(stderr, "%s\n", status_.c_str());
}

void Application::closeRom() {
    stopEmuThread();
    std::lock_guard lock(sessionMutex_);
    session_.reset();
    adapter_ = nullptr;
    snapshot_ = GameSnapshot{};
    status_ = "No cart.";
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
    persistPrefs();
    stopEmuThread();
    session_.reset();
    audio_.close();
    host_.destroy();
    SDL_Quit();
}

}