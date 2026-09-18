#include "ui/CalculatorMoveLine.hpp"

#include "calc/Calculate.hpp"
#include "calc/Dex.hpp"
#include "ui/Theme.hpp"

#include <algorithm>

namespace emulocke {

CalcHit evalCalcHit(uint8_t dmgGen, uint8_t chart, const Pokemon& atk, const Pokemon& def, Move mv,
    const Field& field, bool crit) {
    mv.crit = crit;
    CalcHit hit{};
    hit.dmg = calculate(dmgGen, chart, atk, def, mv, field);
    if (crit || hit.dmg.immune || hit.dmg.max <= 0 || hit.dmg.max >= def.hp) {
        hit.band = koBand(hit.dmg, nullptr, def.hp);
        return hit;
    }
    mv.crit = true;
    const DamageResult critDmg = calculate(dmgGen, chart, atk, def, mv, field);
    hit.band = koBand(hit.dmg, &critDmg, def.hp);
    return hit;
}

int collectCalcMoves(uint8_t dmgGen, uint8_t chart, const CalcPack* pack, const Pokemon& atk,
    const Pokemon& def, const uint16_t* moves, const Field& field, const int* pct, bool crit,
    CalcMoveLine* out) {
    int n = 0;
    for (int i = 0; i < 4; ++i) {
        Move mv = packedMove(pack, moves[i]);
        if (!mv.id) {
            continue;
        }
        const CalcHit hit = evalCalcHit(dmgGen, chart, atk, def, mv, field, crit);
        CalcMoveLine& line = out[n++];
        line.name = mv.name;
        line.blank = hit.dmg.immune || hit.dmg.max <= 0 || mv.kind == MoveKind::Status || mv.bp == 0;
        line.band = hit.band;
        line.slot = i;
        line.use = pct ? pct[i] : -1;
        line.pmin = def.maxHp > 0 ? hit.dmg.min * 100 / def.maxHp : 0;
        line.pmax = def.maxHp > 0 ? hit.dmg.max * 100 / def.maxHp : 0;
    }
    return n;
}

void sortCalcMoves(CalcMoveLine* lines, int n, bool byUse) {
    std::sort(lines, lines + n, [byUse](const CalcMoveLine& a, const CalcMoveLine& b) {
        if (byUse) {
            if (a.use != b.use) {
                return a.use > b.use;
            }
            return a.pmax != b.pmax ? a.pmax > b.pmax : a.pmin > b.pmin;
        }
        if (a.blank != b.blank) {
            return !a.blank && b.blank;
        }
        return a.pmax != b.pmax ? a.pmax > b.pmax : a.pmin > b.pmin;
    });
}

ImU32 calcKoInk(KoBand band) {
    switch (band) {
    case KoBand::Ohko:
        return kKoOhko;
    case KoBand::RollOhko:
        return kKoRollOhko;
    case KoBand::CritOhko:
        return kKoCritOhko;
    case KoBand::TwoHko:
        return kKoTwoHko;
    case KoBand::RollTwoHko:
        return kKoRollTwoHko;
    case KoBand::None:
        break;
    }
    return ImGui::GetColorU32(kMetal);
}

}
