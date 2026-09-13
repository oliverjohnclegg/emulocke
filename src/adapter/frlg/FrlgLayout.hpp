#pragma once

#include <cstddef>
#include <cstdint>

namespace emulocke {

inline constexpr uint32_t kFrlgPartyCount = 0x02024029;
inline constexpr uint32_t kFrlgParty = 0x02024284;
inline constexpr uint32_t kFrlgSaveBlock2 = 0x02024588;
inline constexpr uint32_t kFrlgSaveBlock1 = 0x0202552C;
inline constexpr uint32_t kFrlgStorage = 0x02029314;
inline constexpr uint32_t kFrlgSaveBlock1Ptr = 0x03005008;
inline constexpr uint32_t kFrlgSaveBlock2Ptr = 0x0300500C;
inline constexpr uint32_t kFrlgStoragePtr = 0x03005010;

inline constexpr std::size_t kFrlgSaveBlock2Size = 0xF24;
inline constexpr std::size_t kFrlgSaveBlock1Size = 0x3D68;
inline constexpr std::size_t kFrlgStorageSize = 0x83D0;
inline constexpr std::size_t kFrlgPartyOff = 0x38;
inline constexpr std::size_t kFrlgPartyCountOff = 0x34;
inline constexpr std::size_t kFrlgMapGroupOff = 0x04;
inline constexpr std::size_t kFrlgMapNumOff = 0x05;
inline constexpr std::size_t kFrlgBoxStart = 0x0004;
inline constexpr std::size_t kFrlgBoxNameOff = 0x8344;
inline constexpr std::size_t kFrlgSaveSize = 0x20000;
inline constexpr std::size_t kFrlgFlagsOff = 0x0EE0;
inline constexpr uint16_t kFrlgBadge1Flag = 0x820;
inline constexpr uint8_t kFrlgBadgeCount = 8;
inline constexpr std::size_t kFrlgBadgeByteOff = kFrlgFlagsOff + kFrlgBadge1Flag / 8;

inline constexpr uint32_t kFrlgBattleTypeFlags = 0x02022B4C;
inline constexpr uint32_t kFrlgBattleMons = 0x02023BE4;
inline constexpr uint32_t kFrlgBattleWeather = 0x02023F1C;
inline constexpr uint32_t kFrlgEnemyPartyCount = 0x0202402A;
inline constexpr uint32_t kFrlgEnemyParty = 0x0202402C;
inline constexpr std::size_t kFrlgBattleMonSize = 0x58;
inline constexpr std::size_t kFrlgPartyHpOff = 0x56;
inline constexpr std::size_t kFrlgPartyMaxHpOff = 0x58;
inline constexpr std::size_t kFrlgPartyLevelOff = 0x54;
inline constexpr uint32_t kFrlgBattleTypeTrainer = 1u << 3;

inline constexpr uint8_t kVersionFireRed = 4;
inline constexpr uint8_t kVersionLeafGreen = 5;

}