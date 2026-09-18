#include "calc/SwitchInHits.hpp"

#include "calc/Build.hpp"
#include "calc/Calculate.hpp"
#include "calc/Type.hpp"

namespace emulocke {
namespace {

int typeEff(uint8_t chart, Type t, const Pokemon& d) {
    int e = typeMul(chart, t, d.t1);
    if (d.t2 != Type::None && d.t2 != d.t1) {
        e = e * typeMul(chart, t, d.t2) / 10;
    }
    return e;
}

}  // namespace

int playerHitsMon(uint8_t chart, const Pokemon& player, const SpeciesRow& row) {
    const Type t1 = static_cast<Type>(row.t1);
    const Type t2 = row.t2 == row.t1 ? Type::None : static_cast<Type>(row.t2);
    int d = 10;
    d = d * typeMul(chart, player.t1, t1) / 10;
    if (t2 != Type::None) {
        d = d * typeMul(chart, player.t1, t2) / 10;
    }
    if (player.t2 != Type::None && player.t2 != player.t1) {
        d = d * typeMul(chart, player.t2, t1) / 10;
        if (t2 != Type::None) {
            d = d * typeMul(chart, player.t2, t2) / 10;
        }
    }
    return d;
}

bool hasSeMove(uint8_t chart, const PackMon& mon, const Pokemon& player, const CalcPack* pack) {
    for (int i = 0; i < 4; ++i) {
        const Move mv = packedMove(pack, mon.moves[i]);
        if (mv.id && typeEff(chart, mv.type, player) >= 20) {
            return true;
        }
    }
    return false;
}

int maxHitVs(const CalcPack& pack, const PackMon& mon, const Pokemon& player) {
    const Pokemon atk = pokemonFromPack(mon, &pack);
    int best = 0;
    for (int i = 0; i < 4; ++i) {
        const Move mv = packedMove(&pack, mon.moves[i]);
        if (!mv.id || mv.bp <= 1) {
            continue;
        }
        const DamageResult r = calculate(pack.dmgGen, pack.typeChart, atk, player, mv, Field{});
        if (!r.immune && r.max > best) {
            best = r.max;
        }
    }
    return best;
}

}
