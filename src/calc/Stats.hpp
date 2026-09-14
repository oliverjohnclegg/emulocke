#pragma once

#include <cstdint>

namespace emulocke {

int hpStat(int base, int iv, int ev, int level);
int otherStat(int base, int iv, int ev, int level, int natureMul);

}
