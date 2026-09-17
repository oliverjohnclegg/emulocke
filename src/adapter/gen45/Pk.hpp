#pragma once

#include "adapter/Snapshot.hpp"

#include <cstdint>
#include <span>

namespace emulocke {

inline constexpr std::size_t kPkStoredSize = 136;
inline constexpr std::size_t kPk4PartySize = 236;
inline constexpr std::size_t kPk5PartySize = 220;
inline constexpr std::size_t kPkPartyStatsEnd = 0x9C;

bool decryptPk45(std::span<const uint8_t> raw, std::span<uint8_t> out);
bool encryptPk45(std::span<const uint8_t> plain, std::span<uint8_t> out);
void decodeGen4Text(std::span<const uint8_t> src, char* dest, std::size_t destSize);
void encodeGen4Text(const char* src, std::span<uint8_t> dest);
void decodeUtf16Text(std::span<const uint8_t> src, char* dest, std::size_t destSize);
void encodeUtf16Text(const char* src, std::span<uint8_t> dest);
bool utf16NamePresent(std::span<const uint8_t> src);
bool parsePk45(std::span<const uint8_t> raw, bool utf16Names, Mon& out);

}
