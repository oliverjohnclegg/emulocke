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
    if (calcChip(label, v, ImGui::GetContentRegionAvail().x)) {
        v = !v;
    }
}

void sideCol(const char* id, SideMods& s) {
    ImGui::PushID(id);
    sideToggle("Reflect", s.reflect);
    sideToggle("Light Screen", s.lightScreen);
    sideToggle("Protect", s.protect);
    sideToggle("Leech Seed", s.seeded);
    sideToggle("Foresight", s.foresight);
    sideToggle("Helping Hand", s.helpingHand);
    sideToggle("Switching Out", s.switchingOut);
    ImGui::PopID();
}

}  // namespace

void drawCalcField(Application&, CalcSession& session) {
    session.seedWeather(fieldFromSnap(session.snap()).weather);
    ImGui::Dummy(ImVec2(0, 6));
    weatherBar(session.fieldState());
    ImGui::Dummy(ImVec2(0, 6));
    if (!ImGui::BeginTable("calc-field", 2, ImGuiTableFlags_NoPadInnerX)) {
        return;
    }
    ImGui::TableSetupColumn("o", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableSetupColumn("t", ImGuiTableColumnFlags_WidthStretch);
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    sideCol("o", session.fieldState().ours);
    ImGui::TableSetColumnIndex(1);
    sideCol("t", session.fieldState().theirs);
    ImGui::EndTable();
}

}
