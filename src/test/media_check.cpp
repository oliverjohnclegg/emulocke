#include "cart/GameArtPng.hpp"
#include "emu/FileBytes.hpp"
#include "test/Check.hpp"

#include <cstdio>
#include <filesystem>
#include <vector>

namespace {

std::vector<uint8_t> pngWithIhdr(uint32_t width, uint32_t height) {
    std::vector<uint8_t> png{0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A, 0, 0, 0, 13, 'I', 'H', 'D', 'R'};
    for (const uint32_t v : {width, height}) {
        png.insert(png.end(), {static_cast<uint8_t>(v >> 24), static_cast<uint8_t>(v >> 16),
                               static_cast<uint8_t>(v >> 8), static_cast<uint8_t>(v)});
    }
    png.insert(png.end(), {8, 6, 0, 0, 0, 0, 0, 0, 0});
    return png;
}

void checkPngDecode() {
    REQUIRE(!emulocke::decodePngRgba({}));
    REQUIRE(!emulocke::decodePngRgba(pngWithIhdr(100000, 100000)));
    REQUIRE(!emulocke::decodePngRgba(pngWithIhdr(emulocke::kMaxImageSide + 1, 1)));
    REQUIRE(!emulocke::decodePngRgba(pngWithIhdr(1, emulocke::kMaxImageSide + 1)));
    std::vector<uint8_t> truncated = pngWithIhdr(4, 4);
    truncated.resize(20);
    REQUIRE(!emulocke::decodePngRgba(truncated));
    std::vector<uint8_t> oversized(emulocke::kMaxImageFile + 1, 0);
    REQUIRE(!emulocke::decodePngRgba(oversized));

    const auto dir = std::filesystem::temp_directory_path() / "emulocke-media-check";
    std::filesystem::create_directories(dir);
    const auto path = dir / "tiny.png";
    const std::vector<uint8_t> rgba(4 * 4 * 4, 0x7f);
    REQUIRE(emulocke::writeRgbaPng(path, 4, 4, rgba.data()));
    const auto decoded = emulocke::decodePngRgba(emulocke::readWholeFile(path.string(), emulocke::kMaxImageFile));
    REQUIRE(decoded && decoded->width == 4 && decoded->height == 4 && decoded->pixels == rgba);
    std::filesystem::remove_all(dir);
}

}  // namespace

int main() {
    checkPngDecode();
    std::printf("media check ok\n");
    return 0;
}
