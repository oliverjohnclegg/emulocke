#pragma once

#include <cstdint>

struct SDL_Renderer;
struct SDL_Texture;

namespace emulocke {

class ScreenTexture {
public:
    ScreenTexture() = default;
    ~ScreenTexture();
    ScreenTexture(const ScreenTexture&) = delete;
    ScreenTexture& operator=(const ScreenTexture&) = delete;
    bool ensure(SDL_Renderer* renderer, int width, int height, int pixelFormat);
    void upload(const void* pixels, int pitchBytes);
    SDL_Texture* texture() const { return texture_; }
    int width() const { return width_; }
    int height() const { return height_; }

private:
    void destroy();
    SDL_Texture* texture_{};
    int width_{};
    int height_{};
};

}