#include "application/Application.hpp"

#include "adapter/GameAdapter.hpp"
#include "emu/Paths.hpp"
#include "poke/Sprites.hpp"
#include "tracker/Atlas.hpp"
#include "tracker/Log.hpp"
#include "ui/BoxSprites.hpp"

namespace emulocke {

Application::Application() = default;
Application::~Application() = default;

void Application::initTracker() {
    spriteCache_ = std::make_unique<SpriteCache>(prefDir() / "sprites", assetsDir() / "sprites");
    boxSprites_ = std::make_unique<BoxSprites>(host_.renderer(), *spriteCache_,
                                               assetsDir() / "sprites" / "missing-box.png");
}

const GameAdapter* Application::adapter() const {
    std::unique_lock lock(sessionMutex_, std::try_to_lock);
    if (lock.owns_lock()) {
        uiAdapter_ = adapter_;
        return adapter_;
    }
    return uiAdapter_;
}

const TrackerAtlas* Application::trackerAtlas() const {
    if (activeRunId_.empty() || !runStore_) {
        return nullptr;
    }
    const Run* run = runStore_->find(activeRunId_);
    if (!run) {
        return nullptr;
    }
    return emulocke::trackerAtlas(run->catalogUuid, run->difficulty);
}

void Application::syncTracker(const GameSnapshot& snap) {
    const TrackerAtlas* atlas = trackerAtlas();
    if (!atlas || !snap.ok) {
        return;
    }
    applyTrackerFill(trackerLog_, *atlas, snap);
}

void Application::noteLoadingPainted() {
    loadingPainted_ = true;
}

void Application::persistTracker() {
    if (activeRunId_.empty() || !runStore_) {
        return;
    }
    if (trackerLog_.save(runStore_->dir(activeRunId_) / "tracker.ini")) {
        trackerLog_.clearDirty();
    }
}

void Application::destroyTracker() {
    persistTracker();
    boxSprites_.reset();
    spriteCache_.reset();
}

void Application::loadTrackerLog() {
    trackerLog_ = {};
    if (activeRunId_.empty() || !runStore_) {
        return;
    }
    trackerLog_.load(runStore_->dir(activeRunId_) / "tracker.ini");
}

}
