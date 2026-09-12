#pragma once

#include <cstdint>
#include <filesystem>
#include <optional>
#include <vector>

namespace emulocke {

struct RgbaImage {
    int width = 0;
    int height = 0;
    std::vector<uint8_t> pixels;
};

std::optional<RgbaImage> decodePngRgba(const std::vector<uint8_t>& png);
bool writeRgbaPng(const std::filesystem::path& path, int width, int height, const uint8_t* rgba);

}
