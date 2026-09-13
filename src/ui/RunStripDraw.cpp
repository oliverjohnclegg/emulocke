#include "ui/RunStripDraw.hpp"

#include "adapter/frlg/FrlgNames.hpp"
#include "application/Application.hpp"
#include "cart/GameIndex.hpp"
#include "poke/SpriteIndex.hpp"
#include "ui/MediaFetch.hpp"
#include "ui/PngCache.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <SDL3/SDL.h>
#include <algorithm>
#include <string>

namespace emulocke {
namespace {

constexpr float kSockW = 40.f;
constexpr float kSockH = 30.f;
const char* kBadgeName[] = {"Boulder", "Cascade", "Thunder", "Rainbow", "Soul", "Marsh", "Volcano", "Earth"};

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
    ImGui::SetCursorScreenPos(p);
    PngCache::drawNearest(app.pngs().get(*path), ImVec2(kRunArtW, kRunArtH));
}

void drawRunBadges(const Gyms& gyms, ImVec2 p) {
    if (gyms.slots == 0) {
        return;
    }
    ImDrawList* dl = ImGui::GetWindowDrawList();
    for (uint8_t i = 0; i < gyms.slots && i < 8; ++i) {
        const ImVec2 a(p.x + i * 10.f, p.y);
        const ImVec2 b(a.x + 8.f, a.y + 8.f);
        const bool on = (gyms.earned & (1u << i)) != 0;
        dl->AddRectFilled(a, b, ImGui::GetColorU32(on ? kMetal : kScreenWell));
        dl->AddRect(a, b, ImGui::GetColorU32(kBorder));
        const ImVec2 mouse = ImGui::GetMousePos();
        if (ImGui::IsWindowHovered() && mouse.x >= a.x && mouse.x < b.x && mouse.y >= a.y && mouse.y < b.y) {
            ImGui::SetTooltip("%s", kBadgeName[i]);
        }
    }
}

void drawRunParty(Application& app, const Party& party, ImVec2 p) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    for (int i = 0; i < 6; ++i) {
        const ImVec2 a(p.x + i * (kSockW + 4.f), p.y);
        const ImVec2 b(a.x + kSockW, a.y + kSockH);
        well(dl, a, b);
        const Mon& mon = party.mons[static_cast<std::size_t>(i)];
        const std::string slug = speciesSlug(frlgSpeciesName(mon.species));
        if (slug.empty()) {
            continue;
        }
        const auto path = app.media().box(slug);
        if (!path) {
            continue;
        }
        SDL_Texture* tex = app.pngs().get(*path);
        if (!tex) {
            continue;
        }
        float tw = 0.f;
        float th = 0.f;
        SDL_GetTextureSize(tex, &tw, &th);
        if (tw <= 0.f || th <= 0.f) {
            continue;
        }
        const float fit = std::min(kSockW / tw, kSockH / th);
        const ImVec2 sz(tw * fit, th * fit);
        ImGui::SetCursorScreenPos(ImVec2(a.x + (kSockW - sz.x) * 0.5f, a.y + (kSockH - sz.y) * 0.5f));
        PngCache::drawNearest(tex, sz);
    }
}

}
