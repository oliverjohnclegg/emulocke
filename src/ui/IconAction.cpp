#include "ui/IconAction.hpp"

#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {

bool iconAction(const char* id, const char* tip, ImVec2 size) {
    const ImVec2 p = ImGui::GetCursorScreenPos();
    ImGui::InvisibleButton(id, size);
    const bool hovered = ImGui::IsItemHovered();
    const bool clicked = ImGui::IsItemClicked();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImVec2 q(p.x + size.x, p.y + size.y);
    dl->AddRectFilled(p, q, ImGui::GetColorU32(hovered ? kHeaderHover : kButton));
    dl->AddRect(p, q, ImGui::GetColorU32(kBorder));
    if (hovered) {
        ImGui::SetTooltip("%s", tip);
    }
    return clicked;
}

void iconPlus(ImVec2 p, ImVec2 size) {
    const float cx = p.x + size.x * 0.5f;
    const float cy = p.y + size.y * 0.5f;
    const float arm = size.x * 0.28f;
    const float t = 1.5f;
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImU32 metal = ImGui::GetColorU32(kMetal);
    dl->AddRectFilled(ImVec2(cx - arm, cy - t), ImVec2(cx + arm, cy + t), metal);
    dl->AddRectFilled(ImVec2(cx - t, cy - arm), ImVec2(cx + t, cy + arm), metal);
}

void iconX(ImVec2 p, ImVec2 size) {
    const float cx = p.x + size.x * 0.5f;
    const float cy = p.y + size.y * 0.5f;
    const float arm = size.x * 0.22f;
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImU32 metal = ImGui::GetColorU32(kMetal);
    dl->AddLine(ImVec2(cx - arm, cy - arm), ImVec2(cx + arm, cy + arm), metal, 1.5f);
    dl->AddLine(ImVec2(cx + arm, cy - arm), ImVec2(cx - arm, cy + arm), metal, 1.5f);
}

}
