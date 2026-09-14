#include "ui/IconAction.hpp"

#include "ui/Theme.hpp"

#include <imgui.h>
#include <cmath>
#include <numbers>

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

void iconRetry(ImVec2 p, ImVec2 size) {
    const float cx = p.x + size.x * 0.5f;
    const float cy = p.y + size.y * 0.5f;
    const float r = size.x * 0.28f;
    const float t = 1.5f;
    const float a0 = std::numbers::pi_v<float> * 0.45f;
    const float a1 = std::numbers::pi_v<float> * 2.05f;
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImU32 metal = ImGui::GetColorU32(kMetal);
    dl->PathArcTo(ImVec2(cx, cy), r, a0, a1, 16);
    dl->PathStroke(metal, 0, t);
    const float ax = cx + std::cos(a1) * r;
    const float ay = cy + std::sin(a1) * r;
    const float s = size.x * 0.16f;
    dl->AddTriangleFilled(ImVec2(ax - std::sin(a1) * s, ay + std::cos(a1) * s),
        ImVec2(ax + std::sin(a1) * s, ay - std::cos(a1) * s),
        ImVec2(ax + std::cos(a1) * s, ay + std::sin(a1) * s), metal);
}

void iconTrash(ImVec2 p, ImVec2 size) {
    const float cx = p.x + size.x * 0.5f;
    const float cy = p.y + size.y * 0.5f;
    const float w = size.x * 0.20f;
    const float t = 1.5f;
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImU32 metal = ImGui::GetColorU32(kMetal);
    dl->AddLine(ImVec2(cx - w * 1.2f, cy - w * 0.45f), ImVec2(cx + w * 1.2f, cy - w * 0.45f), metal, t);
    dl->AddLine(ImVec2(cx - w * 0.35f, cy - w * 0.85f), ImVec2(cx + w * 0.35f, cy - w * 0.85f), metal, t);
    dl->AddLine(ImVec2(cx - w, cy - w * 0.45f), ImVec2(cx - w * 0.75f, cy + w * 1.05f), metal, t);
    dl->AddLine(ImVec2(cx + w, cy - w * 0.45f), ImVec2(cx + w * 0.75f, cy + w * 1.05f), metal, t);
    dl->AddLine(ImVec2(cx - w * 0.75f, cy + w * 1.05f), ImVec2(cx + w * 0.75f, cy + w * 1.05f), metal, t);
    dl->AddLine(ImVec2(cx, cy - w * 0.2f), ImVec2(cx, cy + w * 0.75f), metal, t);
    dl->AddLine(ImVec2(cx - w * 0.4f, cy - w * 0.2f), ImVec2(cx - w * 0.32f, cy + w * 0.75f), metal, t);
    dl->AddLine(ImVec2(cx + w * 0.4f, cy - w * 0.2f), ImVec2(cx + w * 0.32f, cy + w * 0.75f), metal, t);
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
