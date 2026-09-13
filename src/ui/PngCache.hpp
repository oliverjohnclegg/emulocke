#pragma once

#include <imgui.h>
#include <filesystem>
#include <string>
#include <unordered_map>

struct SDL_Renderer;
struct SDL_Texture;

namespace emulocke {

class PngCache {
public:
    explicit PngCache(SDL_Renderer* renderer);
    ~PngCache();
    PngCache(const PngCache&) = delete;
    PngCache& operator=(const PngCache&) = delete;
    SDL_Texture* get(const std::filesystem::path& path);
    static void drawNearest(SDL_Texture* tex, ImVec2 size);

private:
    SDL_Renderer* renderer_{};
    std::unordered_map<std::string, SDL_Texture*> tex_;
};

}
