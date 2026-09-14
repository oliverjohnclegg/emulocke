#pragma once

namespace emulocke {

inline constexpr int kHpBarPx = 48;

inline int hpBarPixels(int hp, int maxHp) {
    if (maxHp <= 0 || hp <= 0) {
        return 0;
    }
    int px = hp * kHpBarPx / maxHp;
    if (px < 1) {
        px = 1;
    }
    if (px > kHpBarPx) {
        px = kHpBarPx;
    }
    return px;
}

inline int hpExactPct(int hp, int maxHp) {
    if (maxHp <= 0 || hp <= 0) {
        return 0;
    }
    const int pct = hp * 100 / maxHp;
    return pct < 1 ? 1 : pct;
}

inline void hpBarPctRange(int px, int& lo, int& hi) {
    if (px <= 0) {
        lo = hi = 0;
        return;
    }
    if (px >= kHpBarPx) {
        lo = hi = 100;
        return;
    }
    lo = px == 1 ? 1 : px * 100 / kHpBarPx;
    hi = ((px + 1) * 100 - 1) / kHpBarPx;
}

}
