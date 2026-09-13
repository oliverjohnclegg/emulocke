#include "ui/CalculatorDraw.hpp"

#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {

void calcStamp(const char* label) {
    if (!label || !label[0]) {
        return;
    }
    const ImVec2 ts = ImGui::CalcTextSize(label);
    const ImVec2 p = ImGui::GetCursorScreenPos();
    const ImVec2 b(p.x + ts.x + 8.f, p.y + ts.y + 2.f);
    ImGui::GetWindowDrawList()->AddRect(
        p, b, ImGui::GetColorU32(ImVec4(kMetal.x, kMetal.y, kMetal.z, 0.45f)));
    ImGui::SetCursorScreenPos(ImVec2(p.x + 4.f, p.y + 1.f));
    ImGui::TextDisabled("%s", label);
    ImGui::SameLine(0, 8.f);
}

void calcAlignRight(float width) {
    const float inset = 6.f;
    const float avail = ImGui::GetContentRegionAvail().x;
    if (avail > width + inset) {
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + avail - width - inset);
    }
}

void calcPixelBar(int hp, int maxHp) {
    const float w = 48.f;
    const float h = 8.f;
    const ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->AddRectFilled(p, ImVec2(p.x + w, p.y + h), ImGui::GetColorU32(kScreenWell));
    int px = 0;
    if (maxHp > 0 && hp > 0) {
        px = hp * 48 / maxHp;
        if (px < 1) {
            px = 1;
        }
        if (px > 48) {
            px = 48;
        }
    }
    const ImU32 fill = (hp * 2 > maxHp)
        ? ImGui::GetColorU32(kMetal)
        : ImGui::GetColorU32(ImVec4(196 / 255.f, 43 / 255.f, 43 / 255.f, 1.f));
    if (px) {
        for (int i = 0; i < px; ++i) {
            dl->AddRectFilled(ImVec2(p.x + static_cast<float>(i), p.y),
                ImVec2(p.x + static_cast<float>(i) + 1.f, p.y + h), fill);
        }
    }
    dl->AddRect(p, ImVec2(p.x + w, p.y + h), ImGui::GetColorU32(kBorder));
    ImGui::Dummy(ImVec2(w, h));
}

}