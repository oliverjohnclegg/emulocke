#include "ui/TrackerStatus.hpp"

#include "ui/Theme.hpp"
#include "ui/Tracker.hpp"

#include <imgui.h>

namespace emulocke {
namespace {

bool statusCell(const char* id, const char* tip) {
    const bool hit = ImGui::InvisibleButton(id, ImVec2(kTrackerStatus, kTrackerStatus));
    const ImVec2 a = ImGui::GetItemRectMin();
    const ImVec2 b = ImGui::GetItemRectMax();
    ImGui::GetWindowDrawList()->AddRect(a, b, ImGui::GetColorU32(kBorder));
    ImGui::SetItemTooltip("%s", tip);
    return hit;
}

const char* encounterTip(EncounterStatus status) {
    switch (status) {
        case EncounterStatus::Captured:
            return "Captured";
        case EncounterStatus::Dead:
            return "Dead";
        case EncounterStatus::Missed:
            return "Missed";
        case EncounterStatus::Traded:
            return "Traded";
        case EncounterStatus::Empty:
            return "Empty";
    }
    return "Empty";
}

void paintEncounterGlyph(EncounterStatus status, ImVec2 a, ImVec2 b) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImVec2 c((a.x + b.x) * 0.5f, (a.y + b.y) * 0.5f);
    const ImU32 ink = ImGui::GetColorU32(kMetal);
    const ImU32 mute = ImGui::GetColorU32(kDisabled);
    switch (status) {
        case EncounterStatus::Captured:
            dl->AddCircle(c, 5.f, ink, 12, 1.2f);
            dl->AddCircleFilled(c, 1.6f, ink, 8);
            break;
        case EncounterStatus::Dead:
            dl->AddLine(ImVec2(a.x + 5.f, a.y + 5.f), ImVec2(b.x - 5.f, b.y - 5.f), kPaused, 1.4f);
            dl->AddLine(ImVec2(b.x - 5.f, a.y + 5.f), ImVec2(a.x + 5.f, b.y - 5.f), kPaused, 1.4f);
            break;
        case EncounterStatus::Missed:
            dl->AddCircle(c, 5.f, mute, 12, 1.2f);
            dl->AddLine(ImVec2(a.x + 5.f, b.y - 5.f), ImVec2(b.x - 5.f, a.y + 5.f), mute, 1.2f);
            break;
        case EncounterStatus::Traded:
            dl->AddLine(ImVec2(a.x + 4.f, c.y - 3.f), ImVec2(b.x - 4.f, c.y - 3.f), ink, 1.2f);
            dl->AddLine(ImVec2(b.x - 8.f, c.y - 6.f), ImVec2(b.x - 4.f, c.y - 3.f), ink, 1.2f);
            dl->AddLine(ImVec2(b.x - 8.f, c.y), ImVec2(b.x - 4.f, c.y - 3.f), ink, 1.2f);
            dl->AddLine(ImVec2(b.x - 4.f, c.y + 3.f), ImVec2(a.x + 4.f, c.y + 3.f), ink, 1.2f);
            dl->AddLine(ImVec2(a.x + 8.f, c.y), ImVec2(a.x + 4.f, c.y + 3.f), ink, 1.2f);
            dl->AddLine(ImVec2(a.x + 8.f, c.y + 6.f), ImVec2(a.x + 4.f, c.y + 3.f), ink, 1.2f);
            break;
        case EncounterStatus::Empty:
            break;
    }
}

}  // namespace

bool drawEncounterStatus(EncounterStatus status) {
    const bool hit = statusCell("stat", encounterTip(status));
    paintEncounterGlyph(status, ImGui::GetItemRectMin(), ImGui::GetItemRectMax());
    return hit;
}

bool drawBossStatus(bool defeated) {
    const bool hit = statusCell("win", defeated ? "Defeated" : "Undefeated");
    if (defeated) {
        const ImVec2 a = ImGui::GetItemRectMin();
        const ImVec2 b = ImGui::GetItemRectMax();
        ImDrawList* dl = ImGui::GetWindowDrawList();
        const ImU32 ink = ImGui::GetColorU32(kMetal);
        dl->AddLine(ImVec2(a.x + 4.f, a.y + 9.f), ImVec2(a.x + 8.f, b.y - 5.f), ink, 1.4f);
        dl->AddLine(ImVec2(a.x + 8.f, b.y - 5.f), ImVec2(b.x - 4.f, a.y + 5.f), ink, 1.4f);
    }
    return hit;
}

}
