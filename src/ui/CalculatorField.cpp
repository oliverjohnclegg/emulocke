#include "ui/CalculatorDraw.hpp"

#include "calc/Build.hpp"

#include <imgui.h>

namespace emulocke {
namespace {

void weatherBar(FieldState& f) {
    static const char* k[] = {"None", "Sun", "Rain", "Sand", "Hail"};
    static const Weather v[] = {
        Weather::None, Weather::Sun, Weather::Rain, Weather::Sand, Weather::Hail};
    const float gap = ImGui::GetStyle().ItemSpacing.x;
    float row = 4.f * gap;
    for (int i = 0; i < 5; ++i) {
        row += calcChipWidth(k[i]);
    }
    calcAlignCenter(row);
    for (int i = 0; i < 5; ++i) {
        if (i) {
            ImGui::SameLine();
        }
        if (calcChip(k[i], f.weather == v[i])) {
            f.weather = v[i];
        }
    }
    ImGui::Dummy(ImVec2(0, 4));
    calcAlignCenter(calcChipWidth("Singles") + gap + calcChipWidth("Doubles"));
    if (calcChip("Singles", !f.doubles)) {
        f.doubles = false;
    }
    ImGui::SameLine();
    if (calcChip("Doubles", f.doubles)) {
        f.doubles = true;
    }
}

void sideToggle(const char* label, bool& v, float w) {
    if (calcChip(label, v, w)) {
        v = !v;
    }
}

void sideCol(const char* id, SideMods& s, float w) {
    ImGui::PushID(id);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5.f, 3.f));
    ImGui::BeginGroup();
    sideToggle("Reflect", s.reflect, w);
    sideToggle("Light Screen", s.lightScreen, w);
    sideToggle("Protect", s.protect, w);
    sideToggle("Leech Seed", s.seeded, w);
    sideToggle("Foresight", s.foresight, w);
    sideToggle("Helping Hand", s.helpingHand, w);
    sideToggle("Switching Out", s.switchingOut, w);
    ImGui::EndGroup();
    ImGui::PopStyleVar();
    ImGui::PopID();
}

}  // namespace

void drawCalcField(Application&, CalcSession& session) {
    session.seedWeather(fieldFromSnap(session.snap()).weather);
    ImGui::Dummy(ImVec2(0, 6));
    weatherBar(session.fieldState());
    ImGui::Dummy(ImVec2(0, 6));
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    const float avail = ImGui::GetContentRegionAvail().x;
    const float gap = 8.f;
    const float col = calcChipWidth("Switching Out");
    const float block = col * 2.f + gap;
    const float x0 = origin.x + (avail > block ? (avail - block) * 0.5f : 0.f);
    ImGui::SetCursorScreenPos(ImVec2(x0, origin.y));
    sideCol("o", session.fieldState().ours, col);
    ImGui::SetCursorScreenPos(ImVec2(x0 + col + gap, origin.y));
    sideCol("t", session.fieldState().theirs, col);
    const float h = ImGui::GetItemRectSize().y;
    ImGui::SetCursorScreenPos(ImVec2(origin.x, origin.y + h));
    ImGui::Dummy(ImVec2(avail, 0));
}

}
