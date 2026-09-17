#include "application/Application.hpp"

#include "adapter/GameAdapter.hpp"
#include "adapter/frlg/FrlgNames.hpp"
#include "adapter/gen45/Names.hpp"
#include "application/PreviewSuite.hpp"
#include "calc/Pack.hpp"
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
namespace {

bool cartDifficultyTitle(std::string_view uuid) {
    return uuid == kRadicalRedUuid || uuid == kUnboundUuid || uuid == kInclementEmeraldUuid ||
        uuid == kVoltWhite2ReduxUuid;
}

const TrackerAtlas* atlasIfPacked(std::string_view uuid, std::string_view difficulty, std::string_view patch) {
    const TrackerAtlas* atlas = trackerAtlas(uuid, difficulty, patch);
    if (!atlas || !calcPack(uuid, difficulty)) {
        return nullptr;
    }
    return atlas;
}

}  // namespace

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
    if (!activeRunId_.empty() && runStore_) {
        if (const Run* run = runStore_->find(activeRunId_)) {
            if (const CatalogTitle* title = catalogByUuid(run->catalogUuid)) {
                if (title->kind == TitleKind::Hack) {
                    const SpeciesRef nat = nationalSpeciesRef(id);
                    if (nat.slug && nat.slug[0] && std::strcmp(nat.slug, "???") != 0) {
                        return nat;
                    }
                }
            }
        }
    }
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
            if (const TrackerAtlas* atlas =
                    atlasIfPacked(run->catalogUuid, run->difficulty, run->patchOption)) {
                return atlas;
            }
        }
    }
    if (previewTracker_) {
        return atlasIfPacked(kFireRedUs10Uuid, {}, {});
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
    Run* run = nullptr;
    if (!activeRunId_.empty() && runStore_) {
        run = runStore_->find(activeRunId_);
        if (run && snap.progress.difficulty[0] && cartDifficultyTitle(run->catalogUuid)) {
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
    if (!run || run->rules.faintIsDeath) {
        applyFaintDeath(trackerLog_, snap);
    }
    for (const auto& [id, row] : trackerLog_.caughtRows()) {
        if (row.species == 0 || !row.slug.empty()) {
            continue;
        }
        const SpeciesRef ref = species(row.species);
        if (ref.slug && ref.slug[0]) {
            trackerLog_.setCaught(id, row.species, row.personality, ref.slug);
        }
    }
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