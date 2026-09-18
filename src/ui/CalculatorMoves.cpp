#include "ui/CalculatorDraw.hpp"
#include "ui/CalculatorMoveLine.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {

void drawCalcMoveCol(uint8_t dmgGen, uint8_t chart, const Pokemon& atk, const Pokemon& def,
    const uint16_t* moves, const Field& field, const int* pct, bool crit, bool right,
    CalcSession& session, int focusRow, bool act) {
    CalcMoveLine lines[4];
    const int n =
        collectCalcMoves(dmgGen, chart, session.pack(), atk, def, moves, field, pct, crit, lines);
    sortCalcMoves(lines, n, right);
    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(72 / 255.f, 68 / 255.f, 62 / 255.f, 1.f));
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, kButtonHover);
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(72 / 255.f, 68 / 255.f, 62 / 255.f, 1.f));
    const ImVec2 tableW(ImGui::GetContentRegionAvail().x, 0.f);
    const int base = right ? 6 : 2;
    if (!right) {
        if (ImGui::BeginTable("cml", 2, ImGuiTableFlags_NoPadInnerX, tableW)) {
            ImGui::TableSetupColumn("n", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("d", ImGuiTableColumnFlags_WidthFixed, 88.f);
            for (int i = 0; i < n; ++i) {
                drawCalcMoveRow(lines[i], false, session, focusRow == base + i, act && focusRow == base + i);
            }
            ImGui::EndTable();
        }
    } else if (ImGui::BeginTable("cmr", 2, ImGuiTableFlags_NoPadInnerX, tableW)) {
        ImGui::TableSetupColumn("d", ImGuiTableColumnFlags_WidthFixed, 56.f);
        ImGui::TableSetupColumn("n", ImGuiTableColumnFlags_WidthStretch);
        for (int i = 0; i < n; ++i) {
            drawCalcMoveRow(lines[i], true, session, focusRow == base + i, act && focusRow == base + i);
        }
        ImGui::EndTable();
    }
    ImGui::PopStyleColor(3);
}

}
