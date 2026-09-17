#include "ui/Suite.hpp"

#include "application/Application.hpp"
#include "ui/FieldLog.hpp"
#include "ui/Calculator.hpp"
#include "ui/Cheats.hpp"
#include "ui/KitFocus.hpp"
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

ImGuiTabItemFlags kitTab(Application& app, int n, ImGuiTabItemFlags extra = 0) {
    if (app.kitFocus().pendingTab == n) {
        extra |= ImGuiTabItemFlags_SetSelected;
    }
    return extra;
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
    bool allowCheats = true;
    if (const Run* run = app.runStore().find(app.activeRunId())) {
        allowCheats = run->allowCheats;
    }
    const SuiteTabs tabs = suiteTabs(app.activeRunId(), app.previewTracker(), app.previewCalc(), allowCheats);
    if (ImGui::BeginTabBar("suite-tabs", ImGuiTabBarFlags_DrawSelectedOverline | ImGuiTabBarFlags_NoTooltip)) {
        if (tabs.tracker && ImGui::BeginTabItem("Tracker", nullptr, kitTab(app, 1))) {
            app.kitFocus().tab = KitTab::Tracker;
            suitePane("tracker", drawTracker, app);
            ImGui::EndTabItem();
        }
        if (tabs.pokemon && ImGui::BeginTabItem("Pokémon", nullptr, kitTab(app, 2))) {
            app.kitFocus().tab = KitTab::Pokemon;
            suitePane("pokemon", drawPokemon, app);
            ImGui::EndTabItem();
        }
        if (tabs.calculator &&
            ImGui::BeginTabItem("Calculator", nullptr,
                kitTab(app, 3, app.consumePreviewCalcSelect() ? ImGuiTabItemFlags_SetSelected : 0))) {
            app.kitFocus().tab = KitTab::Calculator;
            suitePane("calc", drawCalculator, app);
            ImGui::EndTabItem();
        }
        if (tabs.cheats && ImGui::BeginTabItem("Cheats", nullptr, kitTab(app, 4))) {
            app.kitFocus().tab = KitTab::Cheats;
            suitePane("cheats", drawCheats, app);
            ImGui::EndTabItem();
        }
        const ImGuiTabItemFlags logFlags =
            (tabs.tracker || tabs.pokemon || tabs.calculator || tabs.cheats) ? 0 : ImGuiTabItemFlags_SetSelected;
        if (tabs.logs && ImGui::BeginTabItem("Logs", nullptr, kitTab(app, 5, logFlags))) {
            app.kitFocus().tab = KitTab::Logs;
            suitePane("logs", drawFieldLog, app);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    app.kitFocus().pendingTab = 0;
    ImGui::PopStyleVar();
    if (app.displayFont()) {
        ImGui::PopFont();
    }
    ImGui::EndChild();
}

}
