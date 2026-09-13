#include "ui/Tracker.hpp"

#include "adapter/Species.hpp"
#include "ui/BoxSprites.hpp"
#include "ui/TrackerMarks.hpp"
#include "ui/TrackerStatus.hpp"

#include <imgui.h>

namespace emulocke {
namespace {

void drawRowLeft(const TrackerStop& stop, bool struck) {
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    const float kindY = origin.y + (kTrackerRowH - kTrackerKind) * 0.5f;
    const float textY = origin.y + (kTrackerRowH - ImGui::GetTextLineHeight()) * 0.5f;
    ImGui::SetCursorScreenPos(ImVec2(origin.x + 6.f, kindY));
    drawKindMark(stop.kind);
    ImGui::SetCursorScreenPos(ImVec2(origin.x + 6.f + kTrackerKind + 6.f, textY));
    drawStruckLabel(stop.name, struck);
    if (stop.locale && stop.locale[0]) {
        ImGui::SameLine(0.f, 8.f);
        ImGui::TextDisabled("%s", stop.locale);
    }
}

}  // namespace

void drawEncounterRow(const TrackerStop& stop, EncounterStatus status, const SpeciesRef& species,
                      BoxSprites& sprites, bool& cycleStatus) {
    const float w = ImGui::GetContentRegionAvail().x;
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    paintTrackerRow(w);
    drawRowLeft(stop, status != EncounterStatus::Empty);
    const bool has = species.slug && species.slug[0];
    const float spriteY = origin.y + (kTrackerRowH - kBoxSpriteH) * 0.5f;
    const float statusX = origin.x + w - 8.f - kTrackerStatus;
    if (has) {
        const bool grey = status == EncounterStatus::Dead || status == EncounterStatus::Missed;
        const float x = statusX - 4.f - (kBoxSpriteW + 2.f);
        ImGui::SetCursorScreenPos(ImVec2(x, spriteY));
        drawBoxSprite(sprites.get(species.slug), species.name, grey);
    }
    ImGui::SetCursorScreenPos(ImVec2(statusX, origin.y + (kTrackerRowH - kTrackerStatus) * 0.5f));
    cycleStatus = drawEncounterStatus(status);
    ImGui::SetCursorScreenPos(ImVec2(origin.x, origin.y + kTrackerRowH));
}

void drawBossRow(const TrackerStop& stop, const char* const* slugs, const char* const* tips, int n, bool defeated,
                 BoxSprites& sprites, bool& toggle) {
    const float w = ImGui::GetContentRegionAvail().x;
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    paintTrackerRow(w);
    drawRowLeft(stop, defeated);
    const float spriteY = origin.y + (kTrackerRowH - kBoxSpriteH) * 0.5f;
    const float statusX = origin.x + w - 8.f - kTrackerStatus;
    if (n > 0) {
        const float x = statusX - 4.f - static_cast<float>(n) * (kBoxSpriteW + 2.f);
        ImGui::SetCursorScreenPos(ImVec2(x, spriteY));
        for (int i = 0; i < n; ++i) {
            ImGui::PushID(i);
            drawBoxSprite(sprites.get(slugs[i] ? slugs[i] : ""), tips[i] ? tips[i] : "", defeated);
            ImGui::PopID();
            if (i + 1 < n) {
                ImGui::SameLine(0.f, 2.f);
            }
        }
    }
    ImGui::SetCursorScreenPos(ImVec2(statusX, origin.y + (kTrackerRowH - kTrackerStatus) * 0.5f));
    toggle = drawBossStatus(defeated);
    ImGui::SetCursorScreenPos(ImVec2(origin.x, origin.y + kTrackerRowH));
}

}
