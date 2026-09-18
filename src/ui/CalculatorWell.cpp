#include "ui/CalculatorWell.hpp"

#include "application/Application.hpp"
#include "ui/MediaFetch.hpp"
#include "ui/PngCache.hpp"
#include "ui/Theme.hpp"

#include <algorithm>
#include <cstdio>

namespace emulocke {

const char* calcStageMark(const int8_t stages[8]) {
    if (!stages) {
        return "";
    }
    bool up = false;
    bool down = false;
    for (int i = 1; i < 8; ++i) {
        if (stages[i] > 0) {
            up = true;
        }
        if (stages[i] < 0) {
            down = true;
        }
    }
    if (up && down) {
        return "\xC2\xB1";
    }
    if (up) {
        return "+";
    }
    if (down) {
        return "-";
    }
    return "";
}

void drawCalcWell(Application& app, ImVec2 a, const char* slug, bool dim, bool selected, bool next,
    int level, const char* stage) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImVec2 b(a.x + kCalcWell, a.y + kCalcWell);
    dl->AddRectFilled(a, b, ImGui::GetColorU32(kScreenWell));
    if (next && !selected) {
        dl->AddRectFilled(a, ImVec2(a.x + 2.f, b.y), ImGui::GetColorU32(kMetal));
    }
    dl->AddRect(a, b, selected ? ImGui::GetColorU32(kMetal) : ImGui::GetColorU32(kBorder));
    if (slug && slug[0]) {
        if (const auto path = app.media().box(slug)) {
            const CachedPng png = app.pngs().get(*path);
            if (png.tex && png.cropW > 0) {
                const float max = kCalcWell - 4.f;
                const float scale = std::min(max / png.cropW, max / png.cropH);
                const ImVec2 sz(png.cropW * scale, png.cropH * scale);
                const ImVec2 pos(a.x + (kCalcWell - sz.x) * 0.5f, a.y + (kCalcWell - sz.y) * 0.5f);
                const ImVec2 uv0(png.cropX / static_cast<float>(png.w),
                    png.cropY / static_cast<float>(png.h));
                const ImVec2 uv1((png.cropX + png.cropW) / static_cast<float>(png.w),
                    (png.cropY + png.cropH) / static_cast<float>(png.h));
                const ImU32 col = dim ? IM_COL32(255, 255, 255, 70) : IM_COL32(255, 255, 255, 255);
                dl->AddImage(png.tex, pos, ImVec2(pos.x + sz.x, pos.y + sz.y), uv0, uv1, col);
            }
        }
    }
    if (stage && stage[0]) {
        const ImVec2 ts = ImGui::CalcTextSize(stage);
        dl->AddText(ImVec2(b.x - ts.x - 2.f, b.y - ts.y - 1.f), ImGui::GetColorU32(kMetal), stage);
    }
    if (level > 0) {
        char lv[8];
        std::snprintf(lv, sizeof lv, "%d", level);
        dl->AddText(ImVec2(b.x + 3.f, a.y + (kCalcWell - ImGui::GetFontSize()) * 0.5f),
            ImGui::GetColorU32(kDisabled), lv);
    }
}

}
