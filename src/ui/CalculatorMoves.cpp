#include "ui/CalculatorDraw.hpp"
#include "ui/CalculatorMoveLine.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <cstdio>

namespace emulocke {
namespace {

void drawCrit(CalcMoveLine& line, bool* crits) {
    if (!crits || !line.canCrit) {
        return;
    }
    ImGui::PushID(line.slot);
    if (calcChip("CR", line.crit)) {
        crits[line.slot] = !crits[line.slot];
    }
    ImGui::PopID();
}

}  // namespace

void drawCalcMoveCol(uint8_t dmgGen, uint8_t chart, const Pokemon& atk, const Pokemon& def,
    const uint16_t* moves, const Field& field, const int* pct, bool* crits, bool right) {
    CalcMoveLine lines[4];
    const int n = collectCalcMoves(dmgGen, chart, atk, def, moves, field, pct, crits, right, lines);
    sortCalcMoves(lines, n, right);
    if (!right) {
        if (!ImGui::BeginTable("cml", 3, ImGuiTableFlags_NoPadInnerX)) {
            return;
        }
        ImGui::TableSetupColumn("n", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("c", ImGuiTableColumnFlags_WidthFixed, 40.f);
        ImGui::TableSetupColumn("d", ImGuiTableColumnFlags_WidthFixed, 56.f);
        for (int i = 0; i < n; ++i) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            drawCalcMoveName(lines[i], false);
            ImGui::TableSetColumnIndex(1);
            drawCrit(lines[i], crits);
            ImGui::TableSetColumnIndex(2);
            drawCalcMoveDmg(lines[i], true);
        }
        ImGui::EndTable();
        return;
    }
    if (!ImGui::BeginTable("cmr", 3, ImGuiTableFlags_NoPadInnerX)) {
        return;
    }
    ImGui::TableSetupColumn("d", ImGuiTableColumnFlags_WidthFixed, 56.f);
    ImGui::TableSetupColumn("c", ImGuiTableColumnFlags_WidthFixed, 32.f);
    ImGui::TableSetupColumn("n", ImGuiTableColumnFlags_WidthStretch);
    for (int i = 0; i < n; ++i) {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        drawCalcMoveDmg(lines[i], false);
        ImGui::TableSetColumnIndex(1);
        drawCrit(lines[i], crits);
        ImGui::TableSetColumnIndex(2);
        if (lines[i].use >= 0) {
            char ai[16];
            std::snprintf(ai, sizeof ai, "AI %d", lines[i].use);
            const float nw = ImGui::CalcTextSize(lines[i].name).x;
            calcAlignRight(ImGui::CalcTextSize(ai).x + 8.f + nw);
            ImGui::TextColored(ImVec4(kMetal.x, kMetal.y, kMetal.z, 0.7f), "%s", ai);
            ImGui::SameLine(0, 8.f);
            drawCalcMoveName(lines[i], false);
        } else {
            drawCalcMoveName(lines[i], true);
        }
    }
    ImGui::EndTable();
}

}
