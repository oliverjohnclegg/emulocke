#include "ui/CalculatorDraw.hpp"
#include "ui/CalculatorMoveLine.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <cstdio>

namespace emulocke {

void drawCalcMoveCol(uint8_t dmgGen, uint8_t chart, const Pokemon& atk, const Pokemon& def,
    const uint16_t* moves, const Field& field, const int* pct, bool right) {
    CalcMoveLine lines[4];
    const int n = collectCalcMoves(dmgGen, chart, atk, def, moves, field, pct, right, lines);
    sortCalcMoves(lines, n, right);
    if (!right) {
        if (!ImGui::BeginTable("cml", 2, ImGuiTableFlags_NoPadInnerX)) {
            return;
        }
        ImGui::TableSetupColumn("n", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("d", ImGuiTableColumnFlags_WidthFixed, 56.f);
        for (int i = 0; i < n; ++i) {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            drawCalcMoveName(lines[i], false);
            ImGui::TableSetColumnIndex(1);
            drawCalcMoveDmg(lines[i], true);
        }
        ImGui::EndTable();
        return;
    }
    if (!ImGui::BeginTable("cmr", 2, ImGuiTableFlags_NoPadInnerX)) {
        return;
    }
    ImGui::TableSetupColumn("d", ImGuiTableColumnFlags_WidthFixed, 56.f);
    ImGui::TableSetupColumn("n", ImGuiTableColumnFlags_WidthStretch);
    for (int i = 0; i < n; ++i) {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        drawCalcMoveDmg(lines[i], false);
        ImGui::TableSetColumnIndex(1);
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
