#include "ui/CalculatorDraw.hpp"
#include "ui/CalculatorMoveLine.hpp"

#include "calc/Dex.hpp"
#include "calc/KoChance.hpp"

#include <imgui.h>

namespace emulocke {

void drawCalcKo(CalcSession& session, uint8_t dmgGen, uint8_t chart, const Pokemon& player,
    const Pokemon& foe, const uint16_t* ours, const uint16_t* theirs, const Field& intoFoe,
    const Field& intoUs) {
    const bool foeAtk = session.pickFoe();
    const uint16_t* moves = foeAtk ? theirs : ours;
    Move mv = packedMove(session.pack(), moves[session.pickSlot()]);
    if (!mv.id) {
        return;
    }
    const Pokemon& atk = foeAtk ? foe : player;
    const Pokemon& def = foeAtk ? player : foe;
    const CalcHit hit = evalCalcHit(dmgGen, chart, atk, def, mv, foeAtk ? intoUs : intoFoe,
        session.sideCrit(foeAtk));
    char line[72];
    koChance(line, sizeof line, hit.dmg, def.hp);
    if (!line[0]) {
        return;
    }
    ImGui::Dummy(ImVec2(0, 12));
    calcAlignCenter(ImGui::CalcTextSize(line).x);
    if (hit.dmg.immune || hit.dmg.max <= 0) {
        ImGui::TextDisabled("%s", line);
    } else {
        ImGui::TextColored(ImGui::ColorConvertU32ToFloat4(calcKoInk(hit.band)), "%s", line);
    }
}

}
