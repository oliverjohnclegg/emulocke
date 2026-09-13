#include "application/PreviewSuite.hpp"
#include "run/Catalog.hpp"
#include "test/Check.hpp"
#include "tracker/Atlas.hpp"

#include <string>
#include <unordered_set>

void testPreviewSuite() {
    emulocke::TrackerLog log;
    emulocke::GameSnapshot snap;
    emulocke::seedPreviewSuite(log, snap);
    REQUIRE(snap.ok);
    REQUIRE(std::string(snap.adapterId) == "firered-us-1.0");
    REQUIRE(snap.party.count == 6);
    REQUIRE(snap.party.mons[0].species == 1);
    REQUIRE(snap.party.mons[0].personality == 0x1001);
    REQUIRE(snap.party.mons[2].species == 25);
    REQUIRE(snap.party.mons[2].hp * 5 <= snap.party.mons[2].maxHp);
    REQUIRE(log.markedDead(0x1004));
    REQUIRE(!log.markedDead(0x1001));
    REQUIRE(log.caught("viridian-forest").status == emulocke::EncounterStatus::Dead);
    REQUIRE(log.caught("route-4").status == emulocke::EncounterStatus::Missed);
    REQUIRE(log.caught("celadon-city").status == emulocke::EncounterStatus::Traded);

    std::unordered_set<uint32_t> pids;
    bool caterpie = false;
    bool magikarp = false;
    int boxedLiving = 0;
    for (int i = 0; i < 6; ++i) {
        const emulocke::Mon& mon = snap.party.mons[static_cast<std::size_t>(i)];
        REQUIRE(mon.species != 0);
        REQUIRE(mon.personality != 0);
        REQUIRE(pids.insert(mon.personality).second);
        REQUIRE(mon.species != 10);
        REQUIRE(mon.species != 129);
        REQUIRE(!log.markedDead(mon.personality));
    }
    for (const emulocke::Mon& mon : snap.boxes.boxes[0].mons) {
        if (mon.species == 0) {
            continue;
        }
        REQUIRE(pids.insert(mon.personality).second);
        if (mon.species == 10) {
            caterpie = true;
        }
        if (mon.species == 129) {
            magikarp = true;
        }
        if (!mon.egg && !log.markedDead(mon.personality)) {
            ++boxedLiving;
        }
    }
    REQUIRE(caterpie);
    REQUIRE(!magikarp);
    REQUIRE(boxedLiving >= 16);
    REQUIRE(log.markedDead(0x1004));

    const emulocke::TrackerAtlas* atlas = emulocke::trackerAtlas(emulocke::kFireRedUs10Uuid, "");
    REQUIRE(atlas != nullptr);
    emulocke::applyTrackerFill(log, *atlas, snap);
    REQUIRE(log.caught("pallet-town").species == 0);
    REQUIRE(log.caught("viridian-forest").status == emulocke::EncounterStatus::Dead);
    REQUIRE(log.caught("starter").personality == 0x1001);
}