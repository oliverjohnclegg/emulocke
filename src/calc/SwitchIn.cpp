#include "calc/SwitchIn.hpp"

#include "calc/SwitchInPick.hpp"

namespace emulocke {

void switchOrder(const CalcPack& pack, const PackTrainer& trainer, const bool fainted[6],
    const Pokemon& player, uint8_t, int order[6], int current) {
    bool skip[6]{};
    for (int i = 0; i < 6; ++i) {
        order[i] = -1;
        skip[i] = i >= trainer.count || fainted[i];
    }
    int n = 0;
    int lead = -1;
    if (current >= 0 && current < trainer.count && !fainted[current]) {
        lead = current;
    } else {
        for (int i = 0; i < trainer.count; ++i) {
            if (!fainted[i]) {
                lead = i;
                break;
            }
        }
    }
    if (lead >= 0) {
        order[n++] = lead;
        skip[lead] = true;
    }
    for (;;) {
        const int pick = mostSuitableMon(pack, trainer, skip, player);
        if (pick < 0) {
            break;
        }
        order[n++] = pick;
        skip[pick] = true;
    }
    for (int i = 0; i < trainer.count; ++i) {
        if (!skip[i] && !fainted[i]) {
            order[n++] = i;
            skip[i] = true;
        }
    }
    for (int i = 0; i < trainer.count; ++i) {
        if (fainted[i]) {
            order[n++] = i;
        }
    }
}

int nextSwitchSlot(const CalcPack& pack, const PackTrainer& trainer, const bool fainted[6],
    const Pokemon& player, uint8_t switchIn, int current) {
    int order[6];
    switchOrder(pack, trainer, fainted, player, switchIn, order, current);
    if (current >= 0 && order[1] >= 0) {
        return order[1];
    }
    return order[0] >= 0 ? order[0] : 0;
}

}
