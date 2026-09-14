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

bool isFrlg(std::string_view uuid) {
    return uuid == kFireRedUs10Uuid || uuid == kFireRedUs11Uuid || uuid == kLeafGreenUs10Uuid ||
        uuid == kLeafGreenUs11Uuid;
}

}  // namespace

const CalcPack* calcPack(std::string_view uuid, std::string_view) {
    if (isFrlg(uuid)) {
        return &kFrlgPack;
    }
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
