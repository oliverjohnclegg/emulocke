#include "adapter/Snapshot.hpp"
#include "run/Catalog.hpp"
#include "test/Check.hpp"
#include "tracker/Atlas.hpp"
#include "tracker/Log.hpp"
#include "tracker/frlg/Keys.hpp"

#include <cstring>

namespace {

void setFlag(emulocke::Progress& progress, uint16_t id) {
    progress.flags[id / 8] =
        static_cast<uint8_t>(progress.flags[id / 8] | (1u << (id % 8)));
}

void requireOnlyRival(const emulocke::TrackerLog& log, const char* id) {
    const char* rivals[] = {"rival-1", "rival-2", "rival-3", "rival-4", "rival-5", "rival-6",
                             "rival-7"};
    for (const char* rival : rivals) {
        if (std::strcmp(rival, id) == 0) {
            REQUIRE(log.defeated(rival));
        } else {
            REQUIRE(!log.defeated(rival));
        }
    }
}

}  // namespace

void testTrackerRivalFill() {
    const emulocke::TrackerAtlas* atlas = emulocke::trackerAtlas(emulocke::kFireRedUs10Uuid, "");
    REQUIRE(atlas != nullptr);

    emulocke::TrackerLog hideLog;
    emulocke::GameSnapshot snap;
    snap.ok = true;
    setFlag(snap.progress, 0x03C);
    setFlag(snap.progress, 0x03D);
    setFlag(snap.progress, 0x04E);
    setFlag(snap.progress, 0x04F);
    setFlag(snap.progress, 0x051);
    emulocke::applyTrackerFill(hideLog, *atlas, snap);
    REQUIRE(!hideLog.defeated("rival-1"));
    REQUIRE(!hideLog.defeated("rival-2"));
    REQUIRE(!hideLog.defeated("rival-3"));
    REQUIRE(!hideLog.defeated("rival-4"));
    REQUIRE(!hideLog.defeated("rival-5"));
    REQUIRE(!hideLog.defeated("rival-6"));
    REQUIRE(!hideLog.defeated("rival-7"));

    emulocke::TrackerLog lab;
    emulocke::GameSnapshot labSnap;
    labSnap.ok = true;
    setFlag(labSnap.progress, emulocke::kFlagBeatLabRival);
    emulocke::applyTrackerFill(lab, *atlas, labSnap);
    requireOnlyRival(lab, "rival-1");

    emulocke::TrackerLog route22;
    emulocke::GameSnapshot routeSnap;
    routeSnap.ok = true;
    setFlag(routeSnap.progress, emulocke::kFlagRivalRoute22 + 1);
    emulocke::applyTrackerFill(route22, *atlas, routeSnap);
    requireOnlyRival(route22, "rival-2");

    const emulocke::TrackerAtlas* rr = emulocke::trackerAtlas(emulocke::kRadicalRedUuid, "");
    REQUIRE(rr != nullptr);
    emulocke::TrackerLog labRr;
    emulocke::GameSnapshot rrSnap;
    rrSnap.ok = true;
    setFlag(rrSnap.progress, emulocke::kFlagBeatLabRival);
    emulocke::applyTrackerFill(labRr, *rr, rrSnap);
    REQUIRE(labRr.defeated("r1"));
    REQUIRE(!labRr.defeated("r2"));
}
