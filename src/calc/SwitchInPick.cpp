#include "calc/SwitchInPick.hpp"

#include "calc/Dex.hpp"
#include "calc/SwitchInHits.hpp"

namespace emulocke {

int mostSuitableMon(const CalcPack& pack, const PackTrainer& trainer, const bool skip[6],
    const Pokemon& player) {
    bool invalid[6]{};
    for (int i = 0; i < 6; ++i) {
        invalid[i] = skip[i] || i >= trainer.count;
    }
    for (;;) {
        int bestDmg = 0;
        int bestId = -1;
        for (int i = 0; i < trainer.count; ++i) {
            if (invalid[i]) {
                continue;
            }
            const PackMon* mon = trainerMon(pack, trainer, i);
            const SpeciesRow* row = mon ? speciesById(mon->species) : nullptr;
            if (!row) {
                invalid[i] = true;
                continue;
            }
            const int dmg = playerHitsMon(pack.typeChart, player, *row);
            if (bestDmg < dmg) {
                bestDmg = dmg;
                bestId = i;
            }
        }
        if (bestId < 0) {
            break;
        }
        if (hasSeMove(pack.typeChart, *trainerMon(pack, trainer, bestId), player)) {
            return bestId;
        }
        invalid[bestId] = true;
    }
    int bestDmg = 0;
    int bestId = -1;
    for (int i = 0; i < trainer.count; ++i) {
        if (skip[i]) {
            continue;
        }
        const PackMon* mon = trainerMon(pack, trainer, i);
        if (!mon) {
            continue;
        }
        const int dmg = maxHitVs(pack, *mon, player);
        if (bestDmg < dmg) {
            bestDmg = dmg;
            bestId = i;
        }
    }
    return bestId;
}

}
