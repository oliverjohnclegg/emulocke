#include "application/Application.hpp"

#include "adapter/GameAdapter.hpp"
#include "adapter/frlg/FrlgNames.hpp"
#include "emu/Paths.hpp"
#include "poke/Sprites.hpp"
#include "tracker/Atlas.hpp"
#include "tracker/frlg/Frlg.hpp"
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

SpeciesRef Application::species(uint16_t id) const {
    if (const GameAdapter* live = adapter()) {
        return live->species(id);
    }
    if (previewTracker_) {
        return frlgSpeciesRef(id);
    }
    return {};
}

const TrackerAtlas* Application::trackerAtlas() const {
    if (!activeRunId_.empty() && runStore_) {
        const Run* run = runStore_->find(activeRunId_);
        if (run) {
            return emulocke::trackerAtlas(run->catalogUuid, run->difficulty);
        }
    }
    if (previewTracker_) {
        return &frlgAtlas();
    }
    return nullptr;
}

void Application::seedPreviewTracker() {
    trackerLog_ = {};
    trackerLog_.setCaught("starter", 1, 1);
    trackerLog_.setCaught("route-1", 16, 1);
    trackerLog_.setCaught("route-2", 25, 1);
    trackerLog_.setCaught("viridian-forest", 10, 1);
    trackerLog_.setStatus("viridian-forest", EncounterStatus::Dead);
    trackerLog_.setCaught("route-3", 19, 1);
    trackerLog_.setCaught("mt-moon", 41, 1);
    trackerLog_.setCaught("route-4", 129, 1);
    trackerLog_.setStatus("route-4", EncounterStatus::Missed);
    trackerLog_.setCaught("digletts-cave", 50, 1);
    trackerLog_.setCaught("celadon-city", 122, 1);
    trackerLog_.setStatus("celadon-city", EncounterStatus::Traded);
    trackerLog_.setCaught("power-plant", 145, 1);
    trackerLog_.setDefeated("rival-1", true);
    trackerLog_.setDefeated("brock", true);
    trackerLog_.setDefeated("misty", true);
    trackerLog_.clearDirty();
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
