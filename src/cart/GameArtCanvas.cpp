#include "cart/GameArtCanvas.hpp"

#include "cart/GameArt.hpp"
#include "cart/GameArtPng.hpp"

#include <algorithm>
#include <vector>

namespace emulocke {
namespace {

void blitNearest(const RgbaImage& src, uint8_t* dest, int dw, int dh, int ox, int oy) {
    for (int y = 0; y < dh; ++y) {
        const int sy = y * src.height / dh;
        for (int x = 0; x < dw; ++x) {
            const int sx = x * src.width / dw;
            const uint8_t* in = src.pixels.data() + (static_cast<size_t>(sy) * src.width + sx) * 4;
            uint8_t* out =
                dest + (static_cast<size_t>(oy + y) * kGameArtWidth + (ox + x)) * 4;
            out[0] = in[0];
            out[1] = in[1];
            out[2] = in[2];
            out[3] = 255;
        }
    }
}

}  // namespace

bool writeLetterboxedPng(const std::vector<uint8_t>& png, const std::filesystem::path& out) {
    const auto src = decodePngRgba(png);
    if (!src) {
        return false;
    }
    std::vector<uint8_t> canvas(static_cast<size_t>(kGameArtWidth) * kGameArtHeight * 4, 0);
    int dw = src->width;
    int dh = src->height;
    if (dw > kGameArtWidth || dh > kGameArtHeight) {
        if (dw * kGameArtHeight > dh * kGameArtWidth) {
            dw = kGameArtWidth;
            dh = src->height * kGameArtWidth / src->width;
        } else {
            dh = kGameArtHeight;
            dw = src->width * kGameArtHeight / src->height;
        }
    } else {
        const int scale = std::min(kGameArtWidth / dw, kGameArtHeight / dh);
        dw *= scale;
        dh *= scale;
    }
    dw = std::max(1, std::min(dw, kGameArtWidth));
    dh = std::max(1, std::min(dh, kGameArtHeight));
    blitNearest(*src, canvas.data(), dw, dh, (kGameArtWidth - dw) / 2, (kGameArtHeight - dh) / 2);
    return writeRgbaPng(out, kGameArtWidth, kGameArtHeight, canvas.data());
}

}
