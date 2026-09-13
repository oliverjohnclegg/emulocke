#pragma once

#include <cstdint>
#include <string_view>

namespace emulocke {

struct PackMon {
    uint16_t species;
    uint8_t level;
    uint8_t iv;
    uint16_t item;
    uint16_t moves[4];
};

struct PackTrainer {
    uint16_t id;
    const char* name;
    const char* cls;
    const char* location;
    uint8_t count;
    uint16_t monOff;
    uint8_t mandatory;
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
};

const CalcPack* calcPack(std::string_view uuid, std::string_view variant);
const PackTrainer* packTrainer(const CalcPack& pack, uint16_t id);
const PackMon* trainerMon(const CalcPack& pack, const PackTrainer& trainer, int slot);

}
