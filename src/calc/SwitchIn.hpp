#pragma once

#include "calc/Pack.hpp"
#include "calc/Pokemon.hpp"

namespace emulocke {

int nextSwitchSlot(const CalcPack& pack, const PackTrainer& trainer, const bool fainted[6],
    const Pokemon& player, uint8_t switchIn, int current = -1);
void switchOrder(const CalcPack& pack, const PackTrainer& trainer, const bool fainted[6],
    const Pokemon& player, uint8_t switchIn, int order[6], int current = -1);

}
