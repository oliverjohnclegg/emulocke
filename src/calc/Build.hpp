#pragma once

#include "adapter/Snapshot.hpp"
#include "calc/Field.hpp"
#include "calc/Pack.hpp"
#include "calc/Pokemon.hpp"

namespace emulocke {

Pokemon pokemonFromPack(const PackMon& mon);
Pokemon pokemonFromPack(const PackMon& mon, const CalcPack* pack);
Pokemon pokemonFromSnap(const Mon& mon, const CalcPack* pack = nullptr);
Field fieldFromSnap(const GameSnapshot* snap);
void applyBattler(Pokemon& mon, const BattleBattler& b);

}
