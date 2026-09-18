#include "ui/CalculatorDraw.hpp"

#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {
namespace {

constexpr float kStampPx = 11.f;
constexpr float kStampPad = 2.f;
constexpr float kStampGap = 3.f;
constexpr int kStampRows = 2;

float stampChipW(ImFont* font, float px, const char* label) {
    return font->CalcTextSizeA(px, 1e9f, 0.f, label).x + kStampPad * 2.f;
}

int stampRows(ImFont* font, float px, float avail, const char* const* labels, int n) {
    float x = 0.f;
    int rows = 1;
    for (int i = 0; i < n; ++i) {
        if (!labels[i] || !labels[i][0]) {
            continue;
        }
        const float w = stampChipW(font, px, labels[i]);
        if (x > 0.f && x + w > avail) {
            x = 0.f;
            ++rows;
        }
        x += w + kStampGap;
    }
    return rows;
}

float stampPx(ImFont* font, float avail, const char* const* labels, int n) {
    float px = kStampPx;
    while (px > 8.f && stampRows(font, px, avail, labels, n) > kStampRows) {
        px -= 1.f;
    }
    return px;
}

void stampAt(ImDrawList* dl, ImFont* font, float px, ImVec2 p, const char* label) {
    const ImVec2 sz(stampChipW(font, px, label), px + kStampPad * 2.f);
    dl->AddRect(p, ImVec2(p.x + sz.x, p.y + sz.y),
        ImGui::GetColorU32(ImVec4(kMetal.x, kMetal.y, kMetal.z, 0.45f)));
    dl->AddText(font, px, ImVec2(p.x + kStampPad, p.y + kStampPad), ImGui::GetColorU32(kMetal),
        label);
}

}  // namespace

void calcStampBlock(const char* const* labels, int n, bool right, bool hold) {
    const float h = static_cast<float>(kStampRows) * (kStampPx + kStampPad * 2.f + 2.f) - 2.f;
    if (!labels || n <= 0) {
        if (hold) ImGui::Dummy(ImVec2(0.f, h));
        return;
    }
    ImFont* font = ImGui::GetFont();
    const float avail = ImGui::GetContentRegionAvail().x;
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    const float px = stampPx(font, avail, labels, n);
    const float rowH = px + kStampPad * 2.f + 2.f;
    float x = 0.f;
    int row = 0;
    float rowW[4]{};
    ImVec2 pos[8]{};
    const int used = n > 8 ? 8 : n;
    for (int i = 0; i < used; ++i) {
        if (!labels[i] || !labels[i][0]) {
            continue;
        }
        const float w = stampChipW(font, px, labels[i]);
        if (x > 0.f && x + w > avail && row + 1 < kStampRows) {
            x = 0.f;
            ++row;
        }
        pos[i] = ImVec2(x, rowH * static_cast<float>(row));
        x += w + kStampGap;
        rowW[row] = x - kStampGap;
    }
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImGui::PushClipRect(origin, ImVec2(origin.x + avail, origin.y + h), true);
    for (int i = 0; i < used; ++i) {
        if (!labels[i] || !labels[i][0]) {
            continue;
        }
        const int r = static_cast<int>(pos[i].y / rowH + 0.1f);
        float ox = 0.f;
        if (right && avail > rowW[r]) {
            ox = avail - rowW[r];
        }
        stampAt(dl, font, px, ImVec2(origin.x + ox + pos[i].x, origin.y + pos[i].y), labels[i]);
    }
    ImGui::PopClipRect();
    ImGui::Dummy(ImVec2(0.f, h));
}

}