#include "calc/SwitchIn.hpp"

#include "calc/Build.hpp"
#include "calc/Dex.hpp"
#include "calc/Type.hpp"

namespace emulocke {

int nextSwitchSlot(const CalcPack& pack, const PackTrainer& trainer, const bool fainted[6], uint8_t) {
    int first = -1;
    int best = -1;
    int bestScore = -999;
    for (int i = 0; i < trainer.count; ++i) {
        if (fainted[i]) {
            continue;
        }
        if (first < 0) {
            first = i;
        }
        const PackMon* mon = trainerMon(pack, trainer, i);
        const SpeciesRow* row = mon ? speciesById(mon->species) : nullptr;
        if (!row) {
            continue;
        }
        int score = 0;
        for (uint8_t t : {row->t1, row->t2}) {
            score += typeMul(pack.typeChart, static_cast<Type>(t), Type::Normal);
        }
        if (score > bestScore) {
            bestScore = score;
            best = i;
        }
    }
    if (best >= 0) {
        return best;
    }
    return first < 0 ? 0 : first;
}

}
