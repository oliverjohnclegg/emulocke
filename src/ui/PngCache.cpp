#include "ui/PngCache.hpp"

#include "cart/GameArtPng.hpp"
#include "emu/FileBytes.hpp"

#include <imgui.h>
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>

namespace emulocke {
namespace {

void opaqueCrop(const RgbaImage& image, CachedPng& png) {
    png.w = image.width;
    png.h = image.height;
    int x0 = image.width;
    int y0 = image.height;
    int x1 = 0;
    int y1 = 0;
    for (int y = 0; y < image.height; ++y) {
        const uint8_t* row = image.pixels.data() + static_cast<std::size_t>(y) * image.width * 4;
        for (int x = 0; x < image.width; ++x) {
            if (row[x * 4 + 3] > 8) {
                x0 = std::min(x0, x);
                y0 = std::min(y0, y);
                x1 = std::max(x1, x + 1);
                y1 = std::max(y1, y + 1);
            }
        }
    }
    if (x1 <= x0) {
        png.cropW = image.width;
        png.cropH = image.height;
        return;
    }
    png.cropX = x0;
    png.cropY = y0;
    png.cropW = x1 - x0;
    png.cropH = y1 - y0;
}

}  // namespace

PngCache::PngCache(SDL_Renderer* renderer) : renderer_(renderer) {}

PngCache::~PngCache() {
    for (auto& [_, png] : tex_) {
        if (png.tex) {
            SDL_DestroyTexture(png.tex);
        }
    }
}

CachedPng PngCache::get(const std::filesystem::path& path) {
    const std::string key = path.string();
    auto it = tex_.find(key);
    if (it != tex_.end()) {
        return it->second;
    }
    CachedPng png;
    const auto bytes = readWholeFile(key, kMaxImageFile);
    const auto image = decodePngRgba(bytes);
    if (!image || !renderer_) {
        tex_[key] = png;
        return png;
    }
    png.tex = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, image->width,
        image->height);
    if (!png.tex) {
        tex_[key] = png;
        return png;
    }
    SDL_SetTextureBlendMode(png.tex, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode(png.tex, SDL_SCALEMODE_NEAREST);
    SDL_UpdateTexture(png.tex, nullptr, image->pixels.data(), image->width * 4);
    opaqueCrop(*image, png);
    tex_[key] = png;
    return png;
}

void PngCache::drawNearest(SDL_Texture* tex, ImVec2 p, ImVec2 size, ImVec2 uv0, ImVec2 uv1) {
    if (!tex) {
        return;
    }
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImGuiPlatformIO& pio = ImGui::GetPlatformIO();
    if (pio.DrawCallback_SetSamplerNearest) {
        dl->AddCallback(pio.DrawCallback_SetSamplerNearest, nullptr);
    }
    const ImVec2 a(std::floor(p.x + 0.5f), std::floor(p.y + 0.5f));
    const ImVec2 b(std::floor(p.x + size.x + 0.5f), std::floor(p.y + size.y + 0.5f));
    dl->AddImage(tex, a, b, uv0, uv1);
    if (pio.DrawCallback_SetSamplerLinear) {
        dl->AddCallback(pio.DrawCallback_SetSamplerLinear, nullptr);
    }
}

}
