#include "ui/CalculatorDraw.hpp"

#include "calc/Calculate.hpp"
#include "calc/Dex.hpp"
#include "calc/KoChance.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <cstdio>

namespace emulocke {

void drawCalcKo(CalcSession& session, uint8_t dmgGen, uint8_t chart, const Pokemon& player,
    const Pokemon& foe, const uint16_t* ours, const uint16_t* theirs, const Field& intoFoe,
    const Field& intoUs) {
    const bool foeAtk = session.pickFoe();
    const uint16_t* moves = foeAtk ? theirs : ours;
    const MoveRow* row = moveById(moves[session.pickSlot()]);
    if (!row) {
        return;
    }
    Move mv = moveFromRow(*row);
    mv.crit = session.sideCrit(foeAtk);
    const Pokemon& atk = foeAtk ? foe : player;
    const Pokemon& def = foeAtk ? player : foe;
    const DamageResult dmg = calculate(dmgGen, chart, atk, def, mv, foeAtk ? intoUs : intoFoe);
    char line[72];
    koChance(line, sizeof line, dmg, def.hp);
    if (!line[0]) {
        return;
    }
    ImGui::Dummy(ImVec2(0, 12));
    const bool ko = dmg.ohko(def.hp);
    if (foeAtk) {
        calcAlignRight(ImGui::CalcTextSize(line).x);
    }
    if (ko) {
        ImGui::TextColored(ImVec4(196 / 255.f, 43 / 255.f, 43 / 255.f, 1.f), "%s", line);
    } else {
        ImGui::TextDisabled("%s", line);
    }
}

}
