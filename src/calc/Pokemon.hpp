#pragma once

#include "calc/Type.hpp"

#include <cstdint>

namespace emulocke {

struct Pokemon {
    const char* name{"-"};
    uint16_t species{};
    Type t1{Type::Normal};
    Type t2{Type::None};
    int level{100};
    int hp{1};
    int maxHp{1};
    int atk{};
    int def{};
    int spa{};
    int spd{};
    int spe{};
    int8_t atkStage{};
    int8_t defStage{};
    int8_t speStage{};
    int8_t spaStage{};
    int8_t spdStage{};
    int8_t accStage{};
    int8_t evaStage{};
    uint8_t ability{};
    uint16_t item{};
    uint32_t status{};
    bool flashFire{};
};

}
