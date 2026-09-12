#pragma once

#include "adapter/Snapshot.hpp"
#include "emu/EmuSession.hpp"
#include "emu/Input.hpp"
#include "emu/AudioOutput.hpp"
#include "emu/ScreenTexture.hpp"

#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

struct SDL_Window;
struct SDL_Renderer;
struct ImFont;

namespace emulocke {

class GameAdapter;

class Host {
public:
    bool create();
    void destroy();
    SDL_Window* window() const { return window_; }
    SDL_Renderer* renderer() const { return renderer_; }

private:
    SDL_Window* window_{};
    SDL_Renderer* renderer_{};
};

class Application {
public:
    bool start(int argc, char** argv);
    void run();
    void shutdown();
    void requestOpenRom();
    void queueRom(std::string path);
    void loadRom(const std::string& path);
    void pauseToggle();
    void resetSession();
    void closeRom();
    void setTouch(bool down, uint16_t x, uint16_t y);
    bool paused() const { return paused_; }
    EmuSession* session() const { return session_.get(); }
    SDL_Renderer* renderer() const { return host_.renderer(); }
    ScreenTexture& screen(int i) { return screens_[i]; }
    ImFont* displayFont() const { return displayFont_; }
    ImFont* bodyFont() const { return bodyFont_; }
    const std::string& status() const { return status_; }
    bool copySnapshot(GameSnapshot& out) const;

private:
    void startEmuThread();
    void stopEmuThread();
    void emuLoop();
    Host host_;
    Input input_;
    AudioOutput audio_;
    ScreenTexture screens_[2];
    std::unique_ptr<EmuSession> session_;
    const GameAdapter* adapter_{};
    GameSnapshot snapshot_{};
    mutable std::mutex sessionMutex_;
    std::thread emuThread_;
    std::atomic<bool> running_{false};
    std::atomic<bool> paused_{false};
    ImFont* displayFont_{};
    ImFont* bodyFont_{};
    std::string pendingRom_;
    std::string status_;
    std::atomic<uint32_t> buttons_{0};
    std::atomic<bool> touchDown_{false};
    std::atomic<uint16_t> touchX_{0};
    std::atomic<uint16_t> touchY_{0};
    std::vector<uint8_t> uploadScratch_;
};

}