#include "ui/PngCache.hpp"

#include "cart/GameArtPng.hpp"
#include "emu/FileBytes.hpp"

#include <imgui.h>
#include <SDL3/SDL.h>

namespace emulocke {

PngCache::PngCache(SDL_Renderer* renderer) : renderer_(renderer) {}

PngCache::~PngCache() {
    for (auto& [_, tex] : tex_) {
        if (tex) {
            SDL_DestroyTexture(tex);
        }
    }
}

SDL_Texture* PngCache::get(const std::filesystem::path& path) {
    const std::string key = path.string();
    auto it = tex_.find(key);
    if (it != tex_.end()) {
        return it->second;
    }
    const auto bytes = readWholeFile(key);
    const auto image = decodePngRgba(bytes);
    if (!image || !renderer_) {
        tex_[key] = nullptr;
        return nullptr;
    }
    SDL_Texture* tex = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC,
        image->width, image->height);
    if (!tex) {
        tex_[key] = nullptr;
        return nullptr;
    }
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
    SDL_UpdateTexture(tex, nullptr, image->pixels.data(), image->width * 4);
    tex_[key] = tex;
    return tex;
}

void PngCache::drawNearest(SDL_Texture* tex, ImVec2 size) {
    if (!tex) {
        return;
    }
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImGuiPlatformIO& pio = ImGui::GetPlatformIO();
    if (pio.DrawCallback_SetSamplerNearest) {
        dl->AddCallback(pio.DrawCallback_SetSamplerNearest, nullptr);
    }
    ImGui::Image(tex, size);
    if (pio.DrawCallback_SetSamplerLinear) {
        dl->AddCallback(pio.DrawCallback_SetSamplerLinear, nullptr);
    }
}

}
