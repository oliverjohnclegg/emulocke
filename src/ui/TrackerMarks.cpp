#include "ui/TrackerMarks.hpp"

#include "ui/Theme.hpp"
#include "ui/Tracker.hpp"

#include <imgui.h>

namespace emulocke {

void paintTrackerRow(float w) {
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->AddRectFilled(origin, ImVec2(origin.x + w, origin.y + kTrackerRowH), ImGui::GetColorU32(kScreenWell));
    dl->AddRect(origin, ImVec2(origin.x + w, origin.y + kTrackerRowH), ImGui::GetColorU32(kBorder));
}

void drawKindMark(TrackerStopKind kind) {
    const ImVec2 p = ImGui::GetCursorScreenPos();
    ImGui::InvisibleButton("kind", ImVec2(kTrackerKind, kTrackerKind));
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImVec2 c(p.x + kTrackerKind * 0.5f, p.y + kTrackerKind * 0.5f);
    if (kind == TrackerStopKind::Boss) {
        dl->AddTriangleFilled(ImVec2(c.x, p.y + 1.f), ImVec2(p.x + kTrackerKind - 1.f, p.y + kTrackerKind - 1.f),
                               ImVec2(p.x + 1.f, p.y + kTrackerKind - 1.f), kPaused);
        ImGui::SetItemTooltip("Boss");
    } else {
        dl->AddCircle(c, 3.6f, ImGui::GetColorU32(kMetal), 12, 1.2f);
        ImGui::SetItemTooltip("Encounter");
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
