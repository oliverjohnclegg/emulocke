#pragma once

#include "adapter/LiveMemory.hpp"
#include "adapter/Snapshot.hpp"
#include "adapter/rse/RseLayout.hpp"

namespace emulocke {

void fillSnapshotFromRseLive(const LiveMemory& mem, GameSnapshot& snap, bool emerald);

}
