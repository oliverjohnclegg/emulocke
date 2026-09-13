#include "ui/CalculatorDraw.hpp"

#include "adapter/frlg/FrlgNames.hpp"
#include "application/Application.hpp"
#include "calc/Dex.hpp"
#include "poke/SpriteIndex.hpp"
#include "ui/MediaFetch.hpp"
#include "ui/PngCache.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <algorithm>
#include <string>

namespace emulocke {
namespace {

constexpr float kWell = 36.f;

void spriteWell(Application& app, ImVec2 a, const char* slug, bool dim, bool next) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImVec2 b(a.x + kWell, a.y + kWell);
    dl->AddRectFilled(a, b, ImGui::GetColorU32(kScreenWell));
    dl->AddRect(a, b, next ? ImGui::GetColorU32(kMetal) : ImGui::GetColorU32(kBorder));
    if (!slug || !slug[0]) {
        return;
    }
    const auto path = app.media().box(slug);
    if (!path) {
        return;
    }
    const CachedPng png = app.pngs().get(*path);
    if (!png.tex || png.cropW <= 0) {
        return;
    }
    const float max = kWell - 4.f;
    const float scale = std::min(max / png.cropW, max / png.cropH);
    const ImVec2 sz(png.cropW * scale, png.cropH * scale);
    const ImVec2 pos(a.x + (kWell - sz.x) * 0.5f, a.y + (kWell - sz.y) * 0.5f);
    const ImVec2 uv0(png.cropX / static_cast<float>(png.w), png.cropY / static_cast<float>(png.h));
    const ImVec2 uv1((png.cropX + png.cropW) / static_cast<float>(png.w),
        (png.cropY + png.cropH) / static_cast<float>(png.h));
    const ImU32 col = dim ? IM_COL32(255, 255, 255, 70) : IM_COL32(255, 255, 255, 255);
    dl->AddImage(png.tex, pos, ImVec2(pos.x + sz.x, pos.y + sz.y), uv0, uv1, col);
}

}  // namespace

void drawCalcStrips(Application& app, CalcSession& session) {
    const CalcPack* pack = session.pack();
    const PackTrainer* t = session.trainer();
    if (!pack || !t) {
        return;
    }
    ImGui::Dummy(ImVec2(0, 8));
    ImGui::TextUnformatted(t->name);
    ImGui::SameLine();
    ImGui::TextDisabled("%s  %s", t->cls, t->location);
    const int next = session.nextIn();
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    for (int i = 0; i < 6; ++i) {
        const PackMon* mon = trainerMon(*pack, *t, i);
        const SpeciesRow* row = mon ? speciesById(mon->species) : nullptr;
        spriteWell(app, ImVec2(origin.x + i * (kWell + 4.f), origin.y), row ? row->slug : "",
            session.fainted(i), i == next);
    }
    ImGui::Dummy(ImVec2(0, kWell + 8.f));
    const GameSnapshot* snap = session.snap();
    const ImVec2 party = ImGui::GetCursorScreenPos();
    for (int i = 0; i < 6; ++i) {
        const Mon* mon = snap ? &snap->party.mons[static_cast<std::size_t>(i)] : nullptr;
        const std::string slug = mon && mon->species ? speciesSlug(frlgSpeciesName(mon->species)) : "";
        const bool dim = mon && mon->species && mon->hp == 0;
        ImGui::SetCursorScreenPos(ImVec2(party.x + i * (kWell + 4.f), party.y));
        ImGui::PushID(i + 20);
        if (ImGui::InvisibleButton("p", ImVec2(kWell, kWell))) {
            session.lockParty(i);
        }
        ImGui::PopID();
        spriteWell(app, ImVec2(party.x + i * (kWell + 4.f), party.y), slug.c_str(), dim,
            i == session.partySlot());
    }
    ImGui::SetCursorScreenPos(ImVec2(party.x, party.y + kWell + 8.f));
}

}
