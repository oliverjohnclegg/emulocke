#include "application/Host.hpp"
#include "application/BuildId.hpp"
#include "emu/Paths.hpp"
#include "ui/Layout.hpp"

#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <algorithm>
#include <memory>
#include <string>

namespace emulocke {
namespace {

void scaledLogicalSize(SDL_Window* window, int logicalW, int logicalH, int& w, int& h) {
    SDL_DisplayID display = window ? SDL_GetDisplayForWindow(window) : 0;
    if (!display) {
        display = SDL_GetPrimaryDisplay();
    }
    float scale = SDL_GetDisplayContentScale(display);
    if (scale <= 0.f) {
        scale = 1.f;
    }
    w = static_cast<int>(logicalW * scale);
    h = static_cast<int>(logicalH * scale);
    SDL_Rect bounds{};
    if (SDL_GetDisplayUsableBounds(display, &bounds) && bounds.w > 0 && bounds.h > 0) {
        w = std::min(w, bounds.w);
        h = std::min(h, bounds.h);
    }
}

void defaultWindowSize(int& w, int& h) {
    scaledLogicalSize(nullptr, kDefaultWindowW, kDefaultWindowH, w, h);
}

struct SdlSurfaceDeleter {
    void operator()(SDL_Surface* surface) const { SDL_DestroySurface(surface); }
};

}  // namespace

void SdlWindowDeleter::operator()(SDL_Window* window) const {
    SDL_DestroyWindow(window);
}

void SdlRendererDeleter::operator()(SDL_Renderer* renderer) const {
    SDL_DestroyRenderer(renderer);
}

Host::~Host() {
    destroy();
}

bool Host::create(const Prefs& prefs) {
    int w = prefs.windowW;
    int h = prefs.windowH;
    if (w <= 0 || h <= 0) {
        defaultWindowSize(w, h);
    }
    const std::string title = windowTitle(buildChannel(), buildVersion(), buildHash(), {});
    window_.reset(SDL_CreateWindow(title.c_str(), w, h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY));
    if (!window_) {
        return false;
    }
    if (prefs.hasWindowPos) {
        SDL_SetWindowPosition(window_.get(), prefs.windowX, prefs.windowY);
    }
    if (prefs.fullscreen) {
        SDL_SetWindowFullscreen(window_.get(), true);
    }
    const std::unique_ptr<SDL_Surface, SdlSurfaceDeleter> icon(
        SDL_LoadBMP(assetPath(windowIconBmp(buildChannel())).c_str()));
    if (icon) {
        SDL_SetWindowIcon(window_.get(), icon.get());
    }
    renderer_.reset(SDL_CreateRenderer(window_.get(), nullptr));
    if (!renderer_) {
        return false;
    }
    SDL_SetRenderVSync(renderer_.get(), 1);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    ImGui_ImplSDL3_InitForSDLRenderer(window_.get(), renderer_.get());
    ImGui_ImplSDLRenderer3_Init(renderer_.get());
    imguiReady_ = true;
    return true;
}

void Host::destroy() {
    if (imguiReady_) {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
        imguiReady_ = false;
    }
    renderer_.reset();
    window_.reset();
}

void Host::setFullscreen(bool on) {
    if (window_) {
        SDL_SetWindowFullscreen(window_.get(), on);
    }
}

bool Host::fullscreen() const {
    return window_ && (SDL_GetWindowFlags(window_.get()) & SDL_WINDOW_FULLSCREEN);
}

void Host::restoreDefaultSize() {
    if (!window_) {
        return;
    }
    setFullscreen(false);
    int w = 0;
    int h = 0;
    defaultWindowSize(w, h);
    setWindowSize(w, h);
}

void Host::adjustWidth(int delta) {
    if (!window_ || fullscreen() || delta == 0) {
        return;
    }
    int w = 0;
    int h = 0;
    SDL_GetWindowSize(window_.get(), &w, &h);
    setWindowSize(std::max(1, w + delta), h);
}

void Host::setWindowSize(int w, int h) {
    if (!window_ || w <= 0 || h <= 0) {
        return;
    }
    SDL_SetWindowSize(window_.get(), w, h);
}

void Host::contentWindowSize(int logicalW, int logicalH, int& w, int& h) const {
    scaledLogicalSize(window_.get(), logicalW, logicalH, w, h);
}

void Host::sizeToContent(int logicalW, int logicalH) {
    if (!window_ || fullscreen()) {
        return;
    }
    int w = 0;
    int h = 0;
    contentWindowSize(logicalW, logicalH, w, h);
    setWindowSize(w, h);
}

void Host::captureWindowed(Prefs& prefs) const {
    if (!window_ || fullscreen()) {
        return;
    }
    SDL_GetWindowPosition(window_.get(), &prefs.windowX, &prefs.windowY);
    SDL_GetWindowSize(window_.get(), &prefs.windowW, &prefs.windowH);
    prefs.hasWindowPos = true;
}

void Host::setTitle(const char* title) {
    if (window_ && title) {
        SDL_SetWindowTitle(window_.get(), title);
    }
}

}
