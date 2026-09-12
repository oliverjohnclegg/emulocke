#pragma once

#include "adapter/LiveMemory.hpp"
#include "adapter/Snapshot.hpp"

namespace emulocke {

void fillSnapshotFromFrlgLive(const LiveMemory& mem, GameSnapshot& snap);

}