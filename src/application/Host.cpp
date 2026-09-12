#include "application/Application.hpp"
#include "emu/Paths.hpp"
#include "ui/Layout.hpp"

#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>

namespace emulocke {

bool Host::create() {
    float scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    if (scale <= 0.f) {
        scale = 1.f;
    }
    window_ = SDL_CreateWindow("Emulocke", static_cast<int>(kDefaultWindowW * scale),
        static_cast<int>(kDefaultWindowH * scale), SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    if (!window_) {
        return false;
    }
    if (SDL_Surface* icon = SDL_LoadBMP(assetPath("icons/emulocke.bmp").c_str())) {
        SDL_SetWindowIcon(window_, icon);
        SDL_DestroySurface(icon);
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

}