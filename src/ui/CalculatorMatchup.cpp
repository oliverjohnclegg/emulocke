#include "ui/CalculatorDraw.hpp"

#include "adapter/frlg/FrlgNames.hpp"
#include "application/Application.hpp"
#include "calc/Build.hpp"
#include "calc/Calculate.hpp"
#include "calc/Dex.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <cstdio>

namespace emulocke {

void drawCalcMatchup(Application&, CalcSession& session) {
    const CalcPack* pack = session.pack();
    const PackTrainer* t = session.trainer();
    const GameSnapshot* snap = session.snap();
    if (!pack || !t || !snap || session.partySlot() < 0) {
        return;
    }
    const Mon& raw = snap->party.mons[static_cast<std::size_t>(session.partySlot())];
    if (raw.species == 0) {
        ImGui::TextDisabled("Lock a party mon.");
        return;
    }
    const int foeSlot = snap->battle.inBattle ? session.foeSlot() : session.nextIn();
    const PackMon* foeSet = trainerMon(*pack, *t, foeSlot);
    if (!foeSet) {
        return;
    }
    Pokemon player = pokemonFromSnap(raw);
    Pokemon foe = pokemonFromPack(*foeSet);
    if (snap->battle.inBattle) {
        applyBattler(player, snap->battle.player);
        applyBattler(foe, snap->battle.foe);
    }
    const Field field = fieldFromSnap(snap);
    const int pSpe = finalSpeed(player, field);
    const int fSpe = finalSpeed(foe, field);
    const char* pName = raw.speciesName[0] ? raw.speciesName : player.name;
    const char* fName = frlgSpeciesName(foe.species);
    ImGui::Dummy(ImVec2(0, 8));
    ImGui::TextUnformatted(pName);
    ImGui::SameLine();
    if (pSpe > fSpe) {
        ImGui::TextDisabled(">spe");
    }
    ImGui::SameLine(0, 16);
    ImGui::TextUnformatted(fName);
    ImGui::SameLine();
    if (fSpe > pSpe) {
        ImGui::TextDisabled(">spe");
    }
    ImGui::Separator();
    for (int i = 0; i < 4; ++i) {
        const MoveRow* row = moveById(raw.moves[i]);
        if (!row) {
            continue;
        }
        const Move mv = moveFromRow(*row);
        const DamageResult dmg = calculate(pack->dmgGen, pack->typeChart, player, foe, mv, field);
        char line[96];
        if (dmg.immune) {
            std::snprintf(line, sizeof line, "%-14s  --", mv.name);
            ImGui::TextDisabled("%s", line);
            continue;
        }
        std::snprintf(line, sizeof line, "%-14s  %d-%d", mv.name, dmg.min, dmg.max);
        if (dmg.ohko(foe.hp)) {
            ImGui::TextColored(ImVec4(196 / 255.f, 43 / 255.f, 43 / 255.f, 1.f), "%s  OHKO", line);
        } else if (dmg.twoHko(foe.hp)) {
            ImGui::Text("%s  2HKO", line);
        } else {
            ImGui::TextUnformatted(line);
        }
    }
}

}
