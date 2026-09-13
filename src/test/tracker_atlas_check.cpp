#include "run/Catalog.hpp"
#include "test/Check.hpp"
#include "tracker/Atlas.hpp"
#include "tracker/frlg/Keys.hpp"

#include <cstring>
#include <string>

void testTrackerAtlas() {
    const emulocke::TrackerAtlas* atlas = emulocke::trackerAtlas(emulocke::kFireRedUs10Uuid, "");
    REQUIRE(atlas != nullptr);
    REQUIRE(std::string(atlas->id) == "frlg");
    REQUIRE(!atlas->stops.empty());
    REQUIRE(std::strcmp(atlas->stops[0].id, "starter") == 0);
    REQUIRE(atlas->stops[0].kind == emulocke::TrackerStopKind::Encounter);
    REQUIRE(atlas->stops[0].catchKind == emulocke::CatchKind::Starter);

    REQUIRE(emulocke::trackerAtlas(emulocke::kFireRedUs11Uuid, "hardcore") == atlas);
    REQUIRE(emulocke::trackerAtlas(emulocke::kLeafGreenUs10Uuid, "") == atlas);
    REQUIRE(emulocke::trackerAtlas(emulocke::kLeafGreenUs11Uuid, "") == atlas);
    REQUIRE(emulocke::trackerAtlas(emulocke::kRadicalRedUuid, "") == nullptr);
    REQUIRE(emulocke::trackerAtlas(emulocke::kUnboundUuid, "expert") == nullptr);

    const emulocke::TrackerStop* forest = nullptr;
    const emulocke::TrackerStop* brock = nullptr;
    const emulocke::TrackerStop* route3 = nullptr;
    for (const emulocke::TrackerStop& stop : atlas->stops) {
        if (std::strcmp(stop.id, "viridian-forest") == 0) {
            forest = &stop;
        }
        if (forest && brock == nullptr && stop.kind == emulocke::TrackerStopKind::Boss) {
            brock = &stop;
        }
        if (std::strcmp(stop.id, "route-3") == 0) {
            route3 = &stop;
        }
    }
    REQUIRE(forest != nullptr);
    REQUIRE(brock != nullptr);
    REQUIRE(std::strcmp(brock->id, "brock") == 0);
    REQUIRE(route3 != nullptr);
    REQUIRE(route3->metCount == 1);
    REQUIRE(route3->mets != nullptr);
    REQUIRE(route3->mets[0] == emulocke::kMapRoute3);
    REQUIRE(route3->mets[0] == 0x0F);

    REQUIRE(brock->teamCount == 2);
    REQUIRE(std::strcmp(brock->team[0].slug, "geodude") == 0);
    REQUIRE(std::strcmp(brock->team[1].slug, "onix") == 0);
}
