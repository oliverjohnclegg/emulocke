#include "calc/Pack.hpp"

#include "run/Catalog.hpp"

#include <cstring>
#include <string_view>

namespace emulocke {
namespace {

constexpr PackMon kFrlgMons[] = {
#include "calc/data/PackFrlgMons.inc"
};
constexpr PackTrainer kFrlgTrainers[] = {
#include "calc/data/PackFrlgTrainers.inc"
};
constexpr uint16_t kFrlgLocIds[] = {
#include "calc/data/PackFrlgLocIds.inc"
};
constexpr PackLocation kFrlgLocs[] = {
#include "calc/data/PackFrlgLocs.inc"
};

constexpr PackMon kEmMons[] = {
#include "calc/data/PackEmMons.inc"
};
constexpr PackTrainer kEmTrainers[] = {
#include "calc/data/PackEmTrainers.inc"
};
constexpr uint16_t kEmLocIds[] = {
#include "calc/data/PackEmLocIds.inc"
};
constexpr PackLocation kEmLocs[] = {
#include "calc/data/PackEmLocs.inc"
};

constexpr PackMon kRsMons[] = {
#include "calc/data/PackRsMons.inc"
};
constexpr PackTrainer kRsTrainers[] = {
#include "calc/data/PackRsTrainers.inc"
};
constexpr uint16_t kRsLocIds[] = {
#include "calc/data/PackRsLocIds.inc"
};
constexpr PackLocation kRsLocs[] = {
#include "calc/data/PackRsLocs.inc"
};

constexpr PackMon kDpMons[] = {
#include "calc/data/PackDpMons.inc"
};
constexpr PackTrainer kDpTrainers[] = {
#include "calc/data/PackDpTrainers.inc"
};
constexpr uint16_t kDpLocIds[] = {
#include "calc/data/PackDpLocIds.inc"
};
constexpr PackLocation kDpLocs[] = {
#include "calc/data/PackDpLocs.inc"
};

constexpr PackMon kPtMons[] = {
#include "calc/data/PackPtMons.inc"
};
constexpr PackTrainer kPtTrainers[] = {
#include "calc/data/PackPtTrainers.inc"
};
constexpr uint16_t kPtLocIds[] = {
#include "calc/data/PackPtLocIds.inc"
};
constexpr PackLocation kPtLocs[] = {
#include "calc/data/PackPtLocs.inc"
};

constexpr PackMon kHgssMons[] = {
#include "calc/data/PackHgssMons.inc"
};
constexpr PackTrainer kHgssTrainers[] = {
#include "calc/data/PackHgssTrainers.inc"
};
constexpr uint16_t kHgssLocIds[] = {
#include "calc/data/PackHgssLocIds.inc"
};
constexpr PackLocation kHgssLocs[] = {
#include "calc/data/PackHgssLocs.inc"
};

constexpr PackMon kBwMons[] = {
#include "calc/data/PackBwMons.inc"
};
constexpr PackTrainer kBwTrainers[] = {
#include "calc/data/PackBwTrainers.inc"
};
constexpr uint16_t kBwLocIds[] = {
#include "calc/data/PackBwLocIds.inc"
};
constexpr PackLocation kBwLocs[] = {
#include "calc/data/PackBwLocs.inc"
};

constexpr PackMon kB2w2Mons[] = {
#include "calc/data/PackB2w2Mons.inc"
};
constexpr PackTrainer kB2w2Trainers[] = {
#include "calc/data/PackB2w2Trainers.inc"
};
constexpr uint16_t kB2w2LocIds[] = {
#include "calc/data/PackB2w2LocIds.inc"
};
constexpr PackLocation kB2w2Locs[] = {
#include "calc/data/PackB2w2Locs.inc"
};

constexpr CalcPack kFrlgPack{
    "FIRE RED / LEAF GREEN",
    3,
    3,
    3,
    kFrlgMons,
    static_cast<int>(sizeof(kFrlgMons) / sizeof(kFrlgMons[0])),
    kFrlgTrainers,
    static_cast<int>(sizeof(kFrlgTrainers) / sizeof(kFrlgTrainers[0])),
    kFrlgLocIds,
    kFrlgLocs,
    static_cast<int>(sizeof(kFrlgLocs) / sizeof(kFrlgLocs[0])),
};

constexpr CalcPack kEmPack{
    "EMERALD",
    3,
    3,
    3,
    kEmMons,
    static_cast<int>(sizeof(kEmMons) / sizeof(kEmMons[0])),
    kEmTrainers,
    static_cast<int>(sizeof(kEmTrainers) / sizeof(kEmTrainers[0])),
    kEmLocIds,
    kEmLocs,
    static_cast<int>(sizeof(kEmLocs) / sizeof(kEmLocs[0])),
};

constexpr CalcPack kRsPack{
    "RUBY / SAPPHIRE",
    3,
    3,
    3,
    kRsMons,
    static_cast<int>(sizeof(kRsMons) / sizeof(kRsMons[0])),
    kRsTrainers,
    static_cast<int>(sizeof(kRsTrainers) / sizeof(kRsTrainers[0])),
    kRsLocIds,
    kRsLocs,
    static_cast<int>(sizeof(kRsLocs) / sizeof(kRsLocs[0])),
};

constexpr CalcPack kDpPack{
    "DIAMOND / PEARL",
    4,
    4,
    4,
    kDpMons,
    static_cast<int>(sizeof(kDpMons) / sizeof(kDpMons[0])),
    kDpTrainers,
    static_cast<int>(sizeof(kDpTrainers) / sizeof(kDpTrainers[0])),
    kDpLocIds,
    kDpLocs,
    static_cast<int>(sizeof(kDpLocs) / sizeof(kDpLocs[0])),
};

constexpr CalcPack kPtPack{
    "PLATINUM",
    4,
    4,
    4,
    kPtMons,
    static_cast<int>(sizeof(kPtMons) / sizeof(kPtMons[0])),
    kPtTrainers,
    static_cast<int>(sizeof(kPtTrainers) / sizeof(kPtTrainers[0])),
    kPtLocIds,
    kPtLocs,
    static_cast<int>(sizeof(kPtLocs) / sizeof(kPtLocs[0])),
};

constexpr CalcPack kHgssPack{
    "HEARTGOLD / SOULSILVER",
    4,
    4,
    4,
    kHgssMons,
    static_cast<int>(sizeof(kHgssMons) / sizeof(kHgssMons[0])),
    kHgssTrainers,
    static_cast<int>(sizeof(kHgssTrainers) / sizeof(kHgssTrainers[0])),
    kHgssLocIds,
    kHgssLocs,
    static_cast<int>(sizeof(kHgssLocs) / sizeof(kHgssLocs[0])),
};

constexpr CalcPack kBwPack{
    "BLACK / WHITE",
    5,
    5,
    5,
    kBwMons,
    static_cast<int>(sizeof(kBwMons) / sizeof(kBwMons[0])),
    kBwTrainers,
    static_cast<int>(sizeof(kBwTrainers) / sizeof(kBwTrainers[0])),
    kBwLocIds,
    kBwLocs,
    static_cast<int>(sizeof(kBwLocs) / sizeof(kBwLocs[0])),
};

constexpr CalcPack kB2w2Pack{
    "BLACK 2 / WHITE 2",
    5,
    5,
    5,
    kB2w2Mons,
    static_cast<int>(sizeof(kB2w2Mons) / sizeof(kB2w2Mons[0])),
    kB2w2Trainers,
    static_cast<int>(sizeof(kB2w2Trainers) / sizeof(kB2w2Trainers[0])),
    kB2w2LocIds,
    kB2w2Locs,
    static_cast<int>(sizeof(kB2w2Locs) / sizeof(kB2w2Locs[0])),
};

#include "calc/data/PackGenerated.inc"

bool isFrlg(std::string_view uuid) {
    return uuid == kFireRedUs10Uuid || uuid == kFireRedUs11Uuid || uuid == kLeafGreenUs10Uuid ||
        uuid == kLeafGreenUs11Uuid;
}

}  // namespace

const CalcPack* calcPack(std::string_view uuid, [[maybe_unused]] std::string_view variant) {
#include "calc/data/PackRegistry.inc"
    return nullptr;
}

const PackTrainer* packTrainer(const CalcPack& pack, uint16_t id) {
    for (int i = 0; i < pack.trainerCount; ++i) {
        if (pack.trainers[i].id == id) {
            return &pack.trainers[i];
        }
    }
    return nullptr;
}

const PackMon* trainerMon(const CalcPack& pack, const PackTrainer& trainer, int slot) {
    if (slot < 0 || slot >= trainer.count) {
        return nullptr;
    }
    return &pack.mons[trainer.monOff + slot];
}

}
