#pragma once

namespace emulocke {

struct DamageResult {
    int rolls[16]{};
    int min{};
    int max{};
    int hits{1};
    bool immune{};

    bool ohko(int hp) const { return !immune && min >= hp && hp > 0; }
    bool twoHko(int hp) const { return !immune && 2 * min >= hp && hp > 0; }
};

}
