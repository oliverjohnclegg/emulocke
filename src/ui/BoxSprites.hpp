#pragma once

#include "poke/Sprites.hpp"

#include <SDL3/SDL.h>
#include <filesystem>
#include <string>
#include <string_view>
#include <unordered_map>

namespace emulocke {

class BoxSprites {
public:
    BoxSprites(SDL_Renderer* renderer, SpriteCache& cache, std::filesystem::path missingBox);
    ~BoxSprites();
    BoxSprites(const BoxSprites&) = delete;
    BoxSprites& operator=(const BoxSprites&) = delete;
    SDL_Texture* get(std::string_view slug);

private:
    SDL_Texture* loadPath(const std::filesystem::path& path);
    SDL_Renderer* renderer_{};
    SpriteCache* cache_{};
    SDL_Texture* missing_{};
    std::unordered_map<std::string, SDL_Texture*> loaded_;
};

}