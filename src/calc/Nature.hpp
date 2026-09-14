#pragma once

#include <cstdint>

namespace emulocke {

inline int natureMul(uint8_t nature, int stat) {
    if (stat < 1 || stat > 5 || nature > 24) {
        return 10;
    }
    const int up = nature / 5;
    const int down = nature % 5;
    if (up == down) {
        return 10;
    }
    if (stat - 1 == up) {
        return 11;
    }
    if (stat - 1 == down) {
        return 9;
    }
    return 10;
}

inline int boostedStat(int stat, int stage) {
    if (stage > 6) {
        stage = 6;
    }
    if (stage < -6) {
        stage = -6;
    }
    if (stage >= 0) {
        return stat * (2 + stage) / 2;
    }
    return stat * 2 / (2 - stage);
}

}
