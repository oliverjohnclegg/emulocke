#pragma once

#include "adapter/Snapshot.hpp"
#include "calc/Field.hpp"
#include "calc/Pack.hpp"
#include "calc/Pokemon.hpp"

namespace emulocke {

Pokemon pokemonFromPack(const PackMon& mon);
Pokemon pokemonFromSnap(const Mon& mon);
Field fieldFromSnap(const GameSnapshot* snap);
void applyBattler(Pokemon& mon, const BattleBattler& b);

}
