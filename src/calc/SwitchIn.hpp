#pragma once

#include "calc/Pack.hpp"

namespace emulocke {

int nextSwitchSlot(const CalcPack& pack, const PackTrainer& trainer, const bool fainted[6],
    uint8_t switchIn);

}
