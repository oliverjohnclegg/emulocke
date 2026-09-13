#include "ui/BoxSprites.hpp"

#include "cart/GameArtPng.hpp"

#include <fstream>
#include <vector>

namespace emulocke {
namespace {

std::vector<uint8_t> readAll(const std::filesystem::path& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        return {};
    }
    in.seekg(0, std::ios::end);
    const auto size = in.tellg();
    if (size <= 0) {
        return {};
    }
    std::vector<uint8_t> bytes(static_cast<std::size_t>(size));
    in.seekg(0);
    in.read(reinterpret_cast<char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
    return bytes;
}

}  // namespace

BoxSprites::BoxSprites(SDL_Renderer* renderer, SpriteCache& cache, std::filesystem::path missingBox)
    : renderer_(renderer), cache_(&cache) {
    missing_ = loadPath(missingBox);
}

BoxSprites::~BoxSprites() {
    for (auto& [_, tex] : loaded_) {
        if (tex && tex != missing_) {
            SDL_DestroyTexture(tex);
        }
    }
    if (missing_) {
        SDL_DestroyTexture(missing_);
    }
}

SDL_Texture* BoxSprites::loadPath(const std::filesystem::path& path) {
    const auto bytes = readAll(path);
    const auto image = decodePngRgba(bytes);
    if (!image || !renderer_) {
        return nullptr;
    }
    SDL_Texture* tex = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC,
                                           image->width, image->height);
    if (!tex) {
        return nullptr;
    }
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
    SDL_UpdateTexture(tex, nullptr, image->pixels.data(), image->width * 4);
    return tex;
}

SDL_Texture* BoxSprites::get(std::string_view slug) {
    if (slug.empty()) {
        return missing_;
    }
    const std::string key(slug);
    const auto it = loaded_.find(key);
    if (it != loaded_.end()) {
        return it->second;
    }
    SDL_Texture* tex = nullptr;
    if (cache_) {
        tex = loadPath(cache_->get(slug, SpriteKind::Box));
    }
    if (!tex) {
        tex = missing_;
    }
    loaded_[key] = tex;
    return tex;
}

}