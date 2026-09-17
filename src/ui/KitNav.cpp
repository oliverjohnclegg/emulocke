#include "ui/KitNav.hpp"

#include "application/Application.hpp"
#include "ui/KitKeys.hpp"
#include "ui/Suite.hpp"

#include <imgui.h>
#include <imgui_internal.h>

namespace emulocke {

bool kitPopupOpen() {
    return ImGui::IsPopupOpen("NEW RUN") || ImGui::IsPopupOpen("START NEW ATTEMPT") ||
        ImGui::IsPopupOpen("DELETE RUN") || ImGui::IsPopupOpen("ADD") ||
        ImGui::IsPopupOpen("Controls") || ImGui::IsPopupOpen("About") ||
        ImGui::IsPopupOpen("LOADING RUN");
}

bool kitModalHold() {
    return ImGui::IsWindowAppearing();
}

bool kitNavHome(Application& app) {
    if (kitPopupOpen()) {
        return false;
    }
    if (app.session() || app.previewTracker() || app.previewCalc()) {
        return false;
    }
    return true;
}

bool kitNavSuite(Application& app, KitTab tab) {
    if (kitPopupOpen()) {
        return false;
    }
    if (!app.session() && !app.previewTracker() && !app.previewCalc()) {
        return false;
    }
    return app.kitFocus().tab == tab;
}

void handleKitHost(Application& app) {
    const KitFrame& kit = app.kit();
    KitFocus& focus = app.kitFocus();
    if (kit.search) {
        focus.focusSearch = true;
    }
    if (ImGui::GetIO().WantTextInput) {
        if (kit.pause) {
            ImGui::ClearActiveID();
        }
        return;
    }
    if (kitPopupOpen()) {
        return;
    }
    if (kit.pane) {
        app.setRightPane(!app.prefs().rightPane);
    }
    if (kit.tab) {
        bool allowCheats = true;
        if (const Run* run = app.runStore().find(app.activeRunId())) {
            allowCheats = run->allowCheats;
        }
        const SuiteTabs tabs =
            suiteTabs(app.activeRunId(), app.previewTracker(), app.previewCalc(), allowCheats);
        const bool ok = (kit.tab == 1 && tabs.tracker) || (kit.tab == 2 && tabs.pokemon) ||
            (kit.tab == 3 && tabs.calculator) || (kit.tab == 4 && tabs.cheats) ||
            (kit.tab == 5 && tabs.logs);
        if (ok) {
            app.setRightPane(true);
            focus.pendingTab = kit.tab;
            focus.tab = static_cast<KitTab>(kit.tab);
        }
    }
    if (kit.pause && app.session()) {
        app.pauseToggle();
    }
}

}
