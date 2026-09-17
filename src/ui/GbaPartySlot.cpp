#include "ui/GbaPartySlot.hpp"

#include "application/Application.hpp"
#include "poke/SpriteIndex.hpp"
#include "ui/MediaFetch.hpp"
#include "ui/PngCache.hpp"
#include "ui/Theme.hpp"

#include <algorithm>
#include <cmath>
#include <string>

namespace emulocke {
namespace {

void well(ImDrawList* dl, ImVec2 a, ImVec2 b) {
    dl->AddRectFilled(a, b, ImGui::GetColorU32(kScreenWell));
    dl->AddRect(a, b, ImGui::GetColorU32(kBorder));
}

float hopY(int slot, float wellH, bool live) {
    if (!live) {
        return 0.f;
    }
    const double cycle = 8.4 + slot * 1.55;
    const double phase = std::fmod(ImGui::GetTime() + slot * 1.9, cycle);
    constexpr double dur = 0.16;
    if (phase >= dur) {
        return 0.f;
    }
    const double u = phase / dur;
    return static_cast<float>(-wellH * 0.09 * 4.0 * u * (1.0 - u));
}

void hpTrack(ImDrawList* dl, ImVec2 a, ImVec2 b, const Mon& mon) {
    const bool faint = mon.species != 0 && mon.hp == 0;
    dl->AddRectFilled(a, b, ImGui::GetColorU32(kScreenWell));
    dl->AddRect(a, b, faint ? kPaused : ImGui::GetColorU32(kBorder));
    if (mon.species == 0 || mon.maxHp == 0 || mon.hp == 0) {
        return;
    }
    const float fill = std::clamp(static_cast<float>(mon.hp) / static_cast<float>(mon.maxHp), 0.f, 1.f);
    const float w = std::floor((b.x - a.x - 2.f) * fill);
    if (w <= 0.f) {
        return;
    }
    dl->AddRectFilled(ImVec2(a.x + 1.f, a.y + 1.f), ImVec2(a.x + 1.f + w, b.y - 1.f), ImGui::GetColorU32(kMetal));
}

void boxSprite(Application& app, const Mon& mon, ImVec2 a, ImVec2 b, float hop) {
    const SpeciesRef ref = app.species(mon.species);
    const char* slug = ref.slug && ref.slug[0] ? ref.slug : nullptr;
    const std::string fallback = slug ? std::string{} : speciesSlug(mon.speciesName);
    if (!slug) {
        slug = fallback.c_str();
    }
    if (!slug || !slug[0]) {
        return;
    }
    const auto path = app.media().box(slug);
    if (!path) {
        return;
    }
    const CachedPng png = app.pngs().get(*path);
    if (!png.tex || png.cropW <= 0 || png.cropH <= 0) {
        return;
    }
    const float maxW = (b.x - a.x - 4.f) * 0.8f;
    const float maxH = (b.y - a.y - 4.f) * 0.8f;
    const float scale = std::min(maxW / static_cast<float>(png.cropW), maxH / static_cast<float>(png.cropH));
    const ImVec2 sz(static_cast<float>(png.cropW) * scale, static_cast<float>(png.cropH) * scale);
    const ImVec2 pos(a.x + (b.x - a.x - sz.x) * 0.5f, a.y + (b.y - a.y - sz.y) * 0.5f + hop);
    const ImVec2 uv0(static_cast<float>(png.cropX) / static_cast<float>(png.w),
        static_cast<float>(png.cropY) / static_cast<float>(png.h));
    const ImVec2 uv1(static_cast<float>(png.cropX + png.cropW) / static_cast<float>(png.w),
        static_cast<float>(png.cropY + png.cropH) / static_cast<float>(png.h));
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->PushClipRect(a, b, true);
    PngCache::drawNearest(png.tex, pos, sz, uv0, uv1);
    dl->PopClipRect();
}

}  // namespace

void drawPartySlot(Application& app, const Mon& mon, int slot, ImVec2 wellA, ImVec2 wellB, ImVec2 trackA,
    ImVec2 trackB) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    well(dl, wellA, wellB);
    const bool live = mon.species != 0 && mon.hp > 0 && !app.paused();
    boxSprite(app, mon, wellA, wellB, hopY(slot, wellB.y - wellA.y, live));
    hpTrack(dl, trackA, trackB, mon);
}

}
