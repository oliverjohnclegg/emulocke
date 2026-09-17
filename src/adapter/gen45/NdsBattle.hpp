#pragma once

#include "adapter/LiveMemory.hpp"
#include "adapter/Snapshot.hpp"

#include <cstddef>
#include <cstdint>
#include <span>

namespace emulocke {

inline constexpr std::size_t kNdsBattleMonSize = 0xC0;
inline constexpr std::size_t kNdsBattleMonStages = 0x18;
inline constexpr std::size_t kNdsBattleMonLevel = 0x34;
inline constexpr std::size_t kNdsBattleMonHp = 0x4C;
inline constexpr std::size_t kNdsBattleMonMaxHp = 0x50;
inline constexpr std::size_t kNdsBattleMonStatus = 0x6C;
inline constexpr uint32_t kNdsRam = 0x02000000;
inline constexpr uint32_t kNdsRamBytes = 0x400000;

bool ndsRamRange(uint32_t addr, std::size_t n);
bool readNdsBattleMon(std::span<const uint8_t> raw, BattleBattler& out);
void seedPlayerBattler(GameSnapshot& snap);
void bindBattleSlots(GameSnapshot& snap);
bool fillFoePartyFromPk(const LiveMemory& mem, uint32_t addr, std::size_t pkSize, bool utf16,
    GameSnapshot& snap);
void overlayNdsBattleMons(const LiveMemory& mem, uint32_t from, uint32_t to, GameSnapshot& snap);

}
