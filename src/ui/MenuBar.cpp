#include "ui/Shell.hpp"

#include "application/Application.hpp"

#include <imgui.h>
#include <SDL3/SDL.h>

namespace emulocke {
namespace {

void scaleItem(Application& app, const char* label, int scale) {
    if (ImGui::MenuItem(label, nullptr, app.screenScale() == scale)) {
        app.setScreenScale(scale);
    }
}

void withBody(Application& app, auto&& draw) {
    if (ImFont* body = app.bodyFont()) {
        ImGui::PushFont(body);
    }
    draw();
    if (app.bodyFont()) {
        ImGui::PopFont();
    }
}

}  // namespace

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
        withBody(app, [&] {
            if (ImGui::MenuItem("Start New Attempt", nullptr, false, !app.activeRunId().empty())) {
                app.queueNewAttempt(app.activeRunId());
            }
            if (ImGui::MenuItem("New Run...")) {
                app.requestNewRun();
            }
            if (ImGui::MenuItem("Load Run...", nullptr, false, !app.runStore().runs().empty())) {
                app.requestLoadRun();
            }
            if (ImGui::MenuItem("Import Game...")) {
                app.requestImportGame();
            }
            if (ImGui::MenuItem("Close Run", nullptr, false, app.session() != nullptr)) {
                app.closeRun();
            }
            if (ImGui::MenuItem("Exit")) {
                SDL_Event quit{};
                quit.type = SDL_EVENT_QUIT;
                SDL_PushEvent(&quit);
            }
        });
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Emulation")) {
        withBody(app, [&] {
            const bool has = app.session() != nullptr;
            if (ImGui::MenuItem(app.paused() ? "Resume" : "Pause", nullptr, false, has)) {
                app.pauseToggle();
            }
            if (ImGui::MenuItem("Reset", nullptr, false, has)) {
                app.resetSession();
            }
        });
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("View")) {
        withBody(app, [&] {
            if (ImGui::MenuItem("Fullscreen", nullptr, app.prefs().fullscreen)) {
                app.setFullscreen(!app.prefs().fullscreen);
            }
            if (ImGui::BeginMenu("Screen Scale")) {
                scaleItem(app, "Fit", 0);
                scaleItem(app, "1x", 1);
                scaleItem(app, "2x", 2);
                scaleItem(app, "3x", 3);
                scaleItem(app, "4x", 4);
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Restore Default Window")) {
                app.restoreDefaultWindow();
            }
        });
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Audio")) {
        withBody(app, [&] {
            if (ImGui::MenuItem("Mute", nullptr, app.prefs().mute)) {
                app.setMuted(!app.prefs().mute);
            }
            int volume = app.prefs().volume;
            ImGui::TextUnformatted("Volume");
            ImGui::SetNextItemWidth(168.f);
            if (ImGui::SliderInt("##volume", &volume, 0, 100, "%d")) {
                app.setVolume(volume);
            }
        });
        ImGui::EndMenu();
    }
    bool openControls = false;
    bool openAbout = false;
    if (ImGui::BeginMenu("Help")) {
        withBody(app, [&] {
            if (ImGui::MenuItem("Controls")) {
                openControls = true;
            }
            if (ImGui::MenuItem("About Emulocke")) {
                openAbout = true;
            }
        });
        ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
    if (app.displayFont()) {
        ImGui::PopFont();
    }
    if (openControls) {
        ImGui::OpenPopup("Controls");
    }
    if (openAbout) {
        ImGui::OpenPopup("About");
    }
    drawHelpPopups(app);
}

}
