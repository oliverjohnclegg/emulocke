#include "calc/Stats.hpp"

namespace emulocke {

int hpStat(int base, int iv, int ev, int level) {
    if (base == 1) {
        return 1;
    }
    return (2 * base + iv + ev / 4) * level / 100 + level + 10;
}

int otherStat(int base, int iv, int ev, int level, int natureMul) {
    return ((2 * base + iv + ev / 4) * level / 100 + 5) * natureMul / 10;
}

}
