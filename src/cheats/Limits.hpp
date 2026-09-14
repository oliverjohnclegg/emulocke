#pragma once

#include <cstddef>

namespace emulocke {

inline constexpr std::size_t kMaxCheatFile = 64 * 1024;
inline constexpr int kMaxCheats = 64;
inline constexpr std::size_t kMaxCheatName = 48;
inline constexpr std::size_t kMaxCheatLine = 128;
inline constexpr std::size_t kMaxCheatCode = 4096;

}
