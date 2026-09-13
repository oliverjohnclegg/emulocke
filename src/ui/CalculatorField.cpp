#include "ui/CalculatorDraw.hpp"

#include "calc/Build.hpp"

#include <imgui.h>

namespace emulocke {
namespace {

void weatherBar(FieldState& f) {
    static const char* k[] = {"None", "Sun", "Rain", "Sand", "Hail"};
    static const Weather v[] = {
        Weather::None, Weather::Sun, Weather::Rain, Weather::Sand, Weather::Hail};
    for (int i = 0; i < 5; ++i) {
        if (i) {
            ImGui::SameLine();
        }
        if (calcChip(k[i], f.weather == v[i])) {
            f.weather = v[i];
        }
    }
    ImGui::Dummy(ImVec2(0, 4));
    if (calcChip("Singles", !f.doubles)) {
        f.doubles = false;
    }
    ImGui::SameLine();
    if (calcChip("Doubles", f.doubles)) {
        f.doubles = true;
    }
}

void sideToggle(const char* label, bool& v) {
    if (calcChip(label, v, -1.f)) {
        v = !v;
    }
}

void sideCol(const char* id, SideMods& s) {
    ImGui::PushID(id);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5.f, 3.f));
    sideToggle("Reflect", s.reflect);
    sideToggle("Light Screen", s.lightScreen);
    sideToggle("Protect", s.protect);
    sideToggle("Leech Seed", s.seeded);
    sideToggle("Foresight", s.foresight);
    sideToggle("Helping Hand", s.helpingHand);
    sideToggle("Switching Out", s.switchingOut);
    ImGui::PopStyleVar();
    ImGui::PopID();
}

}  // namespace

void drawCalcField(Application&, CalcSession& session) {
    session.seedWeather(fieldFromSnap(session.snap()).weather);
    ImGui::Dummy(ImVec2(0, 6));
    weatherBar(session.fieldState());
    ImGui::Dummy(ImVec2(0, 6));
    const float w = ImGui::GetContentRegionAvail().x;
    const float gap = 8.f;
    const float col = (w - gap) * 0.5f;
    ImGui::BeginChild("calc-fo", ImVec2(col, 0), ImGuiChildFlags_AutoResizeY);
    sideCol("o", session.fieldState().ours);
    ImGui::EndChild();
    ImGui::SameLine(0, gap);
    ImGui::BeginChild("calc-ft", ImVec2(col, 0), ImGuiChildFlags_AutoResizeY);
    sideCol("t", session.fieldState().theirs);
    ImGui::EndChild();
}

}
