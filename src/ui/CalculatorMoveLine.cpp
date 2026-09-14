#include "ui/CalculatorMoveLine.hpp"

#include "calc/Calculate.hpp"
#include "calc/Dex.hpp"

#include <algorithm>

namespace emulocke {

int collectCalcMoves(uint8_t dmgGen, uint8_t chart, const Pokemon& atk, const Pokemon& def,
    const uint16_t* moves, const Field& field, const int* pct, bool crit, CalcMoveLine* out) {
    int n = 0;
    for (int i = 0; i < 4; ++i) {
        const MoveRow* row = moveById(moves[i]);
        if (!row) {
            continue;
        }
        Move mv = moveFromRow(*row);
        mv.crit = crit;
        const DamageResult dmg = calculate(dmgGen, chart, atk, def, mv, field);
        CalcMoveLine& line = out[n++];
        line.name = mv.name;
        line.blank = dmg.immune || mv.kind == MoveKind::Status || mv.bp == 0;
        line.ohko = dmg.ohko(def.hp);
        line.slot = i;
        line.use = pct ? pct[i] : -1;
        line.pmin = def.maxHp > 0 ? dmg.min * 100 / def.maxHp : 0;
        line.pmax = def.maxHp > 0 ? dmg.max * 100 / def.maxHp : 0;
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

}
