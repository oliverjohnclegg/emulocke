#include "ui/CalculatorMoveLine.hpp"

#include "calc/Session.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <cstdio>

namespace emulocke {
namespace {

constexpr float kDmgCol = 56.f;

ImU32 ink(const CalcMoveLine& line) {
    if (line.blank) {
        return ImGui::GetColorU32(kDisabled);
    }
    if (line.ohko) {
        return IM_COL32(196, 43, 43, 255);
    }
    return ImGui::GetColorU32(kMetal);
}

void dmgText(char* d, int n, const CalcMoveLine& line) {
    if (line.blank) {
        std::snprintf(d, n, "--");
    } else if (line.ohko) {
        std::snprintf(d, n, "100%%+");
    } else if (line.pmin == line.pmax) {
        std::snprintf(d, n, "%d%%", line.pmin);
    } else {
        std::snprintf(d, n, "%d-%d%%", line.pmin, line.pmax);
    }
}

}  // namespace

void drawCalcMoveRow(const CalcMoveLine& line, bool right, CalcSession& session) {
    ImGui::PushID(line.slot);
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    const bool sel = session.pickFoe() == right && session.pickSlot() == line.slot;
    if (ImGui::Selectable("##pk", sel, ImGuiSelectableFlags_SpanAllColumns)) {
        session.pickMove(right, line.slot);
    }
    const ImVec2 a = ImGui::GetItemRectMin();
    const ImVec2 b = ImGui::GetItemRectMax();
    const float pad = ImGui::GetStyle().FramePadding.x;
    const float y = a.y + (b.y - a.y - ImGui::GetTextLineHeight()) * 0.5f;
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImU32 col = ink(line);
    char d[20];
    dmgText(d, sizeof d, line);
    const float dw = ImGui::CalcTextSize(d).x;
    const float nw = ImGui::CalcTextSize(line.name).x;
    if (!right) {
        dl->PushClipRect(a, ImVec2(b.x - kDmgCol, b.y), true);
        dl->AddText(ImVec2(a.x + pad, y), col, line.name);
        dl->PopClipRect();
        dl->AddText(ImVec2(b.x - pad - dw, y), col, d);
    } else {
        dl->AddText(ImVec2(a.x + pad, y), col, d);
        dl->PushClipRect(ImVec2(a.x + kDmgCol, a.y), b, true);
        if (line.use >= 0) {
            char ai[16];
            std::snprintf(ai, sizeof ai, "AI %d", line.use);
            const float aw = ImGui::CalcTextSize(ai).x;
            dl->AddText(ImVec2(b.x - pad - nw - 8.f - aw, y),
                ImGui::GetColorU32(ImVec4(kMetal.x, kMetal.y, kMetal.z, 0.7f)), ai);
        }
        dl->AddText(ImVec2(b.x - pad - nw, y), col, line.name);
        dl->PopClipRect();
    }
    ImGui::PopID();
}

}
