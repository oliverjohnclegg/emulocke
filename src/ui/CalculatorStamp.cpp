#include "ui/CalculatorDraw.hpp"

#include "calc/HpBar.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <cstdio>

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
    const float w = static_cast<float>(kHpBarPx);
    const float h = 8.f;
    const float row = ImGui::GetTextLineHeight();
    const ImVec2 p = ImGui::GetCursorScreenPos();
    const float y = p.y + (row - h) * 0.5f;
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->AddRectFilled(ImVec2(p.x, y), ImVec2(p.x + w, y + h), ImGui::GetColorU32(kScreenWell));
    const int px = hpBarPixels(hp, maxHp);
    const ImU32 fill = (hp * 2 > maxHp)
        ? ImGui::GetColorU32(kMetal)
        : ImGui::GetColorU32(ImVec4(196 / 255.f, 43 / 255.f, 43 / 255.f, 1.f));
    for (int i = 0; i < px; ++i) {
        dl->AddRectFilled(ImVec2(p.x + static_cast<float>(i), y),
            ImVec2(p.x + static_cast<float>(i) + 1.f, y + h), fill);
    }
    dl->AddRect(ImVec2(p.x, y), ImVec2(p.x + w, y + h), ImGui::GetColorU32(kBorder));
    ImGui::Dummy(ImVec2(w, row));
}

namespace {

void foeHpRange(char* buf, int n, int hp, int maxHp) {
    int lo = 0;
    int hi = 0;
    hpBarPctRange(hpBarPixels(hp, maxHp), lo, hi);
    if (lo == hi) {
        std::snprintf(buf, n, "(%d%%)", lo);
    } else {
        std::snprintf(buf, n, "(%d-%d%%)", lo, hi);
    }
}

}  // namespace

float calcFoeHpWidth(int hp, int maxHp) {
    char range[16];
    foeHpRange(range, sizeof range, hp, maxHp);
    return static_cast<float>(kHpBarPx) + ImGui::GetStyle().ItemSpacing.x +
        ImGui::CalcTextSize(range).x;
}

void calcFoeHp(int hp, int maxHp) {
    char range[16];
    foeHpRange(range, sizeof range, hp, maxHp);
    calcPixelBar(hp, maxHp);
    ImGui::SameLine();
    ImGui::TextUnformatted(range);
}

}