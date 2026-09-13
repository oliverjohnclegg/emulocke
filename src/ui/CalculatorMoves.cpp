#include "ui/CalculatorDraw.hpp"

#include "calc/Calculate.hpp"
#include "calc/Dex.hpp"

#include <imgui.h>
#include <cstdio>

namespace emulocke {

void drawCalcMoveCol(uint8_t dmgGen, uint8_t chart, const Pokemon& atk, const Pokemon& def,
    const uint16_t* moves, const Field& field, const int* pct) {
    for (int i = 0; i < 4; ++i) {
        const MoveRow* row = moveById(moves[i]);
        if (!row) {
            continue;
        }
        const Move mv = moveFromRow(*row);
        const DamageResult dmg = calculate(dmgGen, chart, atk, def, mv, field);
        char pri[8]{};
        if (mv.priority) {
            std::snprintf(pri, sizeof pri, "%+d", mv.priority);
        }
        const bool blank = dmg.immune || mv.kind == MoveKind::Status || mv.bp == 0;
        char line[96];
        if (blank && pct) {
            std::snprintf(line, sizeof line, "%-12s %3s  --  %d%%", mv.name, pri, pct[i]);
        } else if (blank) {
            std::snprintf(line, sizeof line, "%-12s %3s  --", mv.name, pri);
        } else if (pct) {
            std::snprintf(line, sizeof line, "%-12s %3s  %d-%d  %d%%", mv.name, pri, dmg.min, dmg.max,
                pct[i]);
        } else {
            std::snprintf(line, sizeof line, "%-12s %3s  %d-%d", mv.name, pri, dmg.min, dmg.max);
        }
        if (blank) {
            ImGui::TextDisabled("%s", line);
        } else if (dmg.ohko(def.hp)) {
            ImGui::TextColored(ImVec4(196 / 255.f, 43 / 255.f, 43 / 255.f, 1.f), "%s  OHKO", line);
        } else if (dmg.twoHko(def.hp)) {
            ImGui::Text("%s  2HKO", line);
        } else {
            ImGui::TextUnformatted(line);
        }
    }
}

}