#pragma once

#include "adapter/LiveMemory.hpp"
#include "adapter/Snapshot.hpp"
#include "adapter/gen4/Layout.hpp"

#include <span>

namespace emulocke {

bool readGen4Save(std::span<const uint8_t> sav, const Gen4Layout& layout, GameSnapshot& snap);
int activeGen4Slot(std::span<const uint8_t> sav, const Gen4Layout& layout);
bool fillGen4Live(const LiveMemory& mem, uint32_t partyAddr, const Gen4Layout& layout, GameSnapshot& snap);

}
