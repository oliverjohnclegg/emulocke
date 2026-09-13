#include "ui/Tracker.hpp"

#include "adapter/Species.hpp"
#include "ui/BoxSprites.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <algorithm>

namespace emulocke {
namespace {

void drawBox(SDL_Texture* tex) {
    const ImVec2 p = ImGui::GetCursorScreenPos();
    if (tex) {
        ImGui::Image(tex, ImVec2(kBoxSpriteW, kBoxSpriteH));
    } else {
        ImGui::Dummy(ImVec2(kBoxSpriteW, kBoxSpriteH));
    }
    ImGui::SetCursorScreenPos(ImVec2(p.x + kBoxSpriteW, p.y));
}

}  // namespace

void drawEncounterRow(const TrackerStop& stop, const SpeciesRef& species, BoxSprites& sprites, bool editing,
                       bool grabFocus, char* edit, int editCap, bool& commit, bool& startEdit) {
    const float w = ImGui::GetContentRegionAvail().x;
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->AddRectFilled(origin, ImVec2(origin.x + w, origin.y + kTrackerRowH), ImGui::GetColorU32(kScreenWell));
    dl->AddRect(origin, ImVec2(origin.x + w, origin.y + kTrackerRowH), ImGui::GetColorU32(kBorder));
    const float textY = origin.y + (kTrackerRowH - ImGui::GetTextLineHeight()) * 0.5f;
    const float spriteY = origin.y + (kTrackerRowH - kBoxSpriteH) * 0.5f;
    ImGui::SetCursorScreenPos(ImVec2(origin.x + 8.f, textY));
    ImGui::TextUnformatted(stop.name);
    const float nameW = 120.f;
    const float cluster = kBoxSpriteW + 6.f + nameW;
    ImGui::SetCursorScreenPos(ImVec2(origin.x + w - 8.f - cluster, spriteY));
    drawBox(sprites.get(species.slug ? species.slug : ""));
    ImGui::SameLine(0.f, 6.f);
    const ImVec2 namePos = ImGui::GetCursorScreenPos();
    ImGui::SetCursorScreenPos(ImVec2(namePos.x, textY));
    if (editing && edit) {
        ImGui::SetNextItemWidth(nameW);
        ImGui::PushID(stop.id);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4.f, 1.f));
        if (grabFocus) {
            ImGui::SetKeyboardFocusHere();
        }
        if (ImGui::InputText("##sp", edit, static_cast<size_t>(editCap),
                             ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll)) {
            commit = true;
        }
        if (ImGui::IsItemDeactivatedAfterEdit()) {
            commit = true;
        }
        ImGui::PopStyleVar();
        ImGui::PopID();
    } else {
        const char* label = (species.name && species.name[0]) ? species.name : "--";
        ImGui::PushID(stop.id);
        if (ImGui::Selectable(label, false, 0, ImVec2(nameW, kBoxSpriteH))) {
            startEdit = true;
        }
        ImGui::PopID();
    }
    ImGui::SetCursorScreenPos(ImVec2(origin.x, origin.y + kTrackerRowH));
}

void drawBossRow(const TrackerStop& stop, uint16_t starter, bool defeated, BoxSprites& sprites, bool& toggle) {
    const float w = ImGui::GetContentRegionAvail().x;
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->AddRectFilled(origin, ImVec2(origin.x + w, origin.y + kTrackerRowH), ImGui::GetColorU32(kScreenWell));
    dl->AddRect(origin, ImVec2(origin.x + w, origin.y + kTrackerRowH), ImGui::GetColorU32(kBorder));
    const float textY = origin.y + (kTrackerRowH - ImGui::GetTextLineHeight()) * 0.5f;
    const float spriteY = origin.y + (kTrackerRowH - kBoxSpriteH) * 0.5f;
    ImGui::SetCursorScreenPos(ImVec2(origin.x + 8.f, textY));
    ImGui::TextUnformatted(stop.name);
    ImGui::SameLine(0.f, 8.f);
    ImGui::TextDisabled("%s", stop.locale);
    const char* slugs[6]{};
    const int n = bossTeamSlugs(stop, starter, slugs, 6);
    const float mark = 18.f;
    float x = origin.x + w - 8.f - mark - 4.f - static_cast<float>(n) * (kBoxSpriteW + 2.f);
    x = std::max(x, origin.x + 140.f);
    ImGui::SetCursorScreenPos(ImVec2(x, spriteY));
    for (int i = 0; i < n; ++i) {
        drawBox(sprites.get(slugs[i] ? slugs[i] : ""));
        ImGui::SameLine(0.f, 2.f);
    }
    ImGui::SetCursorScreenPos(ImVec2(origin.x + w - 8.f - mark, origin.y + (kTrackerRowH - mark) * 0.5f));
    ImGui::PushID(stop.id);
    if (ImGui::InvisibleButton("win", ImVec2(mark, mark))) {
        toggle = true;
    }
    const ImVec2 a = ImGui::GetItemRectMin();
    const ImVec2 b = ImGui::GetItemRectMax();
    dl->AddRect(a, b, ImGui::GetColorU32(kBorder));
    if (defeated) {
        dl->AddRectFilled(ImVec2(a.x + 2.f, a.y + 2.f), ImVec2(b.x - 2.f, b.y - 2.f),
                           ImGui::GetColorU32(kMetal));
    }
    ImGui::PopID();
    ImGui::SetCursorScreenPos(ImVec2(origin.x, origin.y + kTrackerRowH));
}

}
