#pragma once

#include <cstddef>
#include <cstdint>

namespace emulocke {

inline constexpr uint32_t kRsSaveBlock2 = 0x02024EA4;
inline constexpr uint32_t kRsSaveBlock1 = 0x02025734;
inline constexpr uint32_t kRsParty = 0x03004360;
inline constexpr uint32_t kRsPartyCount = 0x03004350;

inline constexpr uint32_t kEmParty = 0x020244EC;
inline constexpr uint32_t kEmPartyCount = 0x020244E9;
inline constexpr uint32_t kEmSaveBlock1Ptr = 0x03005D8C;
inline constexpr uint32_t kEmSaveBlock2Ptr = 0x03005D90;
inline constexpr uint32_t kEmSaveBlock2 = 0x02024A54;
inline constexpr uint32_t kEmSaveBlock1 = 0x02025A00;

inline constexpr std::size_t kRseSaveBlock2Size = 0xF80;
inline constexpr std::size_t kRseSaveBlock1Size = 0x3D88;
inline constexpr std::size_t kRseStorageSize = 0x83D0;
inline constexpr std::size_t kRsePartyOff = 0x238;
inline constexpr std::size_t kRsePartyCountOff = 0x234;
inline constexpr std::size_t kRseBoxStart = 0x0004;
inline constexpr std::size_t kRseBoxNameOff = 0x8344;
inline constexpr std::size_t kRseSaveSize = 0x20000;

inline constexpr uint8_t kVersionSapphire = 1;
inline constexpr uint8_t kVersionRuby = 2;
inline constexpr uint8_t kVersionEmerald = 3;

}
