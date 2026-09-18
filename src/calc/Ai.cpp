#include "calc/Ai.hpp"

#include "calc/Calculate.hpp"
#include "calc/Dex.hpp"
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

void moveUsePct(uint8_t dmgGen, uint8_t chart, uint32_t aiFlags, const Pokemon& foe,
    const Pokemon& player, const uint16_t moveIds[4], const Field& field, int pct[4],
    const CalcPack* pack) {
    int score[4]{};
    int dmgMax[4]{};
    bool live[4]{};
    int bestDmg = 0;
    for (int i = 0; i < 4; ++i) {
        pct[i] = 0;
        const Move mv = packedMove(pack, moveIds[i]);
        if (!mv.id) {
            continue;
        }
        live[i] = true;
        score[i] = 100;
        const bool status = mv.kind == MoveKind::Status || mv.bp == 0;
        const int eff = typeEff(chart, mv.type, player);
        DamageResult dmg{};
        if (!status) {
            dmg = calculate(dmgGen, chart, foe, player, mv, field);
            dmgMax[i] = dmg.immune ? 0 : dmg.max;
            if (dmgMax[i] > bestDmg) {
                bestDmg = dmgMax[i];
            }
        }
        if (aiFlags & kAiCheckBadMove) {
            if (status) {
                if (eff == 0 && mv.type != Type::Normal) {
                    score[i] -= 10;
                }
            } else if (dmg.immune || eff == 0) {
                score[i] -= 10;
            } else if (eff < 10) {
                score[i] -= 5;
            }
        }
        if (!status && (aiFlags & kAiTryToFaint) && player.hp > 0 && dmgMax[i] >= player.hp) {
            score[i] += finalSpeed(foe, field) >= finalSpeed(player, field) ? 4 : 2;
        }
    }
    if (bestDmg > 0 && (aiFlags & (kAiCheckViability | kAiPreferStrongest))) {
        for (int i = 0; i < 4; ++i) {
            if (!live[i] || dmgMax[i] <= 0) {
                continue;
            }
            if ((aiFlags & kAiCheckViability) && dmgMax[i] == bestDmg) {
                score[i] += 2;
            } else if ((aiFlags & kAiCheckViability) && dmgMax[i] * 2 < bestDmg) {
                score[i] -= 1;
            }
            if ((aiFlags & kAiPreferStrongest) && dmgMax[i] == bestDmg) {
                score[i] += 1;
            }
        }
    }
    int best = -999;
    int tied = 0;
    for (int i = 0; i < 4; ++i) {
        if (live[i] && score[i] > best) {
            best = score[i];
        }
    }
    for (int i = 0; i < 4; ++i) {
        if (live[i] && score[i] == best) {
            ++tied;
        }
    }
    if (!tied) {
        return;
    }
    int rem = 100 % tied;
    for (int i = 0; i < 4; ++i) {
        if (live[i] && score[i] == best) {
            pct[i] = 100 / tied + (rem > 0 ? 1 : 0);
            if (rem > 0) {
                --rem;
            }
        }
    }
}

}