#pragma once

#include <cstddef>
#include <cstdint>

namespace emulocke {

inline constexpr uint32_t kRsSaveBlock2 = 0x02024EA4;
inline constexpr uint32_t kRsSaveBlock1 = 0x02025734;
inline constexpr uint32_t kRsParty = 0x03004360;
inline constexpr uint32_t kRsPartyCount = 0x03004350;
inline constexpr uint32_t kRsStorage = 0x020300A4;
inline constexpr uint32_t kRsEnemyPartyCount = 0x030045B8;
inline constexpr uint32_t kRsEnemyParty = 0x030045BC;
inline constexpr uint32_t kRsBattleTypeFlags = 0x020239F8;
inline constexpr uint32_t kRsBattleMons = 0x02024A80;
inline constexpr uint32_t kRsBattleWeather = 0x02024DB8;

inline constexpr uint32_t kEmParty = 0x020244EC;
inline constexpr uint32_t kEmPartyCount = 0x020244E9;
inline constexpr uint32_t kEmSaveBlock1Ptr = 0x03005D8C;
inline constexpr uint32_t kEmSaveBlock2Ptr = 0x03005D90;
inline constexpr uint32_t kEmStoragePtr = 0x03005D94;
inline constexpr uint32_t kEmSaveBlock2 = 0x02024A54;
inline constexpr uint32_t kEmSaveBlock1 = 0x02025A00;
inline constexpr uint32_t kEmStorage = 0x02029808;
inline constexpr uint32_t kEmEnemyPartyCount = 0x020244EA;
inline constexpr uint32_t kEmEnemyParty = 0x02024744;
inline constexpr uint32_t kEmBattleTypeFlags = 0x02022FEC;
inline constexpr uint32_t kEmBattleMons = 0x02024084;
inline constexpr uint32_t kEmBattleWeather = 0x020243FC;

inline constexpr std::size_t kRseSaveBlock2Size = 0xF80;
inline constexpr std::size_t kRseSaveBlock1Size = 0x3D88;
inline constexpr std::size_t kRseStorageSize = 0x83D0;
inline constexpr std::size_t kRsePartyOff = 0x238;
inline constexpr std::size_t kRsePartyCountOff = 0x234;
inline constexpr std::size_t kRseMapGroupOff = 0x04;
inline constexpr std::size_t kRseMapNumOff = 0x05;
inline constexpr std::size_t kRseBoxStart = 0x0004;
inline constexpr std::size_t kRseBoxNameOff = 0x8344;
inline constexpr std::size_t kRseSaveSize = 0x20000;

inline constexpr std::size_t kRseFlagsOffRs = 0x122C;
inline constexpr std::size_t kRseFlagsOffEm = 0x1270;
inline constexpr std::size_t kRseVarsOffEm = 0x139C;
inline constexpr uint16_t kRseDifficultyVar = 0x404E;
inline constexpr uint16_t kRseBadge1Rs = 0x807;
inline constexpr uint16_t kRseBadge1Em = 0x867;
inline constexpr uint8_t kRseBadgeCount = 8;

inline constexpr std::size_t kRseBattleMonSize = 0x58;
inline constexpr std::size_t kRsePartyHpOff = 0x56;
inline constexpr std::size_t kRsePartyMaxHpOff = 0x58;
inline constexpr std::size_t kRsePartyLevelOff = 0x54;
inline constexpr uint32_t kRseBattleTypeTrainer = 1u << 3;

inline constexpr uint8_t kVersionSapphire = 1;
inline constexpr uint8_t kVersionRuby = 2;
inline constexpr uint8_t kVersionEmerald = 3;

}
