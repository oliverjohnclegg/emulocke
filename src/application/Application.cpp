#include "application/Application.hpp"

#include "emu/Paths.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <SDL3/SDL.h>

namespace emulocke {

bool Application::start(int argc, char** argv) {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
        return false;
    }
    SDL_InitSubSystem(SDL_INIT_AUDIO);
    if (!host_.create()) {
        return false;
    }
    applyTheme();
    bodyFont_ = loadBodyFont();
    displayFont_ = loadDisplayFont();
    if (bodyFont_) {
        ImGui::GetIO().FontDefault = bodyFont_;
    }
    audio_.open();
    input_.attach();
    ensureRomsDir();
    romsHint_ = exeRomsDir().string();
    runStore_ = std::make_unique<RunStore>(runsRoot());
    runStore_->load();
    scanRoms();
    if (argc > 1) {
        auto detected = detectRomFile(argv[1]);
        if (detected) {
            bool found = false;
            for (int i = 0; i < static_cast<int>(detectedGames_.size()); ++i) {
                if (detectedGames_[static_cast<size_t>(i)].gameId == detected->gameId) {
                    detectedGames_[static_cast<size_t>(i)] = *detected;
                    newRunDraft_.gameIndex = i;
                    found = true;
                    break;
                }
            }
            if (!found) {
                newRunDraft_.gameIndex = static_cast<int>(detectedGames_.size());
                detectedGames_.push_back(std::move(*detected));
            }
            newRunDraft_.rules = regularRules();
            showNewRun_ = true;
        } else {
            status_ = "Need a Pokemon .gba or .nds dump.";
        }
    }
    return true;
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