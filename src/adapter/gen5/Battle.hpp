#pragma once

#include "adapter/LiveMemory.hpp"
#include "adapter/Snapshot.hpp"

#include <cstdint>

namespace emulocke {

inline constexpr uint32_t kBwEnemyPartyLive = 0x0226ACF4;
inline constexpr uint32_t kWhiteEnemyPartyLive = 0x0226AD14;
inline constexpr uint32_t kBwWildPartyLive = 0x02259DD8;
inline constexpr uint32_t kWhiteWildPartyLive = 0x02259DF8;
inline constexpr uint32_t kBw2EnemyPartyLive = 0x02258834;
inline constexpr uint32_t kWhite2EnemyPartyLive = 0x02258874;
inline constexpr uint32_t kBw2WildPartyLive = 0x0224795C;
inline constexpr uint32_t kWhite2WildPartyLive = 0x0224799C;

void fillGen5Battle(const LiveMemory& mem, uint32_t partyAddr, GameSnapshot& snap);

}
