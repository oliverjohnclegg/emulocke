#include "ui/GameArtGpu.hpp"

#include "emu/FileBytes.hpp"
#include "cart/GameArtPng.hpp"
#include "poke/SpriteIndex.hpp"
#include "run/Catalog.hpp"

#include <SDL3/SDL.h>

namespace emulocke {

GameArtGpu::GameArtGpu(std::filesystem::path cacheDir) : cache_(std::move(cacheDir)) {}

GameArtGpu::~GameArtGpu() {
    destroy();
}

void GameArtGpu::destroy() {
    stop_ = true;
    if (worker_.joinable()) {
        worker_.join();
    }
    destroyTextures();
}

void GameArtGpu::destroyTextures() {
    for (auto& [_, slot] : slots_) {
        if (slot.tex) {
            SDL_DestroyTexture(slot.tex);
            slot.tex = nullptr;
        }
    }
    slots_.clear();
}

void GameArtGpu::requestPrefetch() {
    bool expected = false;
    if (!started_.compare_exchange_strong(expected, true)) {
        return;
    }
    worker_ = std::thread([this] {
        for (const CatalogTitle& title : catalogTitles()) {
            if (stop_) {
                break;
            }
            cache_.get(title.artSlug);
        }
    });
}

SDL_Texture* GameArtGpu::load(SDL_Renderer* renderer, const std::filesystem::path& path) {
    const auto bytes = readWholeFile(path.string(), kMaxImageFile);
    const auto image = decodePngRgba(bytes);
    if (!image || !renderer) {
        return nullptr;
    }
    SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC,
        image->width, image->height);
    if (!tex) {
        return nullptr;
    }
    SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    SDL_UpdateTexture(tex, nullptr, image->pixels.data(), image->width * 4);
    return tex;
}

SDL_Texture* GameArtGpu::texture(SDL_Renderer* renderer, std::string_view slug) {
    const std::string key = normalizeSlug(slug);
    const std::string path = cache_.existing(slug).string();
    Slot& slot = slots_[key];
    if (slot.tex && slot.path == path) {
        return slot.tex;
    }
    if (slot.tex) {
        SDL_DestroyTexture(slot.tex);
        slot.tex = nullptr;
    }
    slot.path = path;
    slot.tex = load(renderer, path);
    return slot.tex;
}

}
