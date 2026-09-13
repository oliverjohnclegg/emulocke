#include "ui/CalculatorDraw.hpp"

#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {

bool calcChip(const char* label, bool on, float width) {
    ImGui::PushStyleColor(ImGuiCol_Button, on ? kHeaderActive : kButton);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, kButtonHover);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, kButtonActive);
    ImGui::PushStyleColor(ImGuiCol_Text, on ? kMetal : kDisabled);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(7.f, 2.f));
    const bool hit = ImGui::Button(label, ImVec2(width, 0.f));
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(4);
    return hit;
}

}
