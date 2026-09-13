#include "ui/CalculatorMoveLine.hpp"

#include "ui/CalculatorDraw.hpp"
#include "calc/Calculate.hpp"
#include "calc/Dex.hpp"

#include <imgui.h>
#include <algorithm>
#include <cstdio>

namespace emulocke {

int collectCalcMoves(uint8_t dmgGen, uint8_t chart, const Pokemon& atk, const Pokemon& def,
    const uint16_t* moves, const Field& field, const int* pct, bool intoUs, CalcMoveLine* out) {
    int n = 0;
    for (int i = 0; i < 4; ++i) {
        const MoveRow* row = moveById(moves[i]);
        if (!row) {
            continue;
        }
        const Move mv = moveFromRow(*row);
        const DamageResult dmg = calculate(dmgGen, chart, atk, def, mv, field);
        CalcMoveLine& line = out[n++];
        line.name = mv.name;
        line.pri[0] = 0;
        if (mv.priority) {
            std::snprintf(line.pri, sizeof line.pri, "%+d", mv.priority);
        }
        line.blank = dmg.immune || mv.kind == MoveKind::Status || mv.bp == 0;
        line.use = pct ? pct[i] : -1;
        line.pmin = def.maxHp > 0 ? dmg.min * 100 / def.maxHp : 0;
        line.pmax = def.maxHp > 0 ? dmg.max * 100 / def.maxHp : 0;
        line.ohko = dmg.ohko(intoUs ? def.hp : def.maxHp);
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

void drawCalcMoveDmg(const CalcMoveLine& line, bool hugRight) {
    char d[20];
    if (line.blank) {
        std::snprintf(d, sizeof d, "--");
    } else if (line.pmin == line.pmax) {
        std::snprintf(d, sizeof d, "%d%%", line.pmin);
    } else {
        std::snprintf(d, sizeof d, "%d-%d%%", line.pmin, line.pmax);
    }
    if (hugRight) {
        calcAlignRight(ImGui::CalcTextSize(d).x);
    }
    if (line.blank) {
        ImGui::TextDisabled("%s", d);
    } else if (line.ohko) {
        ImGui::TextColored(ImVec4(196 / 255.f, 43 / 255.f, 43 / 255.f, 1.f), "%s", d);
    } else {
        ImGui::TextUnformatted(d);
    }
}

void drawCalcMoveName(const CalcMoveLine& line, bool right) {
    char label[40];
    if (line.pri[0]) {
        std::snprintf(label, sizeof label, "%s %s", line.name, line.pri);
    } else {
        std::snprintf(label, sizeof label, "%s", line.name);
    }
    if (right) {
        calcAlignRight(ImGui::CalcTextSize(label).x);
    }
    ImGui::TextUnformatted(label);
}

}