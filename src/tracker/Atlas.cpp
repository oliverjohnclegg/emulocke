#include "tracker/Atlas.hpp"

#include "run/Catalog.hpp"
#include "tracker/frlg/Frlg.hpp"

#include <cstring>

namespace emulocke {

const TrackerAtlas* trackerAtlas(std::string_view catalogUuid, std::string_view) {
    if (catalogUuid == kFireRedUs10Uuid || catalogUuid == kFireRedUs11Uuid ||
        catalogUuid == kLeafGreenUs10Uuid || catalogUuid == kLeafGreenUs11Uuid) {
        return &frlgAtlas();
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