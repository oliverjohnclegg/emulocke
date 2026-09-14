#include "poke/Dex.hpp"

namespace emulocke {
namespace {

uint32_t cube(uint32_t n) {
    return n * n * n;
}

uint32_t expAt(uint8_t growth, uint8_t level) {
    const uint32_t n = level;
    if (n <= 1) {
        return 0;
    }
    switch (growth) {
    case 1:
        if (n < 50) {
            return cube(n) * (100 - n) / 50;
        }
        if (n < 68) {
            return cube(n) * (150 - n) / 100;
        }
        if (n < 98) {
            return cube(n) * ((1911 - 10 * n) / 3) / 500;
        }
        return cube(n) * (160 - n) / 100;
    case 2:
        if (n < 15) {
            return cube(n) * ((n + 1) / 3 + 24) / 50;
        }
        if (n < 36) {
            return cube(n) * (n + 14) / 50;
        }
        return cube(n) * (n / 2 + 32) / 50;
    case 3: {
        const int v = static_cast<int>(6 * cube(n) / 5) - static_cast<int>(15 * n * n) +
                      static_cast<int>(100 * n) - 140;
        return v < 0 ? 0 : static_cast<uint32_t>(v);
    }
    case 4:
        return 4 * cube(n) / 5;
    case 5:
        return 5 * cube(n) / 4;
    default:
        return cube(n);
    }
}

}  // namespace

uint8_t levelFromExp(uint16_t national, uint32_t exp) {
    const uint8_t growth = speciesGrowth(national);
    uint8_t level = 1;
    for (uint8_t n = 2; n <= 100; ++n) {
        if (expAt(growth, n) > exp) {
            break;
        }
        level = n;
    }
    return level;
}

uint8_t monLevel(const Mon& mon, uint16_t national) {
    if (mon.level != 0) {
        return mon.level;
    }
    return levelFromExp(national, mon.experience);
}

}  // namespace emulocke
