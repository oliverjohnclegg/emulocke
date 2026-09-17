#include "ui/CalculatorDraw.hpp"

#include "adapter/gen45/Names.hpp"
#include "application/Application.hpp"
#include "calc/Dex.hpp"
#include "poke/SpriteIndex.hpp"
#include "ui/MediaFetch.hpp"
#include "ui/PngCache.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <algorithm>
#include <cstdio>
#include <string>

namespace emulocke {
namespace {
constexpr float kWell = 36.f;

void spriteWell(Application& app, ImVec2 a, const char* slug, bool dim, bool selected, bool next,
    int level) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImVec2 b(a.x + kWell, a.y + kWell);
    dl->AddRectFilled(a, b, ImGui::GetColorU32(kScreenWell));
    if (next && !selected) {
        dl->AddRectFilled(a, ImVec2(a.x + 2.f, b.y), ImGui::GetColorU32(kMetal));
    }
    dl->AddRect(a, b, selected ? ImGui::GetColorU32(kMetal) : ImGui::GetColorU32(kBorder));
    if (slug && slug[0]) {
        if (const auto path = app.media().box(slug)) {
            const CachedPng png = app.pngs().get(*path);
            if (png.tex && png.cropW > 0) {
                const float max = kWell - 4.f;
                const float scale = std::min(max / png.cropW, max / png.cropH);
                const ImVec2 sz(png.cropW * scale, png.cropH * scale);
                const ImVec2 pos(a.x + (kWell - sz.x) * 0.5f, a.y + (kWell - sz.y) * 0.5f);
                const ImVec2 uv0(png.cropX / static_cast<float>(png.w),
                    png.cropY / static_cast<float>(png.h));
                const ImVec2 uv1((png.cropX + png.cropW) / static_cast<float>(png.w),
                    (png.cropY + png.cropH) / static_cast<float>(png.h));
                const ImU32 col = dim ? IM_COL32(255, 255, 255, 70) : IM_COL32(255, 255, 255, 255);
                dl->AddImage(png.tex, pos, ImVec2(pos.x + sz.x, pos.y + sz.y), uv0, uv1, col);
            }
        }
    }
    if (level > 0) {
        char lv[8];
        std::snprintf(lv, sizeof lv, "%d", level);
        dl->AddText(ImVec2(b.x + 3.f, a.y + (kWell - ImGui::GetFontSize()) * 0.5f),
            ImGui::GetColorU32(kDisabled), lv);
    }
}

}  // namespace

void drawCalcPartyRail(Application& app, CalcSession& session) {
    const GameSnapshot* snap = session.snap();
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    for (int i = 0; i < 6; ++i) {
        const Mon* mon = snap ? &snap->party.mons[static_cast<std::size_t>(i)] : nullptr;
        const std::string slug =
            mon && mon->species ? speciesSlug(mon->speciesName) : "";
        const bool dim = mon && mon->species && mon->hp == 0;
        const ImVec2 a(origin.x, origin.y + i * (kWell + 4.f));
        ImGui::SetCursorScreenPos(a);
        ImGui::PushID(i + 20);
        if (ImGui::InvisibleButton("p", ImVec2(kWell, kWell))) {
            session.lockParty(i);
        }
        ImGui::PopID();
        spriteWell(app, a, slug.c_str(), dim, i == session.partySlot(), false, 0);
    }
    ImGui::SetCursorScreenPos(ImVec2(origin.x, origin.y + 6 * (kWell + 4.f)));
    ImGui::Dummy(ImVec2(kWell, 1));
}

void drawCalcFoeRail(Application& app, CalcSession& session) {
    const CalcPack* pack = session.pack();
    const PackTrainer* t = session.trainer();
    if (!pack || !t) {
        return;
    }
    const int next = session.nextIn();
    int order[6];
    session.foeOrder(order);
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    for (int vis = 0; vis < 6; ++vis) {
        const int i = order[vis];
        const PackMon* mon = i >= 0 ? trainerMon(*pack, *t, i) : nullptr;
        const char* slug = "";
        if (mon) {
            if (pack->dmgGen == 4 || pack->dmgGen == 5) {
                slug = nationalSpeciesRef(mon->species).slug;
            } else if (const SpeciesRow* row = speciesById(mon->species)) {
                slug = row->slug;
            }
        }
        const ImVec2 a(origin.x, origin.y + vis * (kWell + 4.f));
        ImGui::SetCursorScreenPos(a);
        ImGui::PushID(i >= 0 ? i + 40 : vis + 40);
        if (mon && ImGui::InvisibleButton("f", ImVec2(kWell, kWell))) {
            session.lockFoe(i);
        }
        ImGui::PopID();
        spriteWell(app, a, slug, i >= 0 && session.fainted(i),
            i >= 0 && i == session.foeSlot(), i >= 0 && i == next, mon ? mon->level : 0);
    }
    ImGui::SetCursorScreenPos(ImVec2(origin.x, origin.y + 6 * (kWell + 4.f)));
    ImGui::Dummy(ImVec2(56.f, 1));
}

}