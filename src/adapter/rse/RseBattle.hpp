#pragma once

#include "adapter/LiveMemory.hpp"
#include "adapter/Snapshot.hpp"

namespace emulocke {

void fillRseBattle(const LiveMemory& mem, GameSnapshot& snap, bool emerald);

}
