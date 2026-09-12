#pragma once

#include "adapter/Snapshot.hpp"
#include "application/Prefs.hpp"
#include "emu/AudioOutput.hpp"
#include "emu/EmuSession.hpp"
#include "emu/Input.hpp"
#include "emu/ScreenTexture.hpp"
#include "run/Roms.hpp"
#include "run/Run.hpp"
#include "run/RunStore.hpp"

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
    bool create(const Prefs& prefs);
    void destroy();
    SDL_Window* window() const { return window_; }
    SDL_Renderer* renderer() const { return renderer_; }
    void setFullscreen(bool on);
    bool fullscreen() const;
    void restoreDefaultSize();
    void captureWindowed(Prefs& prefs) const;

private:
    SDL_Window* window_{};
    SDL_Renderer* renderer_{};
};

class Application {
public:
    bool start(int argc, char** argv);
    void run();
    void shutdown();
    void requestNewRun();
    void dismissNewRun();
    void confirmNewRun();
    void requestLoadRun();
    void dismissLoadRun();
    void queueLoadRun(std::string id);
    void queueNewAttempt(std::string sourceId);
    void closeRun();
    void pauseToggle();
    void resetSession();
    void setTouch(bool down, uint16_t x, uint16_t y);
    void persistPrefs();
    void setFullscreen(bool on);
    void setScreenScale(int scale);
    void setMuted(bool mute);
    void setVolume(int volume);
    void restoreDefaultWindow();
    bool paused() const { return paused_; }
    int screenScale() const { return prefs_.scale; }
    const Prefs& prefs() const { return prefs_; }
    EmuSession* session() const { return session_.get(); }
    SDL_Renderer* renderer() const { return host_.renderer(); }
    ScreenTexture& screen(int i) { return screens_[i]; }
    ImFont* displayFont() const { return displayFont_; }
    ImFont* bodyFont() const { return bodyFont_; }
    const std::string& status() const { return status_; }
    const std::string& romsHint() const { return romsHint_; }
    bool showNewRun() const { return showNewRun_; }
    bool showLoadRun() const { return showLoadRun_; }
    NewRunDraft& newRunDraft() { return newRunDraft_; }
    const std::vector<DetectedGame>& detectedGames() const { return detectedGames_; }
    RunStore& runStore() { return *runStore_; }
    const RunStore& runStore() const { return *runStore_; }
    const std::string& activeRunId() const { return activeRunId_; }
    bool copySnapshot(GameSnapshot& out) const;

private:
    void startEmuThread();
    void stopEmuThread();
    void emuLoop();
    void scanRoms();
    void drainPending();
    void createRunFromDraft();
    void startNewAttempt(const std::string& sourceId);
    void loadRun(const std::string& id);
    void bootRun(const Run& run);
    void applyPendingHost();
    enum class PendingHost { None, RestoreDefault, FullscreenOn, FullscreenOff };
    Host host_;
    PendingHost pendingHost_{PendingHost::None};
    Input input_;
    AudioOutput audio_;
    Prefs prefs_;
    ScreenTexture screens_[2];
    std::unique_ptr<EmuSession> session_;
    std::unique_ptr<RunStore> runStore_;
    const GameAdapter* adapter_{};
    GameSnapshot snapshot_{};
    mutable std::mutex sessionMutex_;
    std::thread emuThread_;
    std::atomic<bool> running_{false};
    std::atomic<bool> paused_{false};
    ImFont* displayFont_{};
    ImFont* bodyFont_{};
    std::string status_;
    std::string romsHint_;
    std::string activeRunId_;
    std::string pendingLoadId_;
    std::string pendingAttemptId_;
    std::vector<DetectedGame> detectedGames_;
    NewRunDraft newRunDraft_;
    bool showNewRun_{false};
    bool showLoadRun_{false};
    bool pendingCreate_{false};
    std::atomic<uint32_t> buttons_{0};
    std::atomic<bool> touchDown_{false};
    std::atomic<uint16_t> touchX_{0};
    std::atomic<uint16_t> touchY_{0};
    std::vector<uint8_t> uploadScratch_;
};

}
