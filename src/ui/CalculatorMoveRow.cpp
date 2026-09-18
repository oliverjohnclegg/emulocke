#include "ui/CalculatorMoveLine.hpp"
#include "ui/KitMark.hpp"

#include "calc/Session.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <cstdio>

namespace emulocke {
namespace {

ImU32 ink(const CalcMoveLine& line) {
    if (line.blank) {
        return ImGui::GetColorU32(kDisabled);
    }
    return calcKoInk(line.band);
}

void dmgText(char* d, int n, const CalcMoveLine& line) {
    if (line.blank) {
        std::snprintf(d, n, "--");
    } else if (line.pmin == line.pmax) {
        std::snprintf(d, n, "%d%%", line.pmin);
    } else {
        std::snprintf(d, n, "%d-%d%%", line.pmin, line.pmax);
    }
}

void paint(const char* s, ImU32 col, ImVec2 a, float w, float h, bool hugRight) {
    const float pad = ImGui::GetStyle().FramePadding.x;
    const float y = a.y + (h - ImGui::GetTextLineHeight()) * 0.5f;
    const float tw = ImGui::CalcTextSize(s).x;
    const float x = hugRight ? a.x + w - pad - tw : a.x + pad;
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->PushClipRect(a, ImVec2(a.x + w, a.y + h), true);
    dl->AddText(ImVec2(x, y), col, s);
    dl->PopClipRect();
}

}  // namespace

void drawCalcMoveRow(const CalcMoveLine& line, bool right, CalcSession& session, bool focus, bool act) {
    ImGui::PushID(right ? "f" : "u");
    ImGui::PushID(line.slot);
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    const ImVec2 c0 = ImGui::GetCursorScreenPos();
    const float w0 = ImGui::GetContentRegionAvail().x;
    const bool sel = session.pickFoe() == right && session.pickSlot() == line.slot;
    if (ImGui::Selectable("##pk", sel || focus, ImGuiSelectableFlags_SpanAllColumns) || act) {
        session.pickMove(right, line.slot);
    }
    kitStroke(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), focus);
    const float h = ImGui::GetItemRectSize().y;
    char d[20];
    dmgText(d, sizeof d, line);
    const ImU32 col = ink(line);
    if (!right) {
        paint(line.name, col, c0, w0, h, false);
        ImGui::TableSetColumnIndex(1);
        paint(d, col, ImGui::GetCursorScreenPos(), ImGui::GetContentRegionAvail().x, h, true);
    } else {
        paint(d, col, c0, w0, h, false);
        ImGui::TableSetColumnIndex(1);
        const ImVec2 c1 = ImGui::GetCursorScreenPos();
        const float w1 = ImGui::GetContentRegionAvail().x;
        if (line.use >= 0) {
            char ai[16];
            std::snprintf(ai, sizeof ai, "AI %d", line.use);
            const float nw = ImGui::CalcTextSize(line.name).x;
            const float aw = ImGui::CalcTextSize(ai).x;
            const float pad = ImGui::GetStyle().FramePadding.x;
            const float y = c1.y + (h - ImGui::GetTextLineHeight()) * 0.5f;
            ImDrawList* dl = ImGui::GetWindowDrawList();
            dl->PushClipRect(c1, ImVec2(c1.x + w1, c1.y + h), true);
            dl->AddText(ImVec2(c1.x + w1 - pad - nw - 8.f - aw, y),
                ImGui::GetColorU32(ImVec4(kMetal.x, kMetal.y, kMetal.z, 0.7f)), ai);
            dl->PopClipRect();
        }
        paint(line.name, col, c1, w1, h, true);
    }
    ImGui::PopID();
    ImGui::PopID();
}

}
