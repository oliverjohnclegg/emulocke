#include "ui/CalculatorDraw.hpp"

#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {

bool calcChip(const char* label, bool on, float width) {
    const ImVec4 lit{72 / 255.f, 68 / 255.f, 62 / 255.f, 1.f};
    ImGui::PushStyleColor(ImGuiCol_Button, on ? lit : kButton);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, kButtonHover);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, kButtonActive);
    ImGui::PushStyleColor(ImGuiCol_Text, on ? kMetal : kDisabled);
    ImGui::PushStyleColor(ImGuiCol_Border, on ? ImVec4(kMetal.x, kMetal.y, kMetal.z, 0.55f)
                                              : kBorder);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(7.f, 3.f));
    const bool hit = ImGui::Button(label, ImVec2(width, 0.f));
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(5);
    return hit;
}

float calcChipWidth(const char* label) {
    return ImGui::CalcTextSize(label).x + 14.f;
}

bool calcCritMark(bool on) {
    const ImVec2 ts = ImGui::CalcTextSize("CR");
    const ImVec2 p = ImGui::GetCursorScreenPos();
    const bool hit = ImGui::InvisibleButton("CR", ts);
    const ImU32 col = ImGui::GetColorU32(on ? kMetal : kDisabled);
    ImGui::GetWindowDrawList()->AddText(p, col, "CR");
    if (on) {
        ImGui::GetWindowDrawList()->AddLine(
            ImVec2(p.x, p.y + ts.y - 1.f), ImVec2(p.x + ts.x, p.y + ts.y - 1.f), col, 1.f);
    }
    return hit;
}

}
