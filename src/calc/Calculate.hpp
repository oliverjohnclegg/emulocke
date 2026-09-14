#pragma once

#include "calc/Field.hpp"
#include "calc/Move.hpp"
#include "calc/Pokemon.hpp"
#include "calc/Result.hpp"

namespace emulocke {

DamageResult calculate(uint8_t dmgGen, uint8_t typeChart, const Pokemon& atk, const Pokemon& def,
    const Move& move, const Field& field);

int finalSpeed(const Pokemon& mon, const Field& field);

}
