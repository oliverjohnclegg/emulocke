#include "ui/TrackerMarks.hpp"

#include "ui/Theme.hpp"
#include "ui/Tracker.hpp"
#include "ui/TrackerKindTip.hpp"

#include <cstdio>
#include <imgui.h>

namespace emulocke {

void paintTrackerRow(float w, bool focus) {
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->AddRectFilled(origin, ImVec2(origin.x + w, origin.y + kTrackerRowH),
        ImGui::GetColorU32(focus ? kHeaderHover : kScreenWell));
    dl->AddRect(origin, ImVec2(origin.x + w, origin.y + kTrackerRowH), ImGui::GetColorU32(kBorder));
    if (focus) {
        dl->AddRect(origin, ImVec2(origin.x + w, origin.y + kTrackerRowH), ImGui::GetColorU32(kMetal), 0.f, 0,
            1.8f);
    }
}

void drawKindMark(const TrackerStop& stop) {
    const ImVec2 p = ImGui::GetCursorScreenPos();
    ImGui::InvisibleButton("kind", ImVec2(kTrackerKind, kTrackerKindH));
    ImDrawList* dl = ImGui::GetWindowDrawList();
    if (stop.kind != TrackerStopKind::Boss) {
        const ImVec2 c(p.x + kTrackerKind * 0.5f, p.y + kTrackerKindH * 0.5f);
        dl->AddCircle(c, 3.6f, ImGui::GetColorU32(kMetal), 12, 1.2f);
        ImGui::SetItemTooltip("Encounter");
        return;
    }
    const ImVec2 q(p.x + kTrackerKind, p.y + kTrackerKindH);
    dl->AddRectFilled(p, q, ImGui::GetColorU32(kButton));
    dl->AddRect(p, q, ImGui::GetColorU32(kBorder));
    const int n = stop.fieldCount >= 1 ? stop.fieldCount : 1;
    char lab[8];
    std::snprintf(lab, sizeof(lab), "%dx", n);
    const ImVec2 sz = ImGui::CalcTextSize(lab);
    dl->AddText(ImVec2(p.x + (kTrackerKind - sz.x) * 0.5f, p.y + (kTrackerKindH - sz.y) * 0.5f - 1.f),
                ImGui::GetColorU32(kMetal), lab);
    if (stop.weather && stop.weather[0]) {
        const float y = q.y - 3.f;
        dl->AddLine(ImVec2(p.x + 3.f, y), ImVec2(q.x - 3.f, y), battleWeatherTint(stop.weather), 1.4f);
    }
    char tip[512];
    fillBattleTip(stop, tip, sizeof(tip));
    if (ImGui::BeginItemTooltip()) {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 28.f);
        ImGui::TextUnformatted(tip);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void drawStruckLabel(const char* text, bool struck) {
    if (struck) {
        ImGui::PushStyleColor(ImGuiCol_Text, kDisabled);
    }
    ImGui::TextUnformatted(text);
    if (struck) {
        const ImVec2 a = ImGui::GetItemRectMin();
        const ImVec2 b = ImGui::GetItemRectMax();
        const float y = (a.y + b.y) * 0.5f;
        ImGui::GetWindowDrawList()->AddLine(ImVec2(a.x, y), ImVec2(b.x, y), ImGui::GetColorU32(kDisabled));
        ImGui::PopStyleColor();
    }
}

void drawBoxSprite(SDL_Texture* tex, const char* tip, bool grey) {
    const ImVec4 tint = grey ? ImVec4(0.46f, 0.44f, 0.41f, 1.f) : ImVec4(1.f, 1.f, 1.f, 1.f);
    if (tex) {
        ImGui::ImageWithBg(tex, ImVec2(static_cast<float>(kBoxSpriteW), static_cast<float>(kBoxSpriteH)),
                            ImVec2(0.f, 0.f), ImVec2(1.f, 1.f), ImVec4(0, 0, 0, 0), tint);
    } else {
        ImGui::Dummy(ImVec2(static_cast<float>(kBoxSpriteW), static_cast<float>(kBoxSpriteH)));
    }
    if (tip && tip[0]) {
        ImGui::SetItemTooltip("%s", tip);
    }
}

}
