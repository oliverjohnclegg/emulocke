#include "application/Application.hpp"

#include "application/BuildId.hpp"
#include "emu/Paths.hpp"
#include "run/Catalog.hpp"
#include "run/SavePeek.hpp"
#include "ui/MediaFetch.hpp"
#include "ui/PngCache.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <SDL3/SDL.h>
#include <cstring>
#include <string>

namespace emulocke {
namespace {

void onDumpPicked(void* userdata, const char* const* filelist, int) {
    auto* app = static_cast<Application*>(userdata);
    if (filelist && filelist[0]) {
        app->queueImport(filelist[0]);
    }
}

void onSavPicked(void* userdata, const char* const* filelist, int) {
    auto* app = static_cast<Application*>(userdata);
    if (filelist && filelist[0]) {
        app->queueImportSav(filelist[0]);
    } else {
        app->savPickerClosed();
    }
}

}  // namespace

bool Application::start(int argc, char** argv) {
    if (!sdl_.ok()) {
        return false;
    }
    prefs_ = Prefs::load();
    if (!host_.create(prefs_)) {
        return false;
    }
    syncWindowTitle();
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
    gameArt_ = std::make_unique<GameArtGpu>(prefDir() / "game-art");
    media_ = std::make_unique<MediaFetch>();
    pngs_ = std::make_unique<PngCache>(host_.renderer());
    savePeek_ = std::make_unique<SavePeek>();
    titlePlay_ = std::make_unique<TitlePlay>(prefDir() / "playtime.ini");
    std::string import;
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--preview-tracker") == 0) {
            previewTracker_ = true;
        } else if (std::strcmp(argv[i], "--preview-calc") == 0) {
            previewCalc_ = true;
        } else {
            import = argv[i];
        }
    }
    if (previewCalc_) {
        seedPreviewCalc();
        return true;
    }
    if (previewTracker_) {
        seedPreviewTracker();
    }
    if (!import.empty()) {
        importPath(import);
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

void Application::queueImportSav(std::string path) {
    savPickerOpen_ = false;
    pendingImportSav_ = std::move(path);
    pendingNewRun_ = false;
    showNewRun_ = false;
    pendingCreate_ = true;
}

void Application::showDumpPicker() {
    const SDL_DialogFileFilter filters[] = {
        {"Pokemon dumps", "gba;nds"},
    };
    SDL_ShowOpenFileDialog(onDumpPicked, this, host_.window(), filters, 1, nullptr, false);
}

void Application::showSavPicker() {
    const SDL_DialogFileFilter filters[] = {
        {"Save files", "sav"},
    };
    savPickerOpen_ = true;
    SDL_ShowOpenFileDialog(onSavPicked, this, host_.window(), filters, 1, nullptr, false);
}

void Application::requestImportGame() {
    importKeepUuid_.clear();
    showDumpPicker();
}

void Application::requestImportSav() {
    if (pendingSavPicker_ || savPickerOpen_ || pendingCreate_) {
        return;
    }
    pendingSavPicker_ = true;
}

void Application::savPickerClosed() {
    savPickerOpen_ = false;
}

void Application::requestImportFor(std::string uuid) {
    importKeepUuid_ = std::move(uuid);
    pendingDumpPicker_ = true;
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

void Application::syncWindowTitle() {
    std::string game;
    if (!activeRunId_.empty() && runStore_) {
        if (const Run* run = runStore_->find(activeRunId_)) {
            if (const CatalogTitle* title = catalogByUuid(run->catalogUuid)) {
                game = title->fullName;
            } else {
                game = "Pokemon";
            }
        }
    }
    const std::string title = windowTitle(buildChannel(), buildVersion(), buildHash(), game);
    host_.setTitle(title.c_str());
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