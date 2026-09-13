#include "calc/Gen3.hpp"

#include "calc/Ability.hpp"
#include "calc/Type.hpp"

#include <algorithm>

namespace emulocke {

int advFinal(int base, const AdvCtx& ctx) {
    const Pokemon& a = *ctx.atk;
    const Move& m = *ctx.move;
    const Field& f = *ctx.field;
    if ((a.status & kStBurn) && ctx.physical && a.ability != kAbGuts) {
        base /= 2;
    }
    if (!ctx.crit) {
        if ((ctx.physical && f.reflect) || (!ctx.physical && f.lightScreen)) {
            base = f.doubles ? base * 2 / 3 : base / 2;
        }
    }
    if ((f.weather == Weather::Sun && m.type == Type::Fire) ||
        (f.weather == Weather::Rain && m.type == Type::Water)) {
        base = base * 3 / 2;
    } else if ((f.weather == Weather::Sun && m.type == Type::Water) ||
        (f.weather == Weather::Rain && m.type == Type::Fire)) {
        base /= 2;
    }
    if (a.ability == kAbFlashFire && a.flashFire && m.type == Type::Fire) {
        base = base * 3 / 2;
    }
    if (f.doubles && advSpread(m.id)) {
        base /= 2;
    }
    base = (ctx.physical ? std::max(1, base) : base) + 2;
    if (ctx.crit) {
        base *= 2;
    }
    if (f.helpingHand) {
        base = base * 3 / 2;
    }
    if (m.type == a.t1 || m.type == a.t2) {
        base = base * 3 / 2;
    }
    return base;
}

}
