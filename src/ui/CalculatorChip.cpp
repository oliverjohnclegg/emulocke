#include "ui/CalculatorDraw.hpp"
#include "ui/KitMark.hpp"

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
    const ImVec4 lit{72 / 255.f, 68 / 255.f, 62 / 255.f, 1.f};
    ImGui::PushStyleColor(ImGuiCol_Button, on ? lit : kButton);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, kButtonHover);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, kButtonActive);
    ImGui::PushStyleColor(ImGuiCol_Text, on ? kMetal : kDisabled);
    ImGui::PushStyleColor(ImGuiCol_Border, on ? ImVec4(kMetal.x, kMetal.y, kMetal.z, 0.55f)
                                              : kBorder);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.f, 1.f));
    const bool hit = ImGui::Button("CR");
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(5);
    return hit;
}

float calcCritMarkWidth() {
    return ImGui::CalcTextSize("CR").x + 8.f;
}

void drawCalcCrits(bool& ours, bool& theirs, float spineX, float abY, int focus, bool act) {
    const float w = calcCritMarkWidth();
    const float gap = 4.f;
    calcAlignCenter(w * 2.f + gap);
    ImGui::PushID("oh");
    ImGui::SetCursorScreenPos(ImVec2(spineX - w - 1.f, abY));
    if (calcCritMark(ours) || (act && focus == 0)) {
        ours = !ours;
    }
    kitStroke(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), focus == 0);
    ImGui::PopID();
    ImGui::SameLine(0.f, gap);
    ImGui::PushID("fh");
    ImGui::SetCursorScreenPos(ImVec2(spineX + 1.f, abY));
    if (calcCritMark(theirs) || (act && focus == 1)) {
        theirs = !theirs;
    }
    kitStroke(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), focus == 1);
    ImGui::PopID();
}

}
