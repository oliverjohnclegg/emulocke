#pragma once

#include "calc/Move.hpp"
#include "calc/Type.hpp"

#include <cstdint>

namespace emulocke {

struct SpeciesRow {
    uint16_t id;
    const char* slug;
    uint8_t t1;
    uint8_t t2;
    uint8_t hp;
    uint8_t atk;
    uint8_t def;
    uint8_t spa;
    uint8_t spd;
    uint8_t spe;
    uint8_t a1;
    uint8_t a2;
    uint16_t weight10;
};

struct MoveRow {
    uint16_t id;
    const char* name;
    uint8_t type;
    uint8_t bp;
    int8_t priority;
    uint8_t kind;
    uint8_t hits;
    uint8_t contact;
    uint8_t split{255};
};

const SpeciesRow* speciesById(uint16_t id);
const SpeciesRow* nationalDexRow(uint16_t id);
const SpeciesRow* speciesByName(const char* name);
const SpeciesRow* nationalDex();
int nationalDexCount();
const MoveRow* moveById(uint16_t id);
Move moveFromRow(const MoveRow& row);

}
