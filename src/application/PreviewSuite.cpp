#include "application/PreviewSuite.hpp"

#include "application/PreviewMons.hpp"

#include <cstdio>

namespace emulocke {
namespace {

struct CatchRow {
    const char* id;
    uint16_t species;
    uint32_t pid;
    EncounterStatus status;
};

}  // namespace

void seedPreviewSuite(TrackerLog& log, GameSnapshot& snap) {
    log = {};
    constexpr CatchRow kCatches[] = {
        {"starter", 1, 0x1001, EncounterStatus::Captured},
        {"route-1", 16, 0x1002, EncounterStatus::Captured},
        {"route-2", 25, 0x1003, EncounterStatus::Captured},
        {"viridian-forest", 10, 0x1004, EncounterStatus::Dead},
        {"route-3", 19, 0x1005, EncounterStatus::Captured},
        {"mt-moon", 41, 0x1006, EncounterStatus::Captured},
        {"route-4", 129, 0x1007, EncounterStatus::Missed},
        {"digletts-cave", 50, 0x1008, EncounterStatus::Captured},
        {"celadon-city", 122, 0x1009, EncounterStatus::Traded},
        {"power-plant", 145, 0x100A, EncounterStatus::Captured},
    };
    for (const CatchRow& row : kCatches) {
        log.setCaught(row.id, row.species, row.pid);
        if (row.status != EncounterStatus::Captured) {
            log.setStatus(row.id, row.status);
        }
    }
    log.setDefeated("rival-1", true);
    log.setDefeated("brock", true);
    log.setDefeated("misty", true);
    log.clearDirty();

    snap = {};
    snap.ok = true;
    snap.adapterId = "firered-us-1.0";
    snap.origin = SnapshotOrigin::Save;
    std::snprintf(snap.trainer.name, sizeof snap.trainer.name, "RED");
    snap.trainer.trainerId = 413612;
    snap.trainer.playHours = 18;
    snap.trainer.playMinutes = 42;
    std::snprintf(snap.overworld.mapName, sizeof snap.overworld.mapName, "ROUTE 1");
    snap.progress.starterSpecies = 1;
    snap.gyms.slots = 8;
    snap.gyms.earned = 7;
    fillPreviewParty(snap.party);
    fillPreviewBoxes(snap.boxes);
}

}