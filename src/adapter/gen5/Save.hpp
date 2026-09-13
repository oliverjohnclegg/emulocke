#pragma once

#include "adapter/LiveMemory.hpp"
#include "adapter/Snapshot.hpp"

#include <cstdint>
#include <span>

namespace emulocke {

inline constexpr std::size_t kGen5Party = 0x18E00;
inline constexpr std::size_t kGen5Trainer = 0x19400;
inline constexpr std::size_t kGen5Box = 0x400;
inline constexpr uint32_t kBwPartyLive = 0x022349B4;
inline constexpr uint32_t kWhitePartyLive = 0x022349D4;
inline constexpr uint32_t kBw2PartyLive = 0x0221E3EC;
inline constexpr uint32_t kWhite2PartyLive = 0x0221E40C;
inline constexpr uint8_t kVersionWhite = 20;
inline constexpr uint8_t kVersionBlack = 21;
inline constexpr uint8_t kVersionWhite2 = 22;
inline constexpr uint8_t kVersionBlack2 = 23;

bool readGen5Save(std::span<const uint8_t> sav, GameSnapshot& snap);
bool fillGen5Live(const LiveMemory& mem, uint32_t partyAddr, GameSnapshot& snap);

}
