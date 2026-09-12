#include "application/Application.hpp"

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
        {
            std::lock_guard lock(sessionMutex_);
            if (session_ && !paused_) {
                session_->setButtons(buttons_);
                session_->setTouch(touchDown_, touchX_, touchY_);
                session_->runFrame();
                session_->drainAudio(audio_);
            }
        }
        const Uint64 elapsed = SDL_GetTicksNS() - start;
        const Uint64 frameNs = 16742706;
        if (elapsed < frameNs) {
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
        status_ = next ? "GBA cart seated." : "Failed to load GBA ROM.";
    } else if (ext == ".nds") {
        next = NdsSession::open(path);
        status_ = next ? "DS cart seated." : "Failed to load NDS ROM.";
    } else {
        status_ = "Need a .gba or .nds file.";
    }
    {
        std::lock_guard lock(sessionMutex_);
        session_ = std::move(next);
        paused_ = false;
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
    status_ = "No cart.";
}

void Application::resetSession() {
    std::lock_guard lock(sessionMutex_);
    if (session_) {
        session_->reset();
    }
}

void Application::shutdown() {
    stopEmuThread();
    session_.reset();
    audio_.close();
    host_.destroy();
    SDL_Quit();
}

}