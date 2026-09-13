#include "calc/Gen3.hpp"

#include "calc/Ability.hpp"
#include "calc/Nature.hpp"

#include <cstring>

namespace emulocke {
namespace {

bool named(const Pokemon& mon, const char* a, const char* b = nullptr) {
    if (std::strcmp(mon.name, a) == 0) {
        return true;
    }
    return b && std::strcmp(mon.name, b) == 0;
}

}  // namespace

int advAttack(const AdvCtx& ctx) {
    const Pokemon& a = *ctx.atk;
    const Pokemon& d = *ctx.def;
    const Move& m = *ctx.move;
    int at = ctx.physical ? a.atk : a.spa;
    if (ctx.physical && (a.ability == kAbHugePower || a.ability == kAbPurePower)) {
        at *= 2;
    }
    if (ctx.physical && a.item == kItemChoiceBand) {
        at = at * 3 / 2;
    }
    if (!ctx.physical && a.item == kItemSoulDew && (named(a, "Latios") || named(a, "Latias"))) {
        at = at * 3 / 2;
    }
    if (!ctx.physical && a.item == kItemLightBall && named(a, "Pikachu")) {
        at *= 2;
    }
    if (ctx.physical && a.item == kItemThickClub && (named(a, "Cubone") || named(a, "Marowak"))) {
        at *= 2;
    }
    if (d.ability == kAbThickFat && (m.type == Type::Fire || m.type == Type::Ice)) {
        at /= 2;
    }
    if (ctx.physical && (a.ability == kAbHustle || (a.ability == kAbGuts && a.status))) {
        at = at * 3 / 2;
    }
    const int stage = ctx.physical ? a.atkStage : a.spaStage;
    if (stage > 0 || (!ctx.crit && stage < 0)) {
        at = boostedStat(at, stage);
    }
    return at;
}

int advDefense(const AdvCtx& ctx) {
    const Pokemon& d = *ctx.def;
    int df = ctx.physical ? d.def : d.spd;
    if (!ctx.physical && d.item == kItemSoulDew && (named(d, "Latios") || named(d, "Latias"))) {
        df = df * 3 / 2;
    }
    if (ctx.physical && d.item == kItemMetalPowder && named(d, "Ditto")) {
        df *= 2;
    }
    if (ctx.physical && d.ability == kAbMarvelScale && d.status) {
        df = df * 3 / 2;
    }
    const int stage = ctx.physical ? d.defStage : d.spdStage;
    if (stage < 0 || (!ctx.crit && stage > 0)) {
        df = boostedStat(df, stage);
    }
    if (df < 1) {
        df = 1;
    }
    return df;
}

}
