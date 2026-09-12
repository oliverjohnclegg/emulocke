#include "application/Application.hpp"

#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <algorithm>

namespace emulocke {
namespace {

void defaultWindowSize(int& w, int& h) {
    float scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    if (scale <= 0.f) {
        scale = 1.f;
    }
    w = static_cast<int>(1440 * scale);
    h = static_cast<int>(900 * scale);
    SDL_Rect bounds{};
    if (SDL_GetDisplayUsableBounds(SDL_GetPrimaryDisplay(), &bounds) && bounds.w > 0 && bounds.h > 0) {
        w = std::min(w, bounds.w);
        h = std::min(h, bounds.h);
    }
}

}  // namespace

bool Host::create(const Prefs& prefs) {
    int w = prefs.windowW;
    int h = prefs.windowH;
    if (w <= 0 || h <= 0) {
        defaultWindowSize(w, h);
    }
    window_ = SDL_CreateWindow("Emulocke", w, h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    if (!window_) {
        return false;
    }
    if (prefs.hasWindowPos) {
        SDL_SetWindowPosition(window_, prefs.windowX, prefs.windowY);
    }
    if (prefs.fullscreen) {
        SDL_SetWindowFullscreen(window_, true);
    }
    renderer_ = SDL_CreateRenderer(window_, nullptr);
    if (!renderer_) {
        return false;
    }
    SDL_SetRenderVSync(renderer_, 1);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    ImGui_ImplSDL3_InitForSDLRenderer(window_, renderer_);
    ImGui_ImplSDLRenderer3_Init(renderer_);
    return true;
}

void Host::destroy() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }
    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
}

void Host::setFullscreen(bool on) {
    if (window_) {
        SDL_SetWindowFullscreen(window_, on);
    }
}

bool Host::fullscreen() const {
    return window_ && (SDL_GetWindowFlags(window_) & SDL_WINDOW_FULLSCREEN);
}

void Host::restoreDefaultSize() {
    if (!window_) {
        return;
    }
    setFullscreen(false);
    int w = 0;
    int h = 0;
    defaultWindowSize(w, h);
    SDL_SetWindowSize(window_, w, h);
}

void Host::captureWindowed(Prefs& prefs) const {
    if (!window_ || fullscreen()) {
        return;
    }
    SDL_GetWindowPosition(window_, &prefs.windowX, &prefs.windowY);
    SDL_GetWindowSize(window_, &prefs.windowW, &prefs.windowH);
    prefs.hasWindowPos = true;
}

}
