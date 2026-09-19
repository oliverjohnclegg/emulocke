#include "ui/CalculatorDraw.hpp"

#include "adapter/frlg/FrlgNames.hpp"
#include "adapter/gen45/Names.hpp"
#include "application/Application.hpp"
#include "calc/Ai.hpp"
#include "calc/Build.hpp"
#include "calc/Calculate.hpp"
#include "ui/Theme.hpp"
#include "ui/KitNav.hpp"

#include <cstdio>
#include <imgui.h>

namespace emulocke {
namespace {

const uint16_t* calcFoeMoves(const GameSnapshot& snap, int slot, const uint16_t* packMoves) {
    if (!snap.battle.inBattle || slot < 0 || slot >= 6) {
        return packMoves;
    }
    const uint16_t* live = snap.battle.foeMoves[slot];
    if (live[0] || live[1] || live[2] || live[3]) {
        return live;
    }
    return packMoves;
}

void drawCalcSpe(int spe, int other, bool right) {
    char buf[8];
    std::snprintf(buf, sizeof buf, "%d", spe);
    if (right) {
        float w = ImGui::CalcTextSize(buf).x;
        if (spe > other) {
            w += ImGui::CalcTextSize(">spe").x + ImGui::GetStyle().ItemSpacing.x;
        }
        calcAlignRight(w);
        if (spe > other) {
            ImGui::TextDisabled(">spe");
            ImGui::SameLine();
        }
        ImGui::TextUnformatted(buf);
        return;
    }
    ImGui::TextUnformatted(buf);
    if (spe > other) {
        ImGui::SameLine();
        ImGui::TextDisabled(">spe");
    } else if (spe == other) {
        ImGui::SameLine();
        ImGui::TextDisabled("tie");
    }
}

}  // namespace

void drawCalcMatchup(Application& app, CalcSession& session) {
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
    Pokemon player = pokemonFromSnap(raw, pack);
    Pokemon foe = pokemonFromPack(*foeSet, pack);
    if (snap->battle.inBattle) {
        const int fs = session.foeSlot();
        if (fs >= 0 && fs < 6 && snap->battle.foeMaxHp[fs]) {
            foe.maxHp = snap->battle.foeMaxHp[static_cast<std::size_t>(fs)];
            foe.hp = snap->battle.foeHp[static_cast<std::size_t>(fs)];
            if (foe.hp > foe.maxHp) {
                foe.hp = foe.maxHp;
            }
            if (snap->battle.foeLevel[fs]) {
                foe.level = snap->battle.foeLevel[fs];
            }
            if (snap->battle.foeAtk[fs]) {
                foe.atk = snap->battle.foeAtk[fs];
            }
            if (snap->battle.foeDef[fs]) {
                foe.def = snap->battle.foeDef[fs];
            }
            if (snap->battle.foeSpa[fs]) {
                foe.spa = snap->battle.foeSpa[fs];
            }
            if (snap->battle.foeSpd[fs]) {
                foe.spd = snap->battle.foeSpd[fs];
            }
            if (snap->battle.foeSpe[fs]) {
                foe.spe = snap->battle.foeSpe[fs];
            }
        }
        if (session.partySlot() == snap->battle.player.partyIndex ||
            raw.species == snap->battle.player.species) {
            applyBattler(player, snap->battle.player);
        }
        if (session.foeSlot() == snap->battle.foe.partyIndex) {
            applyBattler(foe, snap->battle.foe);
        }
    }
    const uint16_t* foeMoves = calcFoeMoves(*snap, session.foeSlot(), foeSet->moves);
    const Field intoFoe = aimField(session.fieldState(), true);
    const Field intoUs = aimField(session.fieldState(), false);
    const int pSpe = finalSpeed(player, intoFoe);
    const int fSpe = finalSpeed(foe, intoFoe);
    const char* pName = raw.speciesName[0] ? raw.speciesName : player.name;
    const SpeciesRef foeRef =
        (pack->dmgGen == 4 || pack->dmgGen == 5) ? nationalSpeciesRef(foe.species) : SpeciesRef{};
    const char* fName = foeRef.name && foeRef.name[0] ? foeRef.name : frlgSpeciesName(foe.species);
    const ImVec2 top = ImGui::GetCursorScreenPos();
    const float pane = ImGui::GetContentRegionAvail().x;
    if (ImGui::BeginTable("calc-head", 3, ImGuiTableFlags_NoPadInnerX, ImVec2(pane, 0))) {
        ImGui::TableSetupColumn("a", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("s", ImGuiTableColumnFlags_WidthFixed, 78.f);
        ImGui::TableSetupColumn("b", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        drawCalcSideHead(pName, player, false, snap->battle.inBattle);
        const float abY = ImGui::GetItemRectMin().y;
        const float pSpeY = ImGui::GetCursorScreenPos().y;
        ImGui::TableSetColumnIndex(2);
        drawCalcSideHead(fName, foe, true, snap->battle.inBattle);
        const float fSpeY = ImGui::GetCursorScreenPos().y;
        const float speY = pSpeY > fSpeY ? pSpeY : fSpeY;
        ImGui::TableSetColumnIndex(0);
        ImGui::SetCursorScreenPos(ImVec2(ImGui::GetCursorScreenPos().x, speY));
        drawCalcSpe(pSpe, fSpe, false);
        ImGui::TableSetColumnIndex(1);
        ImGui::Dummy(ImVec2(0, 8));
        drawCalcCrits(session.sideCrit(false), session.sideCrit(true), top.x + pane * 0.5f, abY,
            app.kitFocus().calcCol == 1 ? app.kitFocus().calcRow : -1,
            kitNavSuite(app, KitTab::Calculator) && app.kit().act && app.kitFocus().calcCol == 1);
        ImGui::TableSetColumnIndex(2);
        ImGui::SetCursorScreenPos(ImVec2(ImGui::GetCursorScreenPos().x, speY));
        drawCalcSpe(fSpe, pSpe, true);
        ImGui::EndTable();
    }
    ImGui::Dummy(ImVec2(0, 8));
    int pct[4]{};
    moveUsePct(pack->dmgGen, pack->typeChart, t->aiFlags, foe, player, foeMoves, intoUs, pct,
        pack);
    if (ImGui::BeginTable("calc-mv", 2,
            ImGuiTableFlags_NoPadInnerX | ImGuiTableFlags_SizingStretchSame, ImVec2(pane, 0))) {
        ImGui::TableSetupColumn("a", ImGuiTableColumnFlags_WidthStretch, 1.f);
        ImGui::TableSetupColumn("b", ImGuiTableColumnFlags_WidthStretch, 1.f);
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        const bool kit = kitNavSuite(app, KitTab::Calculator);
        const int row = app.kitFocus().calcCol == 1 ? app.kitFocus().calcRow : -1;
        const bool act = kit && app.kit().act && app.kitFocus().calcCol == 1;
        drawCalcMoveCol(pack->dmgGen, pack->typeChart, player, foe, raw.moves, intoFoe, nullptr,
            session.sideCrit(false), false, session, row, act);
        ImGui::TableSetColumnIndex(1);
        drawCalcMoveCol(pack->dmgGen, pack->typeChart, foe, player, foeMoves, intoUs, pct,
            session.sideCrit(true), true, session, row, act);
        ImGui::EndTable();
    }
    const float bot = ImGui::GetCursorScreenPos().y;
    ImGui::GetWindowDrawList()->AddLine(ImVec2(top.x + pane * 0.5f, top.y),
        ImVec2(top.x + pane * 0.5f, bot), ImGui::GetColorU32(kBorder), 1.f);
    drawCalcKo(session, pack->dmgGen, pack->typeChart, player, foe, raw.moves, foeMoves,
        intoFoe, intoUs);
}

}