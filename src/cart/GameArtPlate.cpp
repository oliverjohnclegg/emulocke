#include "cart/GameArtCanvas.hpp"

#include "cart/GameArt.hpp"
#include "cart/GameArtPng.hpp"

#include <cctype>
#include <vector>

namespace emulocke {
namespace {

constexpr uint8_t kDigits[10][7] = {
#include "cart/GameArtFont.inc"
};

constexpr uint8_t kLetters[26][7] = {
#include "cart/GameArtLetters.inc"
};

constexpr uint8_t kSpace[7] = {0, 0, 0, 0, 0, 0, 0};

const uint8_t* glyphRows(char c) {
    if (c >= '0' && c <= '9') {
        return kDigits[c - '0'];
    }
    if (c >= 'A' && c <= 'Z') {
        return kLetters[c - 'A'];
    }
    return kSpace;
}

void stampGlyph(uint8_t* dest, int gx, int gy, const uint8_t* rows, int scale) {
    for (int r = 0; r < 7; ++r) {
        for (int c = 0; c < 5; ++c) {
            if ((rows[r] & (1 << (4 - c))) == 0) {
                continue;
            }
            for (int sy = 0; sy < scale; ++sy) {
                for (int sx = 0; sx < scale; ++sx) {
                    const int x = gx + c * scale + sx;
                    const int y = gy + r * scale + sy;
                    if (x < 0 || y < 0 || x >= kGameArtWidth || y >= kGameArtHeight) {
                        continue;
                    }
                    uint8_t* px = dest + (static_cast<size_t>(y) * kGameArtWidth + x) * 4;
                    px[0] = 255;
                    px[1] = 255;
                    px[2] = 255;
                    px[3] = 255;
                }
            }
        }
    }
}

}  // namespace

bool writeTitlePlate(std::string_view title, const std::filesystem::path& out) {
    std::vector<uint8_t> canvas(static_cast<size_t>(kGameArtWidth) * kGameArtHeight * 4, 0);
    int scale = 3;
    const int n = static_cast<int>(title.size());
    const int cell = 6;
    while (scale > 1 && n * cell * scale - scale > kGameArtWidth - 8) {
        --scale;
    }
    const int textW = n == 0 ? 0 : n * cell * scale - scale;
    const int textH = 7 * scale;
    int x = (kGameArtWidth - textW) / 2;
    const int y = (kGameArtHeight - textH) / 2;
    for (char raw : title) {
        const char c = static_cast<char>(std::toupper(static_cast<unsigned char>(raw)));
        stampGlyph(canvas.data(), x, y, glyphRows(c), scale);
        x += cell * scale;
    }
    return writeRgbaPng(out, kGameArtWidth, kGameArtHeight, canvas.data());
}

}
