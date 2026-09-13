#include "calc/Calculate.hpp"

#include "calc/Ability.hpp"
#include "calc/Gen3.hpp"
#include "calc/Nature.hpp"
#include "calc/Type.hpp"

#include <algorithm>

namespace emulocke {
namespace {

void fillRolls(DamageResult& out, int base) {
    for (int i = 0; i < 16; ++i) {
        out.rolls[i] = std::max(1, base * (85 + i) / 100);
    }
    out.min = out.rolls[0];
    out.max = out.rolls[15];
}

DamageResult oneHit(uint8_t chart, const Pokemon& atk, const Pokemon& def, const Move& move,
    const Field& field, int hit) {
    DamageResult out;
    int eff = 10;
    eff = eff * typeMul(chart, move.type, def.t1) / 10;
    if (def.t2 != Type::None && def.t2 != def.t1) {
        eff = eff * typeMul(chart, move.type, def.t2) / 10;
    }
    if (advImmune(def, move, eff) || move.kind == MoveKind::Status) {
        out.immune = true;
        return out;
    }
    const int fixed = fixedDamage(atk, def, move);
    if (fixed) {
        for (int i = 0; i < 16; ++i) {
            out.rolls[i] = fixed;
        }
        out.min = out.max = fixed;
        return out;
    }
    const bool crit = move.crit && def.ability != kAbBattleArmor && def.ability != kAbShellArmor;
    AdvCtx ctx{&atk, &def, &move, &field, chart, crit, move.category(chart) == MoveCat::Physical};
    const int bp = advBasePower(ctx, hit);
    if (bp <= 0) {
        out.immune = true;
        return out;
    }
    int base = ((2 * atk.level / 5 + 2) * advAttack(ctx) * bp / advDefense(ctx)) / 50;
    base = advFinal(base, ctx);
    base = base * typeMul(chart, move.type, def.t1) / 10;
    if (def.t2 != Type::None && def.t2 != def.t1) {
        base = base * typeMul(chart, move.type, def.t2) / 10;
    }
    fillRolls(out, base);
    return out;
}

}  // namespace

int finalSpeed(const Pokemon& mon, const Field& field) {
    int spe = boostedStat(mon.spe, mon.speStage);
    if (mon.status & kStPar) {
        spe /= 4;
    }
    (void)field;
    return spe;
}

DamageResult calculate(uint8_t, uint8_t typeChart, const Pokemon& atk, const Pokemon& def,
    const Move& move, const Field& field) {
    const int hits = std::max(1, move.hits);
    DamageResult total = oneHit(typeChart, atk, def, move, field, 1);
    total.hits = hits;
    if (total.immune || hits == 1) {
        return total;
    }
    for (int h = 2; h <= hits; ++h) {
        const DamageResult part = oneHit(typeChart, atk, def, move, field, h);
        for (int i = 0; i < 16; ++i) {
            total.rolls[i] += part.rolls[i];
        }
    }
    total.min = total.rolls[0];
    total.max = total.rolls[15];
    return total;
}

}
