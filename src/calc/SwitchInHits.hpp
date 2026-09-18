#pragma once

#include "calc/Dex.hpp"
#include "calc/Pack.hpp"
#include "calc/Pokemon.hpp"

namespace emulocke {

int playerHitsMon(uint8_t chart, const Pokemon& player, const SpeciesRow& row);
bool hasSeMove(uint8_t chart, const PackMon& mon, const Pokemon& player, const CalcPack* pack);
int maxHitVs(const CalcPack& pack, const PackMon& mon, const Pokemon& player);

}
