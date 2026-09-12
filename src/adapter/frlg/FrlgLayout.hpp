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
inline constexpr std::size_t kFrlgBoxStart = 0x0001;
inline constexpr std::size_t kFrlgBoxNameOff = 0x8344;
inline constexpr std::size_t kFrlgSaveSize = 0x20000;

inline constexpr uint8_t kVersionFireRed = 4;
inline constexpr uint8_t kVersionLeafGreen = 5;

}