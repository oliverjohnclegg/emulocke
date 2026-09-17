#pragma once

#include "adapter/LiveMemory.hpp"
#include "adapter/Snapshot.hpp"
#include "adapter/gen45/Pk.hpp"

#include <algorithm>
#include <cstdint>
#include <span>

namespace emulocke {

inline constexpr std::size_t kGen5Party = 0x18E00;
inline constexpr std::size_t kGen5Trainer = 0x19400;
inline constexpr std::size_t kGen5Box = 0x400;
inline constexpr std::size_t kGen5BoxCount = 24;
inline constexpr std::size_t kGen5BoxStride = 30 * kPkStoredSize + 0x10;
inline constexpr std::size_t kGen5BoxNameStride = 0x28;
inline constexpr std::size_t kGen5TrainerBytes = 0x28;
inline constexpr std::size_t kBwBadgeOff = 0x21204;
inline constexpr std::size_t kBw2BadgeOff = 0x21104;
inline constexpr std::size_t kBwEventWork = 0x20100;
inline constexpr std::size_t kBw2EventWork = 0x1FF00;
inline constexpr std::size_t kBwFlagStart = 0x27C;
inline constexpr std::size_t kBw2FlagStart = 0x35E;
inline constexpr std::size_t kGen5FlagBytes = 384;
inline constexpr std::size_t kGen5Position = 0x19500;
inline constexpr std::size_t kGen5MinSave = std::max({kGen5Trainer + kGen5TrainerBytes,
                                                      kGen5Party + 8 + 6 * kPk5PartySize,
                                                      kGen5Box + kGen5BoxCount * kGen5BoxStride,
                                                      4 + kGen5BoxCount * kGen5BoxNameStride,
                                                      kBwEventWork + kBwFlagStart + kGen5FlagBytes,
                                                      kBw2EventWork + kBw2FlagStart + kGen5FlagBytes,
                                                      kGen5Position + 2,
                                                      kBwBadgeOff + 1,
                                                      kBw2BadgeOff + 1});
inline constexpr uint32_t kBwPartyLive = 0x022349B4;
inline constexpr uint32_t kWhitePartyLive = 0x022349D4;
inline constexpr uint32_t kBw2PartyLive = 0x0221E3EC;
inline constexpr uint32_t kWhite2PartyLive = 0x0221E40C;
inline constexpr uint8_t kVersionWhite = 20;
inline constexpr uint8_t kVersionBlack = 21;
inline constexpr uint8_t kVersionWhite2 = 22;
inline constexpr uint8_t kVersionBlack2 = 23;

bool readGen5Save(std::span<const uint8_t> sav, GameSnapshot& snap, bool bw2 = false);
bool fillGen5Live(const LiveMemory& mem, uint32_t partyAddr, GameSnapshot& snap, bool bw2 = false);

}
