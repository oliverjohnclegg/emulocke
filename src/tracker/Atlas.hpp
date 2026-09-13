#pragma once

#include <cstdint>
#include <span>
#include <string_view>

namespace emulocke {

enum class TrackerStopKind : uint8_t { Encounter, Boss };
enum class BossKind : uint8_t { None, Gym, Rival, EliteFour, EvilTeam };
enum class CatchKind : uint8_t { None, Met, Starter };

struct BossMon {
    const char* slug = "";
    uint16_t starterLock{};
};

struct TrackerStop {
    const char* id = "";
    TrackerStopKind kind{TrackerStopKind::Encounter};
    const char* name = "";
    const char* locale = "";
    BossKind bossKind{BossKind::None};
    CatchKind catchKind{CatchKind::None};
    const uint8_t* mets{};
    uint8_t metCount{};
    const BossMon* team{};
    uint8_t teamCount{};
    uint16_t defeatFlag{};
    uint8_t defeatSpan{};
};

struct TrackerAtlas {
    const char* id = "";
    std::span<const TrackerStop> stops;
};

const TrackerAtlas* trackerAtlas(std::string_view catalogUuid, std::string_view difficulty);
int bossTeamSlugs(const TrackerStop& stop, uint16_t starter, const char** out, int cap);

}