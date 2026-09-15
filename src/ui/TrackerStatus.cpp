#include "ui/TrackerStatus.hpp"

#include "ui/Theme.hpp"
#include "ui/Tracker.hpp"

#include <cstdio>
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

bool drawBossStatus(bool defeated, uint8_t cap) {
    char tip[24];
    if (defeated) {
        std::snprintf(tip, sizeof tip, "Defeated");
    } else if (cap) {
        std::snprintf(tip, sizeof tip, "Level cap %u", cap);
    } else {
        std::snprintf(tip, sizeof tip, "Undefeated");
    }
    const bool hit = statusCell("win", tip);
    const ImVec2 a = ImGui::GetItemRectMin();
    const ImVec2 b = ImGui::GetItemRectMax();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImU32 ink = ImGui::GetColorU32(kMetal);
    if (defeated) {
        dl->AddLine(ImVec2(a.x + 4.f, a.y + 9.f), ImVec2(a.x + 8.f, b.y - 5.f), ink, 1.4f);
        dl->AddLine(ImVec2(a.x + 8.f, b.y - 5.f), ImVec2(b.x - 4.f, a.y + 5.f), ink, 1.4f);
    } else if (cap) {
        char lab[4];
        std::snprintf(lab, sizeof lab, "%u", cap);
        const float fs = cap >= 100 ? 9.f : 11.f;
        const ImVec2 ts = ImGui::GetFont()->CalcTextSizeA(fs, 1e9f, 0.f, lab);
        dl->AddText(ImGui::GetFont(), fs,
                    ImVec2(a.x + (b.x - a.x - ts.x) * 0.5f, a.y + (b.y - a.y - ts.y) * 0.5f - 0.5f), ink,
                    lab);
    }
    return hit;
}

}
