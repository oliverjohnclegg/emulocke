#include "cart/GameArtCanvas.hpp"

#include "cart/GameArt.hpp"
#include "cart/GameArtPng.hpp"

#include <algorithm>
#include <vector>

namespace emulocke {
namespace {

void blitNearest(const RgbaImage& src, uint8_t* dest, int sx, int sy, int sw, int sh) {
    for (int y = 0; y < kGameArtHeight; ++y) {
        const int srcY = sy + y * sh / kGameArtHeight;
        for (int x = 0; x < kGameArtWidth; ++x) {
            const int srcX = sx + x * sw / kGameArtWidth;
            const uint8_t* in = src.pixels.data() + (static_cast<size_t>(srcY) * src.width + srcX) * 4;
            uint8_t* out = dest + (static_cast<size_t>(y) * kGameArtWidth + x) * 4;
            out[0] = in[0];
            out[1] = in[1];
            out[2] = in[2];
            out[3] = 255;
        }
    }
}

void coverCrop(int width, int height, int& sx, int& sy, int& sw, int& sh) {
    sx = 0;
    sy = 0;
    sw = width;
    sh = height;
    if (height * 2 == width * 3) {
        sh = width * kGameArtHeight / kGameArtWidth;
        return;
    }
    if (width * kGameArtHeight > height * kGameArtWidth) {
        sw = height * kGameArtWidth / kGameArtHeight;
        sx = (width - sw) / 2;
        return;
    }
    if (width * kGameArtHeight < height * kGameArtWidth) {
        sh = width * kGameArtHeight / kGameArtWidth;
        sy = 0;
    }
}

}  // namespace

bool writeFittedPng(const std::vector<uint8_t>& png, const std::filesystem::path& out) {
    const auto src = decodePngRgba(png);
    if (!src) {
        return false;
    }
    int sx = 0;
    int sy = 0;
    int sw = src->width;
    int sh = src->height;
    coverCrop(src->width, src->height, sx, sy, sw, sh);
    sw = std::max(1, std::min(sw, src->width - sx));
    sh = std::max(1, std::min(sh, src->height - sy));
    std::vector<uint8_t> canvas(static_cast<size_t>(kGameArtWidth) * kGameArtHeight * 4, 0);
    blitNearest(*src, canvas.data(), sx, sy, sw, sh);
    return writeRgbaPng(out, kGameArtWidth, kGameArtHeight, canvas.data());
}

}
