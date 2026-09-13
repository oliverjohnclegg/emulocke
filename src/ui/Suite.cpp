#include "ui/Suite.hpp"

#include "application/Application.hpp"
#include "ui/FieldLog.hpp"
#include "ui/Pokemon.hpp"
#include "ui/Theme.hpp"
#include "ui/Tracker.hpp"

#include <imgui.h>

namespace emulocke {
namespace {

void suitePane(const char* id, void (*draw)(Application&), Application& app) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, kPanel);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.f, 10.f));
    ImGui::BeginChild(id, ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_AlwaysUseWindowPadding);
    draw(app);
    ImGui::EndChild();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}

}  // namespace

void drawSuite(Application& app, ImVec2 size) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, kScreenWell);
    ImGui::BeginChild("suite", size, ImGuiChildFlags_Borders);
    ImGui::PopStyleColor();
    if (ImFont* display = app.displayFont()) {
        ImGui::PushFont(display);
    }
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(ImGui::GetStyle().ItemSpacing.x, 0.f));
    if (ImGui::BeginTabBar("suite-tabs", ImGuiTabBarFlags_DrawSelectedOverline | ImGuiTabBarFlags_NoTooltip)) {
        if (ImGui::BeginTabItem("Tracker")) {
            suitePane("tracker", drawTracker, app);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Pokémon")) {
            suitePane("pokemon", drawPokemon, app);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Logs")) {
            suitePane("logs", drawFieldLog, app);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::PopStyleVar();
    if (app.displayFont()) {
        ImGui::PopFont();
    }
    ImGui::EndChild();
}

}
