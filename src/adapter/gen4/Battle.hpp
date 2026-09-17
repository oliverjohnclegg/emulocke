#pragma once

#include "adapter/LiveMemory.hpp"
#include "adapter/Snapshot.hpp"
#include "adapter/gen4/Layout.hpp"

#include <cstdint>

namespace emulocke {

inline constexpr uint32_t kHgSavePtr = 0x0211186C;
inline constexpr uint32_t kSsSavePtr = 0x0211188C;
inline constexpr uint32_t kDpEnemyPtrOff = 0x364C8;
inline constexpr uint32_t kDpEnemyPartyAdd = 0x774;
inline constexpr uint32_t kDpWildPartyOff = 0x36C6C;
inline constexpr uint32_t kDpFoeHpOff = 0x5568C;
inline constexpr uint32_t kPtEnemyPtrOff = 0x352F4;
inline constexpr uint32_t kPtEnemyPartyAdd = 0x7A0;
inline constexpr uint32_t kPtWildPartyOff = 0x35AC4;
inline constexpr uint32_t kPtFoeHpOff = 0x546A4;
inline constexpr uint32_t kHgEnemyPtrOff = 0x37970;
inline constexpr uint32_t kHgEnemyPartyAdd = 0x1C70;
inline constexpr uint32_t kHgWildPartyOff = 0x38540;
inline constexpr uint32_t kHgFoeHpOff = 0x56F00;

void fillGen4Battle(const LiveMemory& mem, uint32_t partyAddr, const Gen4Layout& layout, GameSnapshot& snap);

}
