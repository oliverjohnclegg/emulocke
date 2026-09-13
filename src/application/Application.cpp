#include "application/Application.hpp"

#include "emu/Paths.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <SDL3/SDL.h>

namespace emulocke {
namespace {

void onDumpPicked(void* userdata, const char* const* filelist, int) {
    auto* app = static_cast<Application*>(userdata);
    if (filelist && filelist[0]) {
        app->queueImport(filelist[0]);
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
    speedUp_ = prefs_.speedUp;
    speedUpHold_ = prefs_.speedUpHold;
    audio_.open();
    input_.attach();
    initTracker();
    romLibrary_ = std::make_unique<RomLibrary>(romsRoot(), assetsDir());
    runStore_ = std::make_unique<RunStore>(runsRoot());
    runStore_->load();
    titlePlay_ = std::make_unique<TitlePlay>(prefDir() / "playtime.ini");
    if (argc > 1) {
        importPath(argv[1]);
        if (newRunDraft_.catalogUuid.empty()) {
            status_ = "Need a supported Pokemon dump.";
        } else {
            newRunDraft_.rules = regularRules();
            showNewRun_ = true;
        }
    }
    return true;
}

void Application::queueImport(std::string path) {
    pendingImport_ = std::move(path);
}

void Application::requestImportGame() {
    const SDL_DialogFileFilter filters[] = {
        {"Pokemon dumps", "gba;nds"},
    };
    SDL_ShowOpenFileDialog(onDumpPicked, this, host_.window(), filters, 1, nullptr, false);
}

void Application::setTouch(bool down, uint16_t x, uint16_t y) {
    touchDown_ = down;
    touchX_ = x;
    touchY_ = y;
}

void Application::pauseToggle() {
    paused_ = !paused_;
    if (paused_) {
        commitPlay();
    }
}

void Application::pollSpeedUp(const bool* keys) {
    const bool down = keys && keys[SDL_SCANCODE_TAB];
    const bool usable = down && session_ && !ImGui::GetIO().WantTextInput;
    if (!session_) {
        speedUpOn_ = false;
    } else if (speedUpHold_.load()) {
        speedUpOn_ = usable;
    } else if (usable && !tabWasDown_) {
        speedUpOn_ = !speedUpOn_.load();
    }
    tabWasDown_ = down;
}

}