#include "calc/Gen3.hpp"

#include "calc/Ability.hpp"

namespace emulocke {

int advBasePower(const AdvCtx& ctx, int hit) {
    const Move& m = *ctx.move;
    const Pokemon& a = *ctx.atk;
    const Field& f = *ctx.field;
    int bp = m.bp;
    if (m.kind == MoveKind::TripleKick) {
        bp = 10 * hit;
    }
    if (m.id == 228 && f.switchingOut) {
        bp *= 2;
    }
    if (a.hp * 3 <= a.maxHp) {
        const uint8_t ab = a.ability;
        if ((ab == kAbOvergrow && m.type == Type::Grass) || (ab == kAbBlaze && m.type == Type::Fire) ||
            (ab == kAbTorrent && m.type == Type::Water) || (ab == kAbSwarm && m.type == Type::Bug)) {
            bp = bp * 3 / 2;
        }
    }
    return bp;
}

bool advSpread(uint16_t id) {
    switch (id) {
    case 57:
    case 75:
    case 89:
    case 120:
    case 129:
    case 153:
    case 157:
    case 181:
    case 196:
    case 222:
    case 239:
    case 257:
    case 284:
    case 304:
        return true;
    default:
        return false;
    }
}

bool advImmune(const Pokemon& def, const Move& move, int typeEff) {
    if (typeEff == 0) {
        return true;
    }
    if (def.ability == kAbFlashFire && move.type == Type::Fire) {
        return true;
    }
    if (def.ability == kAbLevitate && move.type == Type::Ground) {
        return true;
    }
    if (def.ability == kAbVoltAbsorb && move.type == Type::Electric) {
        return true;
    }
    if (def.ability == kAbWaterAbsorb && move.type == Type::Water) {
        return true;
    }
    if (def.ability == kAbWonderGuard && typeEff <= 10) {
        return true;
    }
    if (def.ability == kAbSapSipper && move.type == Type::Grass) {
        return true;
    }
    return false;
}

int fixedDamage(const Pokemon& atk, const Pokemon& def, const Move& move) {
    if (move.kind == MoveKind::Level) {
        return atk.level;
    }
    if (move.kind == MoveKind::DragonRage) {
        return 40;
    }
    if (move.kind == MoveKind::SonicBoom) {
        return 20;
    }
    if (move.kind == MoveKind::SuperFang) {
        return def.hp / 2;
    }
    if (move.kind == MoveKind::Ohko) {
        return def.hp;
    }
    return 0;
}

}
