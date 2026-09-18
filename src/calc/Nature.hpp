#pragma once

#include <cstdint>

namespace emulocke {

inline int naturePlus(uint8_t nature) {
    if (nature > 24) {
        return -1;
    }
    const int up = nature / 5;
    const int down = nature % 5;
    return up == down ? -1 : up;
}

inline int natureMinus(uint8_t nature) {
    if (nature > 24) {
        return -1;
    }
    const int up = nature / 5;
    const int down = nature % 5;
    return up == down ? -1 : down;
}

inline const char* natureStatAbbrev(int index) {
    constexpr const char* kNames[] = {"atk", "def", "spe", "spa", "spd"};
    if (index < 0 || index > 4) {
        return "";
    }
    return kNames[index];
}

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
