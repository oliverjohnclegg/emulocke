#pragma once

#include <cstddef>

namespace emulocke {

inline constexpr std::size_t kMaxCheatFile = std::size_t{64} << 10;
inline constexpr int kMaxCheats = 64;
inline constexpr std::size_t kMaxCheatName = 48;
inline constexpr std::size_t kMaxCheatLine = 128;
inline constexpr std::size_t kMaxCheatCode = 4096;

}
