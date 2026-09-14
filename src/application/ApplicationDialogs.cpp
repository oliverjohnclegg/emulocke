#include "application/Application.hpp"

#include <SDL3/SDL.h>
#include <new>
#include <string>

namespace emulocke {
namespace {

struct PickedFile {
    Application* app;
    std::string path;
};

SDL_Window* pickerWindow(SDL_Window* window) {
#ifdef _WIN32
    (void)window;
    return nullptr;
#else
    return window;
#endif
}

void importPicked(void* userdata) {
    auto* job = static_cast<PickedFile*>(userdata);
    job->app->queueImport(job->path);
    delete job;
}

void importSavPicked(void* userdata) {
    auto* job = static_cast<PickedFile*>(userdata);
    job->app->queueImportSav(job->path);
    delete job;
}

void pickerFailed(void* userdata) {
    static_cast<Application*>(userdata)->notePickerFailed();
}

void savPickerDone(void* userdata) {
    static_cast<Application*>(userdata)->savPickerClosed();
}

void onDumpPicked(void* userdata, const char* const* filelist, int) {
    auto* app = static_cast<Application*>(userdata);
    if (filelist && filelist[0]) {
        auto* job = new (std::nothrow) PickedFile{app, filelist[0]};
        if (job && SDL_RunOnMainThread(importPicked, job, false)) {
            return;
        }
        delete job;
        return;
    }
    if (!filelist) {
        SDL_RunOnMainThread(pickerFailed, app, false);
    }
}

void onSavPicked(void* userdata, const char* const* filelist, int) {
    auto* app = static_cast<Application*>(userdata);
    if (filelist && filelist[0]) {
        auto* job = new (std::nothrow) PickedFile{app, filelist[0]};
        if (job && SDL_RunOnMainThread(importSavPicked, job, false)) {
            return;
        }
        delete job;
        SDL_RunOnMainThread(savPickerDone, app, false);
        return;
    }
    SDL_RunOnMainThread(savPickerDone, app, false);
    if (!filelist) {
        SDL_RunOnMainThread(pickerFailed, app, false);
    }
}

}  // namespace

void Application::queueImport(std::string path) {
    pendingImport_ = std::move(path);
}

void Application::notePickerFailed() {
    status_ = "Couldn't open the file picker.";
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
    SDL_ShowOpenFileDialog(onDumpPicked, this, pickerWindow(host_.window()), filters, 1, nullptr, false);
}

void Application::showSavPicker() {
    const SDL_DialogFileFilter filters[] = {
        {"Save files", "sav"},
    };
    savPickerOpen_ = true;
    SDL_ShowOpenFileDialog(onSavPicked, this, pickerWindow(host_.window()), filters, 1, nullptr, false);
}

}