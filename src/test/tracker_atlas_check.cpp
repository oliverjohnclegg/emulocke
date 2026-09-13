#include "run/Catalog.hpp"
#include "test/Check.hpp"
#include "tracker/Atlas.hpp"
#include "tracker/frlg/Keys.hpp"

#include <cstring>
#include <string>

namespace {

const emulocke::TrackerStop* findStop(const emulocke::TrackerAtlas& atlas, const char* id) {
    for (const emulocke::TrackerStop& stop : atlas.stops) {
        if (std::strcmp(stop.id, id) == 0) {
            return &stop;
        }
    }
    return nullptr;
}

void requireAtlas(const emulocke::TrackerAtlas* atlas) {
    REQUIRE(atlas != nullptr);
    REQUIRE(atlas->id != nullptr);
    REQUIRE(!atlas->stops.empty());
    REQUIRE(std::strcmp(atlas->stops[0].id, "starter") == 0);
    REQUIRE(atlas->stops[0].catchKind == emulocke::CatchKind::Starter);
    bool sawGym = false;
    bool sawRoute = false;
    for (const emulocke::TrackerStop& stop : atlas->stops) {
        if (stop.kind == emulocke::TrackerStopKind::Encounter && stop.catchKind == emulocke::CatchKind::Met) {
            sawRoute = true;
        }
        if (stop.bossKind == emulocke::BossKind::Gym) {
            REQUIRE(sawRoute);
            sawGym = true;
            break;
        }
    }
    REQUIRE(sawGym);
}

}  // namespace

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

    const char* all[] = {
        emulocke::kRubyUsUuid,           emulocke::kRubyUs11Uuid,        emulocke::kSapphireUsUuid,
        emulocke::kEmeraldUsUuid,        emulocke::kFireRedUs10Uuid,     emulocke::kFireRedUs11Uuid,
        emulocke::kLeafGreenUs10Uuid,     emulocke::kLeafGreenUs11Uuid,    emulocke::kDiamondUsUuid,
        emulocke::kPearlUsUuid,          emulocke::kPlatinumUsUuid,       emulocke::kPlatinumUs11Uuid,
        emulocke::kHeartGoldUsUuid,      emulocke::kSoulSilverUsUuid,     emulocke::kBlackUsUuid,
        emulocke::kWhiteUsUuid,          emulocke::kBlack2UsUuid,         emulocke::kWhite2UsUuid,
        emulocke::kBlazeBlackUuid,        emulocke::kVoltWhiteUuid,        emulocke::kVoltWhite2ReduxUuid,
        emulocke::kFireRedOmegaUuid,      emulocke::kSacredGoldUuid,        emulocke::kPlatinumKaizoUuid,
        emulocke::kRenegadePlatinumUuid,   emulocke::kRadicalRedUuid,       emulocke::kUnboundUuid,
        emulocke::kRunAndBunUuid,        emulocke::kInclementEmeraldUuid,  emulocke::kEmeraldKaizoUuid,
    };
    for (const char* uuid : all) {
        requireAtlas(emulocke::trackerAtlas(uuid, ""));
    }

    REQUIRE(emulocke::trackerAtlas(emulocke::kRubyUsUuid, "") ==
            emulocke::trackerAtlas(emulocke::kSapphireUsUuid, ""));
    REQUIRE(emulocke::trackerAtlas(emulocke::kRubyUsUuid, "") ==
            emulocke::trackerAtlas(emulocke::kRubyUs11Uuid, ""));
    REQUIRE(emulocke::trackerAtlas(emulocke::kDiamondUsUuid, "") ==
            emulocke::trackerAtlas(emulocke::kPearlUsUuid, ""));
    REQUIRE(emulocke::trackerAtlas(emulocke::kPlatinumUsUuid, "") ==
            emulocke::trackerAtlas(emulocke::kPlatinumUs11Uuid, ""));
    REQUIRE(emulocke::trackerAtlas(emulocke::kHeartGoldUsUuid, "") ==
            emulocke::trackerAtlas(emulocke::kSoulSilverUsUuid, ""));
    REQUIRE(emulocke::trackerAtlas(emulocke::kBlackUsUuid, "") ==
            emulocke::trackerAtlas(emulocke::kWhiteUsUuid, ""));
    REQUIRE(emulocke::trackerAtlas(emulocke::kBlack2UsUuid, "") ==
            emulocke::trackerAtlas(emulocke::kWhite2UsUuid, ""));

    const emulocke::TrackerAtlas* rr = emulocke::trackerAtlas(emulocke::kRadicalRedUuid, "");
    const emulocke::TrackerAtlas* rrh = emulocke::trackerAtlas(emulocke::kRadicalRedUuid, "hardcore");
    REQUIRE(rr != rrh);
    const emulocke::TrackerStop* brock = findStop(*rr, "gym-1");
    REQUIRE(brock != nullptr);
    REQUIRE(brock->teamCount == 4);
    REQUIRE(std::strcmp(brock->team[0].slug, "geodude-alola") == 0);

    REQUIRE(emulocke::trackerAtlas(emulocke::kUnboundUuid, "") !=
            emulocke::trackerAtlas(emulocke::kUnboundUuid, "expert"));
    REQUIRE(emulocke::trackerAtlas(emulocke::kUnboundUuid, "insane") ==
            emulocke::trackerAtlas(emulocke::kUnboundUuid, "expert"));
    REQUIRE(emulocke::trackerAtlas(emulocke::kVoltWhite2ReduxUuid, "") !=
            emulocke::trackerAtlas(emulocke::kVoltWhite2ReduxUuid, "challenge"));
    REQUIRE(emulocke::trackerAtlas(emulocke::kBlazeBlackUuid, "", "full") ==
            emulocke::trackerAtlas(emulocke::kBlazeBlackUuid, "", "clean"));
    REQUIRE(emulocke::trackerAtlas(emulocke::kBlazeBlackUuid, "") !=
            emulocke::trackerAtlas(emulocke::kVoltWhiteUuid, ""));

    const emulocke::TrackerAtlas* rs = emulocke::trackerAtlas(emulocke::kRubyUsUuid, "");
    const emulocke::TrackerStop* r101 = findStop(*rs, "route-101");
    REQUIRE(r101 != nullptr);
    REQUIRE(r101->metCount == 1);
    REQUIRE(r101->mets[0] == 16);

    const emulocke::TrackerAtlas* dp = emulocke::trackerAtlas(emulocke::kDiamondUsUuid, "");
    const emulocke::TrackerStop* twinleaf = findStop(*dp, "twinleaf-town");
    REQUIRE(twinleaf != nullptr);
    REQUIRE(twinleaf->mets[0] == 1);

    const emulocke::TrackerAtlas* hgss = emulocke::trackerAtlas(emulocke::kHeartGoldUsUuid, "");
    const emulocke::TrackerStop* bark = findStop(*hgss, "new-bark-town");
    REQUIRE(bark != nullptr);
    REQUIRE(bark->mets[0] == 126);

    const emulocke::TrackerAtlas* bw = emulocke::trackerAtlas(emulocke::kBlackUsUuid, "");
    const emulocke::TrackerStop* route1 = findStop(*bw, "route-1");
    REQUIRE(route1 != nullptr);
    REQUIRE(route1->mets[0] == 14);

    const emulocke::TrackerAtlas* b2w2 = emulocke::trackerAtlas(emulocke::kBlack2UsUuid, "");
    const emulocke::TrackerStop* aspertia = findStop(*b2w2, "aspertia-city");
    REQUIRE(aspertia != nullptr);
    REQUIRE(aspertia->mets[0] == 117);

    const emulocke::TrackerStop* forest = nullptr;
    const emulocke::TrackerStop* frBrock = nullptr;
    const emulocke::TrackerStop* route3 = nullptr;
    for (const emulocke::TrackerStop& stop : atlas->stops) {
        if (std::strcmp(stop.id, "viridian-forest") == 0) {
            forest = &stop;
        }
        if (forest && frBrock == nullptr && stop.kind == emulocke::TrackerStopKind::Boss) {
            frBrock = &stop;
        }
        if (std::strcmp(stop.id, "route-3") == 0) {
            route3 = &stop;
        }
    }
    REQUIRE(forest != nullptr);
    REQUIRE(frBrock != nullptr);
    REQUIRE(std::strcmp(frBrock->id, "brock") == 0);
    REQUIRE(route3 != nullptr);
    REQUIRE(route3->metCount == 1);
    REQUIRE(route3->mets != nullptr);
    REQUIRE(route3->mets[0] == emulocke::kMapRoute3);
    REQUIRE(route3->mets[0] == 0x0F);

    REQUIRE(frBrock->teamCount == 2);
    REQUIRE(std::strcmp(frBrock->team[0].slug, "geodude") == 0);
    REQUIRE(std::strcmp(frBrock->team[1].slug, "onix") == 0);

    const emulocke::TrackerStop* rival2 = nullptr;
    for (const emulocke::TrackerStop& stop : atlas->stops) {
        if (std::strcmp(stop.id, "rival-2") == 0) {
            rival2 = &stop;
            break;
        }
    }
    REQUIRE(rival2 != nullptr);
    REQUIRE(rival2->defeatFlag == emulocke::kFlagRivalRoute22);
    REQUIRE(rival2->defeatSpan == emulocke::kRivalTrainerSpan);
    REQUIRE(rival2->defeatFlag != 0x04F);
}