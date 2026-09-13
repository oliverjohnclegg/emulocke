#pragma once

#include "adapter/Snapshot.hpp"
#include "adapter/Species.hpp"
#include "application/Host.hpp"
#include "emu/AudioOutput.hpp"
#include "emu/EmuSession.hpp"
#include "emu/Input.hpp"
#include "emu/ScreenTexture.hpp"
#include "run/RomLibrary.hpp"
#include "run/Run.hpp"
#include "run/RunStore.hpp"
#include "run/TitlePlay.hpp"
#include "tracker/Log.hpp"
#include "ui/GameArtGpu.hpp"

#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

struct ImFont;

namespace emulocke {

class BoxSprites;
class GameAdapter;
class MediaFetch;
class PngCache;
class SavePeek;
class SpriteCache;
struct TrackerAtlas;

class Application {
public:
    Application();
    ~Application();
    bool start(int argc, char** argv);
    void run();
    void shutdown();
    void requestNewRun();
    void dismissNewRun();
    void confirmNewRun();
    void requestImportGame();
    void requestImportFor(std::string uuid);
    void queueImport(std::string path);
    void queueLoadRun(std::string id);
    void queueNewAttempt(std::string sourceId);
    void closeRun();
    void pauseToggle();
    void resetSession();
    void setTouch(bool down, uint16_t x, uint16_t y);
    void persistPrefs();
    void setFullscreen(bool on);
    void setRightPane(bool on);
    void setScreenScale(int scale);
    void setMuted(bool mute);
    void setVolume(int volume);
    void setSpeedUp(int speed);
    void setSpeedUpHold(bool hold);
    void setBottomScreen(bool on);
    void restoreDefaultWindow();
    bool paused() const { return paused_; }
    int screenScale() const { return prefs_.scale; }
    const Prefs& prefs() const { return prefs_; }
    EmuSession* session() const { return session_.get(); }
    SDL_Renderer* renderer() const { return host_.renderer(); }
    ScreenTexture& screen(int i) { return screens_[i]; }
    ImFont* displayFont() const { return displayFont_; }
    ImFont* bodyFont() const { return bodyFont_; }
    GameArtGpu& gameArt() { return *gameArt_; }
    const std::string& status() const { return status_; }
    bool copySnapshot(GameSnapshot& out) const;
    bool showNewRun() const { return showNewRun_; }
    NewRunDraft& newRunDraft() { return newRunDraft_; }
    RomLibrary& romLibrary() { return *romLibrary_; }
    const RomLibrary& romLibrary() const { return *romLibrary_; }
    RunStore& runStore() { return *runStore_; }
    const RunStore& runStore() const { return *runStore_; }
    const std::string& activeRunId() const { return activeRunId_; }
    const GameAdapter* adapter() const;
    SpeciesRef species(uint16_t id) const;
    const TrackerAtlas* trackerAtlas() const;
    TrackerLog& trackerLog() { return trackerLog_; }
    BoxSprites* boxSprites() { return boxSprites_.get(); }
    bool previewTracker() const { return previewTracker_; }
    void syncTracker(const GameSnapshot& snap);
    void persistTracker();
    void noteLoadingPainted();
    bool showLoadingRun() const { return showLoadingRun_; }
    MediaFetch& media() { return *media_; }
    PngCache& pngs() { return *pngs_; }
    SavePeek& savePeek() { return *savePeek_; }

private:
    void startEmuThread();
    void stopEmuThread();
    void emuLoop();
    void pollSpeedUp(const bool* keys);
    void applyPendingHost();
    void drainPending();
    void importPath(const std::string& path);
    void showDumpPicker();
    void createRunFromDraft();
    void startNewAttempt(const std::string& sourceId);
    void loadRun(const std::string& id);
    void bootRun(const Run& run);
    void harvestPlayOrigin();
    void commitPlay();
    void syncWindowTitle();
    void initTracker();
    void loadTrackerLog();
    void destroyTracker();
    void seedPreviewTracker();
    enum class PendingHost { None, RestoreDefault, FullscreenOn, FullscreenOff };
    Host host_;
    PendingHost pendingHost_{PendingHost::None};
    Input input_;
    AudioOutput audio_;
    Prefs prefs_;
    ScreenTexture screens_[2];
    std::unique_ptr<EmuSession> session_;
    std::unique_ptr<RomLibrary> romLibrary_;
    std::unique_ptr<RunStore> runStore_;
    std::unique_ptr<GameArtGpu> gameArt_;
    std::unique_ptr<MediaFetch> media_;
    std::unique_ptr<PngCache> pngs_;
    std::unique_ptr<SavePeek> savePeek_;
    std::unique_ptr<TitlePlay> titlePlay_;
    const GameAdapter* adapter_{};
    GameSnapshot snapshot_{};
    mutable std::mutex sessionMutex_;
    std::thread emuThread_;
    std::atomic<bool> running_{false};
    std::atomic<bool> paused_{false};
    std::atomic<int> speedUp_{3};
    std::atomic<bool> speedUpHold_{true};
    std::atomic<bool> speedUpOn_{false};
    bool tabWasDown_{false};
    ImFont* displayFont_{};
    ImFont* bodyFont_{};
    std::string pendingImport_;
    std::string importKeepUuid_;
    std::string status_;
    std::string activeRunId_;
    std::string pendingLoadId_;
    std::string pendingAttemptId_;
    NewRunDraft newRunDraft_;
    std::atomic<uint64_t> pendingPlayNs_{0};
    std::atomic<uint64_t> playOriginNs_{0};
    uint64_t lastPlayCommitNs_{0};
    bool showNewRun_{false};
    bool showLoadingRun_{false};
    bool loadingPainted_{false};
    bool previewTracker_{false};
    mutable GameSnapshot uiSnap_{};
    mutable bool uiSnapOk_{false};
    mutable const GameAdapter* uiAdapter_{};
    bool pendingNewRun_{false};
    bool pendingCreate_{false};
    bool pendingDumpPicker_{false};
    std::atomic<uint32_t> buttons_{0};
    std::atomic<bool> touchDown_{false};
    std::atomic<uint16_t> touchX_{0};
    std::atomic<uint16_t> touchY_{0};
    std::vector<uint8_t> uploadScratch_;
    std::unique_ptr<SpriteCache> spriteCache_;
    std::unique_ptr<BoxSprites> boxSprites_;
    TrackerLog trackerLog_;
};

}
