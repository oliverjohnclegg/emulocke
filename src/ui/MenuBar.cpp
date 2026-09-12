#include "ui/Shell.hpp"

#include "application/Application.hpp"

#include <imgui.h>
#include <SDL3/SDL.h>

namespace emulocke {

void drawMenuBar(Application& app) {
    if (!ImGui::BeginMenuBar()) {
        return;
    }
    if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Start New Attempt", nullptr, false, !app.activeRunId().empty())) {
            app.queueNewAttempt(app.activeRunId());
        }
        if (ImGui::MenuItem("New Run...")) {
            app.requestNewRun();
        }
        if (ImGui::MenuItem("Load Run...", nullptr, false, !app.runStore().runs().empty())) {
            app.requestLoadRun();
        }
        if (ImGui::MenuItem("Close Run", nullptr, false, app.session() != nullptr)) {
            app.closeRun();
        }
        if (ImGui::MenuItem("Exit")) {
            SDL_Event quit{};
            quit.type = SDL_EVENT_QUIT;
            SDL_PushEvent(&quit);
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Emulation")) {
        const bool has = app.session() != nullptr;
        if (ImGui::MenuItem(app.paused() ? "Resume" : "Pause", nullptr, false, has)) {
            app.pauseToggle();
        }
        if (ImGui::MenuItem("Reset", nullptr, false, has)) {
            app.resetSession();
        }
        ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
}

}