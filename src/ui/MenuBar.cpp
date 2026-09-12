#include "ui/Shell.hpp"

#include "application/Application.hpp"

#include <imgui.h>
#include <SDL3/SDL.h>

namespace emulocke {

void drawMenuBar(Application& app) {
    if (ImFont* display = app.displayFont()) {
        ImGui::PushFont(display);
    }
    if (!ImGui::BeginMenuBar()) {
        if (app.displayFont()) {
            ImGui::PopFont();
        }
        return;
    }
    if (ImGui::BeginMenu("File")) {
        if (ImFont* body = app.bodyFont()) {
            ImGui::PushFont(body);
        }
        if (ImGui::MenuItem("Open ROM...")) {
            app.requestOpenRom();
        }
        if (ImGui::MenuItem("Close", nullptr, false, app.session() != nullptr)) {
            app.closeRom();
        }
        if (ImGui::MenuItem("Exit")) {
            SDL_Event quit{};
            quit.type = SDL_EVENT_QUIT;
            SDL_PushEvent(&quit);
        }
        if (app.bodyFont()) {
            ImGui::PopFont();
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Emulation")) {
        if (ImFont* body = app.bodyFont()) {
            ImGui::PushFont(body);
        }
        const bool has = app.session() != nullptr;
        if (ImGui::MenuItem(app.paused() ? "Resume" : "Pause", nullptr, false, has)) {
            app.pauseToggle();
        }
        if (ImGui::MenuItem("Reset", nullptr, false, has)) {
            app.resetSession();
        }
        if (app.bodyFont()) {
            ImGui::PopFont();
        }
        ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
    if (app.displayFont()) {
        ImGui::PopFont();
    }
}

}
