#pragma once

#include <cstdint>
#include <span>
#include <string_view>

namespace emulocke {

enum class TrackerStopKind : uint8_t { Encounter, Boss };
enum class BossKind : uint8_t { None, Gym, Rival, EliteFour, EvilTeam, MiniBoss };
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
    const uint16_t* mets{};
    uint8_t metCount{};
    const BossMon* team{};
    uint8_t teamCount{};
    uint16_t defeatFlag{};
    uint8_t defeatSpan{};
    uint8_t gymIndex{};
    uint8_t cap{};
    uint8_t fieldCount{1};
    bool tag{};
    const char* weather = "";
    const char* note = "";
};

struct TrackerAtlas {
    const char* id = "";
    std::span<const TrackerStop> stops;
    std::span<const uint16_t> starters;
};

inline bool hoennInternalAtlas(std::string_view id) {
    return id == "rs" || id == "em" || id == "emkaizo" || id == "emrunbun";
}

inline uint16_t trackerSpeciesId(std::string_view atlasId, uint16_t species) {
    if (hoennInternalAtlas(atlasId) && species >= 277 && species <= 411) {
        return static_cast<uint16_t>(species - 25);
    }
    return species;
}

const TrackerAtlas* trackerAtlas(std::string_view catalogUuid, std::string_view difficulty,
                                 std::string_view patchOption = {});
int bossTeamSlugs(const TrackerStop& stop, uint16_t starter, const char** out, int cap);

}
