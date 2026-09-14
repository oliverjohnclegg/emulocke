#include "cart/GameArtPng.hpp"

#include "cart/GameArt.hpp"
#include "emu/FileLimits.hpp"

#include <algorithm>
#include <fstream>
#include <memory>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_ONLY_PNG
#define STBI_NO_FAILURE_STRINGS
#define STBI_MAX_DIMENSIONS 4096
#include "stb_image.h"
#include "stb_image_write.h"

namespace emulocke {
namespace {

struct StbiFree {
    void operator()(uint8_t* pixels) const { stbi_image_free(pixels); }
};

}  // namespace

std::optional<RgbaImage> decodePngRgba(const std::vector<uint8_t>& png) {
    if (png.empty() || png.size() > kMaxImageFile) {
        return std::nullopt;
    }
    int width = 0;
    int height = 0;
    int channels = 0;
    const std::unique_ptr<uint8_t, StbiFree> raw(
        stbi_load_from_memory(png.data(), static_cast<int>(png.size()), &width, &height, &channels, 4));
    if (!raw || width <= 0 || height <= 0 || width > kMaxImageSide || height > kMaxImageSide) {
        return std::nullopt;
    }
    RgbaImage image;
    image.width = width;
    image.height = height;
    image.pixels.assign(raw.get(), raw.get() + static_cast<size_t>(width) * static_cast<size_t>(height) * 4);
    return image;
}

bool writeRgbaPng(const std::filesystem::path& path, int width, int height, const uint8_t* rgba) {
    return stbi_write_png(path.string().c_str(), width, height, 4, rgba, width * 4) != 0;
}

bool gameArtPngSize(const std::filesystem::path& path, int& width, int& height) {
    std::ifstream in(path, std::ios::binary);
    unsigned char header[24];
    if (!in.read(reinterpret_cast<char*>(header), 24)) {
        return false;
    }
    static const unsigned char png[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    if (!std::equal(std::begin(png), std::end(png), header)) {
        return false;
    }
    if (header[12] != 'I' || header[13] != 'H' || header[14] != 'D' || header[15] != 'R') {
        return false;
    }
    width = (header[16] << 24) | (header[17] << 16) | (header[18] << 8) | header[19];
    height = (header[20] << 24) | (header[21] << 16) | (header[22] << 8) | header[23];
    return width > 0 && height > 0;
}

}
