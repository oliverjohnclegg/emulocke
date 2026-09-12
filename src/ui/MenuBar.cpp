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

}  // namespace

void drawMenuBar(Application& app) {
    if (!ImGui::BeginMenuBar()) {
        return;
    }
    if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Open Game...")) {
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
    if (ImGui::BeginMenu("View")) {
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
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Audio")) {
        if (ImGui::MenuItem("Mute", nullptr, app.prefs().mute)) {
            app.setMuted(!app.prefs().mute);
        }
        int volume = app.prefs().volume;
        ImGui::SetNextItemWidth(140.f);
        if (ImGui::SliderInt("Volume", &volume, 0, 100, "%d")) {
            app.setVolume(volume);
        }
        ImGui::EndMenu();
    }
    bool openControls = false;
    bool openAbout = false;
    if (ImGui::BeginMenu("Help")) {
        if (ImGui::MenuItem("Controls")) {
            openControls = true;
        }
        if (ImGui::MenuItem("About Emulocke")) {
            openAbout = true;
        }
        ImGui::EndMenu();
    }
    ImGui::EndMenuBar();
    if (openControls) {
        ImGui::OpenPopup("Controls");
    }
    if (openAbout) {
        ImGui::OpenPopup("About");
    }
    drawHelpPopups(app);
}

}
