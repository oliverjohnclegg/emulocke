#include "ui/PokemonDraw.hpp"

#include "poke/Showdown.hpp"
#include "poke/SpriteIndex.hpp"
#include "ui/BoxSprites.hpp"
#include "ui/Theme.hpp"
#include "ui/Tracker.hpp"
#include "ui/TrackerMarks.hpp"

#include <imgui.h>
#include <string>

namespace emulocke {
namespace {

uint32_t gCopiedPid{};
uint16_t gCopiedSpecies{};
double gCopiedAt{};

bool copied(const Mon& mon) {
    return mon.personality == gCopiedPid && mon.species == gCopiedSpecies &&
           ImGui::GetTime() - gCopiedAt < 1.25;
}

std::string slugOf(const MonView& view) {
    if (view.ref.slug && view.ref.slug[0]) {
        return view.ref.slug;
    }
    return view.mon ? speciesSlug(view.mon->speciesName) : std::string{};
}

}  // namespace

void drawMonWell(BoxSprites& sprites, const MonView& view, ImVec2 size, bool hpBar) {
    const ImVec2 a = ImGui::GetCursorScreenPos();
    const ImVec2 b(a.x + size.x, a.y + size.y);
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->AddRectFilled(a, b, ImGui::GetColorU32(kScreenWell));
    dl->AddRect(a, b, ImGui::GetColorU32(kBorder));
    if (view.mon) {
        const Mon& mon = *view.mon;
        const float spriteArea = hpBar ? size.y - 10.f : size.y;
        const float x = a.x + (size.x - kBoxSpriteW) * 0.5f;
        const float y = a.y + (spriteArea - kBoxSpriteH) * 0.5f;
        ImGui::SetCursorScreenPos(ImVec2(x, y));
        drawBoxSprite(sprites.get(slugOf(view)), nullptr, view.grey);
        if (hpBar && mon.maxHp) {
            const float x = a.x + 4.f;
            const float y = b.y - 7.f;
            const float w = size.x - 8.f;
            float t = static_cast<float>(mon.hp) / static_cast<float>(mon.maxHp);
            if (t < 0.f) {
                t = 0.f;
            }
            if (t > 1.f) {
                t = 1.f;
            }
            dl->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + 3.f), ImGui::GetColorU32(kFrame));
            const ImU32 fill = t <= 0.2f ? kPaused : ImGui::GetColorU32(kMetal);
            if (t > 0.f) {
                dl->AddRectFilled(ImVec2(x, y), ImVec2(x + w * t, y + 3.f), fill);
            }
        }
        if (copied(mon)) {
            dl->AddText(ImVec2(a.x + 3.f, a.y + 2.f), ImGui::GetColorU32(kMetal), "COPIED");
        }
    }
    ImGui::SetCursorScreenPos(a);
    ImGui::InvisibleButton("well", size);
    if (!view.mon) {
        return;
    }
    const Mon& mon = *view.mon;
    if (ImGui::IsItemHovered()) {
        if (ImGui::BeginTooltip()) {
            drawMonHover(view);
            ImGui::EndTooltip();
        }
    }
    if (ImGui::IsItemClicked()) {
        ImGui::SetClipboardText(exportSet(mon, view.ref, view.gen3).c_str());
        gCopiedPid = mon.personality;
        gCopiedSpecies = mon.species;
        gCopiedAt = ImGui::GetTime();
    }
}

}  // namespace emulocke
