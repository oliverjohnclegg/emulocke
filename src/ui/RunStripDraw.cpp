#include "ui/RunStripDraw.hpp"

#include "adapter/HackSpecies.hpp"
#include "application/Application.hpp"
#include "cart/GameIndex.hpp"
#include "poke/SpriteIndex.hpp"
#include "ui/MediaFetch.hpp"
#include "ui/PngCache.hpp"
#include "ui/Theme.hpp"

#include <cstring>

#include <imgui.h>
#include <algorithm>
#include <string>

namespace emulocke {
namespace {

constexpr float kSockW = 40.f;
constexpr float kSockH = 30.f;
constexpr float kSockInset = 2.f;

void well(ImDrawList* dl, ImVec2 a, ImVec2 b) {
    dl->AddRectFilled(a, b, ImGui::GetColorU32(kScreenWell));
    dl->AddRect(a, b, ImGui::GetColorU32(kBorder));
}

}  // namespace

void drawRunArt(Application& app, const CatalogTitle* title, ImVec2 p) {
    well(ImGui::GetWindowDrawList(), p, ImVec2(p.x + kRunArtW, p.y + kRunArtH));
    if (!title) {
        return;
    }
    const auto path = app.media().art(gameArtSlug(title->slug));
    if (!path) {
        return;
    }
    PngCache::drawNearest(app.pngs().get(*path).tex, p, ImVec2(kRunArtW, kRunArtH));
}

void drawRunParty(Application& app, const CatalogTitle* title, const Party& party, ImVec2 p) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    for (int i = 0; i < 6; ++i) {
        const ImVec2 a(p.x + i * (kSockW + 4.f), p.y);
        const ImVec2 b(a.x + kSockW, a.y + kSockH);
        well(dl, a, b);
        const Mon& mon = party.mons[static_cast<std::size_t>(i)];
        const SpeciesRef ref =
            title ? hackAwareSpecies(title->ext, mon.species, nullptr,
                                     std::strcmp(title->uuid, kUnboundUuid) == 0)
                  : app.species(mon.species);
        const char* slug = ref.slug && ref.slug[0] ? ref.slug : nullptr;
        const std::string fallback = slug ? std::string{} : speciesSlug(mon.speciesName);
        if (!slug) {
            slug = fallback.c_str();
        }
        if (!slug || !slug[0]) {
            continue;
        }
        const auto path = app.media().box(slug);
        if (!path) {
            continue;
        }
        const CachedPng png = app.pngs().get(*path);
        if (!png.tex || png.cropW <= 0 || png.cropH <= 0) {
            continue;
        }
        const float maxW = kSockW - kSockInset * 2.f;
        const float maxH = kSockH - kSockInset * 2.f;
        const float scale =
            std::min(maxW / static_cast<float>(png.cropW), maxH / static_cast<float>(png.cropH));
        const ImVec2 sz(static_cast<float>(png.cropW) * scale, static_cast<float>(png.cropH) * scale);
        const ImVec2 pos(a.x + (kSockW - sz.x) * 0.5f, a.y + (kSockH - sz.y) * 0.5f);
        const ImVec2 uv0(static_cast<float>(png.cropX) / static_cast<float>(png.w),
            static_cast<float>(png.cropY) / static_cast<float>(png.h));
        const ImVec2 uv1(static_cast<float>(png.cropX + png.cropW) / static_cast<float>(png.w),
            static_cast<float>(png.cropY + png.cropH) / static_cast<float>(png.h));
        PngCache::drawNearest(png.tex, pos, sz, uv0, uv1);
    }
}

}
