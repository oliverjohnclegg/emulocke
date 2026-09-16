#include "test/Check.hpp"

#include "run/Catalog.hpp"
#include "tracker/Atlas.hpp"
#include "tracker/Log.hpp"
#include "tracker/Snap.hpp"

#include <string_view>

void testTrackerSnap() {
    const emulocke::TrackerAtlas* atlas = emulocke::trackerAtlas(emulocke::kFireRedUs10Uuid, "");
    REQUIRE(atlas != nullptr);
    emulocke::TrackerLog log;
    const int pallet = emulocke::snapTrackerRow(*atlas, log, "PALLET TOWN");
    REQUIRE(pallet >= 0);
    REQUIRE(std::string_view(atlas->stops[static_cast<std::size_t>(pallet)].id) == "pallet-town");
    const int unknown = emulocke::snapTrackerRow(*atlas, log, "NOWHERE");
    REQUIRE(unknown >= 0);
    REQUIRE(atlas->stops[static_cast<std::size_t>(unknown)].kind == emulocke::TrackerStopKind::Encounter);
    REQUIRE(log.caught(atlas->stops[static_cast<std::size_t>(unknown)].id).status ==
        emulocke::EncounterStatus::Empty);
}
