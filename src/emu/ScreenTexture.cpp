#include "emu/ScreenTexture.hpp"

#include <SDL3/SDL.h>

namespace emulocke {

ScreenTexture::~ScreenTexture() {
    destroy();
}

void ScreenTexture::destroy() {
    if (texture_) {
        SDL_DestroyTexture(texture_);
        texture_ = nullptr;
    }
}

bool ScreenTexture::ensure(SDL_Renderer* renderer, int width, int height, int pixelFormat) {
    if (texture_ && width_ == width && height_ == height) {
        return true;
    }
    destroy();
    texture_ = SDL_CreateTexture(
        renderer, static_cast<SDL_PixelFormat>(pixelFormat), SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!texture_) {
        return false;
    }
    SDL_SetTextureScaleMode(texture_, SDL_SCALEMODE_NEAREST);
    width_ = width;
    height_ = height;
    return true;
}

void ScreenTexture::upload(const void* pixels, int pitchBytes) {
    if (!texture_ || !pixels) {
        return;
    }
    SDL_UpdateTexture(texture_, nullptr, pixels, pitchBytes);
}

}