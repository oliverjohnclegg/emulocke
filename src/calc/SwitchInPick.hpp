#pragma once

#include "calc/Pack.hpp"
#include "calc/Pokemon.hpp"

namespace emulocke {

int mostSuitableMon(const CalcPack& pack, const PackTrainer& trainer, const bool skip[6],
    const Pokemon& player);

}
