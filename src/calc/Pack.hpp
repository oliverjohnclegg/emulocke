#pragma once

#include <cstdint>
#include <string_view>

namespace emulocke {

struct SpeciesRow;

struct PackMon {
    uint16_t species;
    uint8_t level;
    uint8_t iv;
    uint16_t item;
    uint16_t moves[4];
    uint8_t ability{};
    uint8_t nature{};
    uint8_t evHp{};
    uint8_t evAtk{};
    uint8_t evDef{};
    uint8_t evSpe{};
    uint8_t evSpa{};
    uint8_t evSpd{};
};

struct PackTrainer {
    uint16_t id;
    const char* name;
    const char* cls;
    const char* location;
    uint8_t count;
    uint16_t monOff;
    uint8_t mandatory;
    uint32_t aiFlags;
};

struct PackLocation {
    const char* name;
    uint16_t count;
    uint16_t idOff;
};

struct CalcPack {
    const char* title;
    uint8_t dmgGen;
    uint8_t typeChart;
    uint8_t switchIn;
    const PackMon* mons;
    int monCount;
    const PackTrainer* trainers;
    int trainerCount;
    const uint16_t* locIds;
    const PackLocation* locations;
    int locationCount;
    const SpeciesRow* dex{};
    int dexCount{};
};

const CalcPack* calcPack(std::string_view uuid, std::string_view variant);
const PackTrainer* packTrainer(const CalcPack& pack, uint16_t id);
const PackMon* trainerMon(const CalcPack& pack, const PackTrainer& trainer, int slot);

}
