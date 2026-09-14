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
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.f, 0.f, 0.f, 0.f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.f, 0.f, 0.f, 0.f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.f, 0.f, 0.f, 0.f));
    ImGui::PushStyleColor(ImGuiCol_Text, on ? kMetal : kDisabled);
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.f, 0.f, 0.f, 0.f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2.f, 0.f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.f);
    const bool hit = ImGui::SmallButton("CR");
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(5);
    if (on) {
        const ImVec2 a = ImGui::GetItemRectMin();
        const ImVec2 b = ImGui::GetItemRectMax();
        ImGui::GetWindowDrawList()->AddLine(
            ImVec2(a.x + 2.f, b.y - 1.f), ImVec2(b.x - 2.f, b.y - 1.f), ImGui::GetColorU32(kMetal), 1.f);
    }
    return hit;
}

}
