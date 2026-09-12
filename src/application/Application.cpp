#include "application/Application.hpp"

#include "ui/Shell.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <SDL3/SDL.h>

namespace emulocke {
namespace {

void onRomPicked(void* userdata, const char* const* filelist, int) {
    auto* app = static_cast<Application*>(userdata);
    if (filelist && filelist[0]) {
        app->queueRom(filelist[0]);
    }
}

}  // namespace

bool Application::start(int argc, char** argv) {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        return false;
    }
    SDL_InitSubSystem(SDL_INIT_AUDIO);
    prefs_ = Prefs::load();
    if (!host_.create(prefs_)) {
        return false;
    }
    applyTheme();
    bodyFont_ = loadBodyFont();
    displayFont_ = loadDisplayFont();
    if (bodyFont_) {
        ImGui::GetIO().FontDefault = bodyFont_;
    }
    audio_.setMuted(prefs_.mute);
    audio_.setVolume(prefs_.volume);
    audio_.open();
    input_.attach();
    if (argc > 1) {
        loadRom(argv[1]);
    }
    return true;
}

void Application::queueRom(std::string path) {
    pendingRom_ = std::move(path);
}

void Application::requestOpenRom() {
    const SDL_DialogFileFilter filters[] = {
        {"Pokemon games", "gba;nds"},
    };
    SDL_ShowOpenFileDialog(onRomPicked, this, host_.window(), filters, 1, nullptr, false);
}

void Application::setTouch(bool down, uint16_t x, uint16_t y) {
    touchDown_ = down;
    touchX_ = x;
    touchY_ = y;
}

void Application::pauseToggle() {
    paused_ = !paused_;
}

}
