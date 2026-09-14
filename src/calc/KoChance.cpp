#include "calc/KoChance.hpp"

#include <cstdio>

namespace emulocke {
namespace {

int countAt(const int* r, int hp, int hits, int sum) {
    if (hits == 0) {
        return sum >= hp ? 1 : 0;
    }
    int n = 0;
    for (int i = 0; i < 16; ++i) {
        n += countAt(r, hp, hits - 1, sum + r[i]);
    }
    return n;
}

void writePct(char* buf, int n, int hits, int total) {
    const int tenths = (hits * 1000 + total / 2) / total;
    if (tenths % 10 == 0) {
        std::snprintf(buf, n, "%d%%", tenths / 10);
    } else {
        std::snprintf(buf, n, "%d.%d%%", tenths / 10, tenths % 10);
    }
}

const char* koName(int h) {
    switch (h) {
    case 1:
        return "OHKO";
    case 2:
        return "2HKO";
    case 3:
        return "3HKO";
    default:
        return "4HKO";
    }
}

}  // namespace

void koChance(char* buf, int n, const DamageResult& dmg, int hp) {
    if (n <= 0) {
        return;
    }
    buf[0] = 0;
    if (dmg.immune || dmg.max <= 0 || hp <= 0) {
        std::snprintf(buf, n, "This move does no damage");
        return;
    }
    int total = 1;
    for (int h = 1; h <= 4; ++h) {
        total *= 16;
        if (h * dmg.max < hp) {
            continue;
        }
        const int c = h * dmg.min >= hp ? total : countAt(dmg.rolls, hp, h, 0);
        if (c == 0) {
            continue;
        }
        const char* ko = koName(h);
        if (c == total) {
            std::snprintf(buf, n, "This move is a guaranteed %s", ko);
        } else {
            char pct[16];
            writePct(pct, sizeof pct, c, total);
            std::snprintf(buf, n, "This move has a %s chance to %s", pct, ko);
        }
        return;
    }
    std::snprintf(buf, n, "This move is a 5HKO+");
}

}
