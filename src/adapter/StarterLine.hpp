#pragma once

#include <cstdint>

namespace emulocke {

inline uint16_t starterLineRoot(uint16_t id) {
    static constexpr uint16_t kRoot[] = {1,   4,   7,   152, 155, 158, 246, 252, 255, 258, 374, 387, 390,
                                         393, 443, 495, 498, 501, 650, 653, 656, 722, 725, 728, 810, 813,
                                         816, 906, 909, 912};
    for (uint16_t root : kRoot) {
        if (id >= root && id < static_cast<uint16_t>(root + 3)) {
            return root;
        }
    }
    return 0;
}

inline bool sameStarterLine(uint16_t a, uint16_t b) {
    const uint16_t root = starterLineRoot(a);
    return root != 0 && root == starterLineRoot(b);
}

}