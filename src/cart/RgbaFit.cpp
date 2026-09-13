#include "cart/RgbaFit.hpp"

#include <algorithm>

namespace emulocke {
namespace {

constexpr uint8_t kAlphaMin = 12;

bool opaqueAt(const RgbaImage& src, int x, int y) {
    return src.pixels[static_cast<std::size_t>((y * src.width + x) * 4 + 3)] >= kAlphaMin;
}

}  // namespace

RgbaImage fitRgbaCell(const RgbaImage& src, int cellW, int cellH) {
    RgbaImage out;
    out.width = cellW;
    out.height = cellH;
    out.pixels.assign(static_cast<std::size_t>(cellW * cellH * 4), 0);
    if (src.width <= 0 || src.height <= 0 || src.pixels.size() < static_cast<std::size_t>(src.width * src.height * 4) ||
        cellW <= 0 || cellH <= 0) {
        return out;
    }
    int minX = src.width;
    int minY = src.height;
    int maxX = -1;
    int maxY = -1;
    for (int y = 0; y < src.height; ++y) {
        for (int x = 0; x < src.width; ++x) {
            if (opaqueAt(src, x, y)) {
                minX = std::min(minX, x);
                minY = std::min(minY, y);
                maxX = std::max(maxX, x);
                maxY = std::max(maxY, y);
            }
        }
    }
    if (maxX < 0) {
        return out;
    }
    const int cw = maxX - minX + 1;
    const int ch = maxY - minY + 1;
    int scale = std::max(1, std::min(cellW / cw, cellH / ch));
    while (scale > 1 && (cw * scale > cellW || ch * scale > cellH)) {
        --scale;
    }
    const int dw = cw * scale;
    const int dh = ch * scale;
    const int ox = (cellW - dw) / 2;
    const int oy = (cellH - dh) / 2;
    const int x0 = std::max(0, ox);
    const int y0 = std::max(0, oy);
    const int x1 = std::min(cellW, ox + dw);
    const int y1 = std::min(cellH, oy + dh);
    for (int y = y0; y < y1; ++y) {
        const int sy = minY + (y - oy) / scale;
        for (int x = x0; x < x1; ++x) {
            const int sx = minX + (x - ox) / scale;
            const std::size_t di = static_cast<std::size_t>((y * cellW + x) * 4);
            const std::size_t si = static_cast<std::size_t>((sy * src.width + sx) * 4);
            out.pixels[di] = src.pixels[si];
            out.pixels[di + 1] = src.pixels[si + 1];
            out.pixels[di + 2] = src.pixels[si + 2];
            out.pixels[di + 3] = src.pixels[si + 3];
        }
    }
    return out;
}

}
