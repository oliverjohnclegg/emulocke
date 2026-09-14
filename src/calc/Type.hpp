#pragma once

#include <cstdint>

namespace emulocke {

enum class Type : uint8_t {
    Normal = 0,
    Fighting = 1,
    Flying = 2,
    Poison = 3,
    Ground = 4,
    Rock = 5,
    Bug = 6,
    Ghost = 7,
    Steel = 8,
    Mystery = 9,
    Fire = 10,
    Water = 11,
    Grass = 12,
    Electric = 13,
    Psychic = 14,
    Ice = 15,
    Dragon = 16,
    Dark = 17,
    Fairy = 18,
    None = 255
};

int typeMul(uint8_t chart, Type atk, Type def);
int typeEff(uint8_t chart, Type atk, Type t1, Type t2, bool foresight);
bool physicalType(Type type);
const char* typeName(Type type);

}
