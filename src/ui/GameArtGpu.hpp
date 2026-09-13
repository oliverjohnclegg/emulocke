#pragma once

#include "cart/GameArt.hpp"

#include <atomic>
#include <filesystem>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>

struct SDL_Renderer;
struct SDL_Texture;

namespace emulocke {

class GameArtGpu {
public:
    explicit GameArtGpu(std::filesystem::path cacheDir);
    ~GameArtGpu();
    GameArtGpu(const GameArtGpu&) = delete;
    GameArtGpu& operator=(const GameArtGpu&) = delete;
    void requestPrefetch();
    SDL_Texture* texture(SDL_Renderer* renderer, std::string_view slug);
    void destroy();

private:
    void destroyTextures();
    SDL_Texture* load(SDL_Renderer* renderer, const std::filesystem::path& path);

    struct Slot {
        std::string path;
        SDL_Texture* tex{};
    };

    GameArtCache cache_;
    std::unordered_map<std::string, Slot> slots_;
    std::thread worker_;
    std::atomic<bool> stop_{false};
    std::atomic<bool> started_{false};
};

}
