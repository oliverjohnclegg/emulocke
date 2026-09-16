#include "application/Application.hpp"

#include "adapter/GameAdapter.hpp"
#include "adapter/frlg/FrlgNames.hpp"
#include "adapter/gen45/Names.hpp"
#include "application/PreviewSuite.hpp"
#include "emu/Paths.hpp"
#include "poke/Sprites.hpp"
#include "run/Catalog.hpp"
#include "run/RunMeta.hpp"
#include "tracker/Atlas.hpp"
#include "tracker/Difficulty.hpp"
#include "tracker/frlg/Frlg.hpp"
#include "tracker/Log.hpp"
#include "ui/BoxSprites.hpp"
#include "ui/MediaFetch.hpp"
#include "ui/PngCache.hpp"
#include "run/SavePeek.hpp"

#include <cstring>
#include <string_view>

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
        const SpeciesRef ref = live->species(id);
        if (ref.slug && ref.slug[0] && std::strcmp(ref.slug, "???") != 0) {
            return ref;
        }
    }
    if (previewTracker_) {
        return frlgSpeciesRef(id);
    }
    if (const TrackerAtlas* atlas = trackerAtlas()) {
        const uint16_t mapped = trackerSpeciesId(atlas->id, id);
        if (mapped != id) {
            return nationalSpeciesRef(mapped);
        }
    }
    return nationalSpeciesRef(id);
}

const TrackerAtlas* Application::trackerAtlas() const {
    if (!activeRunId_.empty() && runStore_) {
        const Run* run = runStore_->find(activeRunId_);
        if (run) {
            return emulocke::trackerAtlas(run->catalogUuid, run->difficulty, run->patchOption);
        }
    }
    if (previewTracker_) {
        return &frlgAtlas();
    }
    return nullptr;
}

void Application::seedPreviewTracker() {
    seedPreviewSuite(trackerLog_, snapshot_);
    kitFocus_.tab = KitTab::Tracker;
    kitFocus_.pendingTab = 1;
}

void Application::syncTracker(const GameSnapshot& snap) {
    if (!snap.ok) {
        return;
    }
    if (!activeRunId_.empty() && runStore_) {
        Run* run = runStore_->find(activeRunId_);
        if (run && snap.progress.difficulty[0] &&
            (run->catalogUuid == kRadicalRedUuid || run->catalogUuid == kUnboundUuid)) {
            const CatalogTitle* title = catalogByUuid(run->catalogUuid);
            const std::string_view slug = title ? title->slug : "";
            const std::string_view cart = snap.progress.difficulty;
            if (run->difficulty.empty() ||
                atlasDifficultyKey(slug, cart) != atlasDifficultyKey(slug, run->difficulty)) {
                run->difficulty = cart;
                writeRunMeta(runStore_->dir(activeRunId_), *run);
            }
        }
    }
    const TrackerAtlas* atlas = trackerAtlas();
    if (!atlas) {
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