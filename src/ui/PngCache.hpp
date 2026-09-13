#pragma once

#include <imgui.h>
#include <filesystem>
#include <string>
#include <unordered_map>

struct SDL_Renderer;
struct SDL_Texture;

namespace emulocke {

struct CachedPng {
    SDL_Texture* tex{};
    int w{};
    int h{};
    int cropX{};
    int cropY{};
    int cropW{};
    int cropH{};
};

class PngCache {
public:
    explicit PngCache(SDL_Renderer* renderer);
    ~PngCache();
    PngCache(const PngCache&) = delete;
    PngCache& operator=(const PngCache&) = delete;
    CachedPng get(const std::filesystem::path& path);
    static void drawNearest(SDL_Texture* tex, ImVec2 p, ImVec2 size, ImVec2 uv0 = ImVec2(0, 0),
        ImVec2 uv1 = ImVec2(1, 1));

private:
    SDL_Renderer* renderer_{};
    std::unordered_map<std::string, CachedPng> tex_;
};

}
