#pragma once

#include "adapter/LiveMemory.hpp"
#include "adapter/Snapshot.hpp"

namespace emulocke {

void fillFrlgBattle(const LiveMemory& mem, GameSnapshot& snap);

}
