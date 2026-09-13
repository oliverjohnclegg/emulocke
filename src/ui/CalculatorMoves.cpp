#include "ui/CalculatorDraw.hpp"
#include "ui/CalculatorMoveLine.hpp"

#include <imgui.h>
#include <cstdio>

namespace emulocke {

void drawCalcMoveCol(uint8_t dmgGen, uint8_t chart, const Pokemon& atk, const Pokemon& def,
    const uint16_t* moves, const Field& field, const int* pct, bool right) {
    CalcMoveLine lines[4];
    const int n = collectCalcMoves(dmgGen, chart, atk, def, moves, field, pct, right, lines);
    sortCalcMoves(lines, n, right);
    if (right) {
        calcAlignRight(ImGui::CalcTextSize("AI").x);
        ImGui::TextDisabled("AI");
    } else {
        ImGui::TextDisabled(" ");
    }
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
    if (!ImGui::BeginTable("cmr", 3, ImGuiTableFlags_NoPadInnerX)) {
        return;
    }
    ImGui::TableSetupColumn("d", ImGuiTableColumnFlags_WidthFixed, 52.f);
    ImGui::TableSetupColumn("n", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableSetupColumn("a", ImGuiTableColumnFlags_WidthFixed, 32.f);
    for (int i = 0; i < n; ++i) {
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        drawCalcMoveDmg(lines[i], false);
        ImGui::TableSetColumnIndex(1);
        drawCalcMoveName(lines[i], true);
        ImGui::TableSetColumnIndex(2);
        if (lines[i].use >= 0) {
            char ai[12];
            std::snprintf(ai, sizeof ai, "%d", lines[i].use);
            calcAlignRight(ImGui::CalcTextSize(ai).x);
            ImGui::TextUnformatted(ai);
        }
    }
    ImGui::EndTable();
}

}
