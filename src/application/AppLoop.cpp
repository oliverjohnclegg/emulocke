#include "application/Application.hpp"

#include "ui/Shell.hpp"

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <SDL3/SDL.h>

namespace emulocke {

void Application::run() {
    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {
                return;
            }
            if (event.type == SDL_EVENT_GAMEPAD_ADDED) {
                input_.handleAdded(event.gdevice.which);
            }
            if (event.type == SDL_EVENT_GAMEPAD_REMOVED) {
                input_.handleRemoved(event.gdevice.which);
            }
        }
        drainPending();
        const bool* keys = SDL_GetKeyboardState(nullptr);
        if (!ImGui::GetIO().WantTextInput) {
            buttons_ = input_.poll(keys);
        }
        {
            std::lock_guard lock(sessionMutex_);
            if (session_) {
                const uint32_t gba = SDL_PIXELFORMAT_ABGR8888;
                const uint32_t nds = SDL_PIXELFORMAT_BGRA32;
                const uint32_t fmt = session_->kind() == ConsoleKind::Nds ? nds : gba;
                for (int i = 0; i < session_->screenCount(); ++i) {
                    const int w = session_->screenWidth(i);
                    const int h = session_->screenHeight(i);
                    screens_[i].ensure(host_.renderer(), w, h, fmt);
                    uploadScratch_.resize(static_cast<size_t>(w * 4 * h));
                    session_->copyScreen(i, uploadScratch_.data(), w * 4);
                    screens_[i].upload(uploadScratch_.data(), w * 4);
                }
            }
        }
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        ImGui::Begin("emulocke", nullptr,
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar |
                ImGuiWindowFlags_NoBringToFrontOnFocus);
        drawMenuBar(*this);
        if (session_) {
            drawShell(*this);
        } else {
            drawHome(*this);
        }
        drawNewRunModal(*this);
        drawLoadRunModal(*this);
        ImGui::End();
        ImGui::Render();
        SDL_SetRenderDrawColor(host_.renderer(), 18, 16, 14, 255);
        SDL_RenderClear(host_.renderer());
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), host_.renderer());
        SDL_RenderPresent(host_.renderer());
    }
}

}
