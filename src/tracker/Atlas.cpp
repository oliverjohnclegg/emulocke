#include "tracker/Atlas.hpp"

#include "run/Catalog.hpp"
#include "tracker/Atlases.hpp"
#include "tracker/Difficulty.hpp"
#include "tracker/frlg/Frlg.hpp"

#include <cstring>

namespace emulocke {
namespace {

bool isFrlg(std::string_view uuid) {
    return uuid == kFireRedUs10Uuid || uuid == kFireRedUs11Uuid || uuid == kLeafGreenUs10Uuid ||
           uuid == kLeafGreenUs11Uuid;
}

}  // namespace

const TrackerAtlas* trackerAtlas(std::string_view catalogUuid, std::string_view difficulty,
                                 std::string_view) {
    if (isFrlg(catalogUuid)) {
        return &frlgAtlas();
    }
    if (catalogUuid == kRubyUsUuid || catalogUuid == kRubyUs11Uuid || catalogUuid == kSapphireUsUuid) {
        return &rsAtlas();
    }
    if (catalogUuid == kEmeraldUsUuid) {
        return &emAtlas();
    }
    if (catalogUuid == kDiamondUsUuid || catalogUuid == kPearlUsUuid) {
        return &dpAtlas();
    }
    if (catalogUuid == kPlatinumUsUuid || catalogUuid == kPlatinumUs11Uuid) {
        return &ptAtlas();
    }
    if (catalogUuid == kHeartGoldUsUuid || catalogUuid == kSoulSilverUsUuid) {
        return &hgssAtlas();
    }
    if (catalogUuid == kBlackUsUuid || catalogUuid == kWhiteUsUuid) {
        return &bwAtlas();
    }
    if (catalogUuid == kBlack2UsUuid || catalogUuid == kWhite2UsUuid) {
        return &b2w2Atlas();
    }
    if (catalogUuid == kBlazeBlackUuid) {
        return &blazeAtlas();
    }
    if (catalogUuid == kVoltWhiteUuid) {
        return &voltAtlas();
    }
    if (catalogUuid == kVoltWhite2ReduxUuid) {
        if (atlasDifficultyKey("volt-white-2-redux", difficulty) == "challenge") {
            return &blazevolt2_challengeAtlas();
        }
        return &blazevolt2Atlas();
    }
    if (catalogUuid == kSacredGoldUuid) {
        return &sacredgoldAtlas();
    }
    if (catalogUuid == kRenegadePlatinumUuid) {
        return &renplatAtlas();
    }
    if (catalogUuid == kEmeraldKaizoUuid) {
        return &emkaizoAtlas();
    }
    if (catalogUuid == kRunAndBunUuid) {
        return &emrunbunAtlas();
    }
    if (catalogUuid == kInclementEmeraldUuid) {
        return &incemAtlas();
    }
    if (catalogUuid == kRadicalRedUuid) {
        const std::string_view key = atlasDifficultyKey("radical-red-4.1", difficulty);
        if (key == "hardcore") {
            return &rr_hardcoreAtlas();
        }
        return &rrAtlas();
    }
    if (catalogUuid == kUnboundUuid) {
        const std::string_view key = atlasDifficultyKey("unbound-2.1.1.1", difficulty);
        if (key == "expert" || key == "insane") {
            return &unbound_expertAtlas();
        }
        return &unboundAtlas();
    }
    if (catalogUuid == kFireRedOmegaUuid) {
        return &froAtlas();
    }
    if (catalogUuid == kPlatinumKaizoUuid) {
        return &platinum_kaizoAtlas();
    }
    return nullptr;
}

int bossTeamSlugs(const TrackerStop& stop, uint16_t starter, const char** out, int cap) {
    if (!out || cap <= 0 || !stop.team) {
        return 0;
    }
    int n = 0;
    auto push = [&](const char* slug) {
        if (!slug || !*slug || n >= cap) {
            return;
        }
        for (int i = 0; i < n; ++i) {
            if (std::strcmp(out[i], slug) == 0) {
                return;
            }
        }
        out[n++] = slug;
    };
    for (uint8_t i = 0; i < stop.teamCount; ++i) {
        const BossMon& mon = stop.team[i];
        if (starter != 0 && mon.starterLock != 0 && mon.starterLock != starter) {
            continue;
        }
        push(mon.slug);
    }
    return n;
}

}
