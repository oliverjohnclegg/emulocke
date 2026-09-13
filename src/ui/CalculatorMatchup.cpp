#include "ui/CalculatorDraw.hpp"

#include "adapter/frlg/FrlgNames.hpp"
#include "application/Application.hpp"
#include "calc/Ai.hpp"
#include "calc/Build.hpp"
#include "calc/Calculate.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>

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
    const PackMon* foeSet = trainerMon(*pack, *t, session.foeSlot());
    if (!foeSet) {
        return;
    }
    Pokemon player = pokemonFromSnap(raw);
    Pokemon foe = pokemonFromPack(*foeSet);
    if (snap->battle.inBattle) {
        if (session.partySlot() == snap->battle.player.partyIndex) {
            applyBattler(player, snap->battle.player);
        }
        if (session.foeSlot() == snap->battle.foe.partyIndex) {
            applyBattler(foe, snap->battle.foe);
        } else if (snap->battle.foeMaxHp[session.foeSlot()]) {
            foe.hp = snap->battle.foeHp[session.foeSlot()];
            foe.maxHp = snap->battle.foeMaxHp[session.foeSlot()];
        }
    }
    const Field field = fieldFromSnap(snap);
    const int pSpe = finalSpeed(player, field);
    const int fSpe = finalSpeed(foe, field);
    const char* pName = raw.speciesName[0] ? raw.speciesName : player.name;
    const char* fName = frlgSpeciesName(foe.species);
    const ImVec2 top = ImGui::GetCursorScreenPos();
    const float pane = ImGui::GetContentRegionAvail().x;
    int pct[4]{};
    moveUsePct(pack->dmgGen, pack->typeChart, t->aiFlags, foe, player, foeSet->moves, field, pct);
    if (ImGui::BeginTable("calc-x", 3, ImGuiTableFlags_NoPadInnerX, ImVec2(pane, 0))) {
        ImGui::TableSetupColumn("a", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("s", ImGuiTableColumnFlags_WidthFixed, 78.f);
        ImGui::TableSetupColumn("b", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        drawCalcSideHead(pName, player, false);
        ImGui::TableSetColumnIndex(1);
        ImGui::Dummy(ImVec2(0, 8));
        ImGui::Text("%d", pSpe);
        if (pSpe > fSpe) {
            ImGui::SameLine();
            ImGui::TextDisabled(">spe");
        }
        ImGui::SameLine();
        ImGui::Text("%d", fSpe);
        if (fSpe > pSpe) {
            ImGui::SameLine();
            ImGui::TextDisabled(">spe");
        } else if (pSpe == fSpe) {
            ImGui::SameLine();
            ImGui::TextDisabled("tie");
        }
        ImGui::TableSetColumnIndex(2);
        drawCalcSideHead(fName, foe, true);
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Dummy(ImVec2(0, 8));
        drawCalcMoveCol(
            pack->dmgGen, pack->typeChart, player, foe, raw.moves, field, nullptr, false);
        ImGui::TableSetColumnIndex(2);
        ImGui::Dummy(ImVec2(0, 8));
        drawCalcMoveCol(pack->dmgGen, pack->typeChart, foe, player, foeSet->moves, field, pct, true);
        ImGui::EndTable();
    }
    const float bot = ImGui::GetCursorScreenPos().y;
    ImGui::GetWindowDrawList()->AddLine(ImVec2(top.x + pane * 0.5f, top.y),
        ImVec2(top.x + pane * 0.5f, bot), ImGui::GetColorU32(kBorder), 1.f);
}

}