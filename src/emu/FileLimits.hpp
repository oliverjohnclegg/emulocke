#pragma once

#include <cstddef>

namespace emulocke {

inline constexpr std::size_t kMaxRomFile = std::size_t{512} << 20;
inline constexpr std::size_t kMaxSaveFile = std::size_t{16} << 20;
inline constexpr std::size_t kMaxPatchFile = std::size_t{64} << 20;
inline constexpr std::size_t kMaxImageFile = std::size_t{32} << 20;
inline constexpr std::size_t kMaxTextFile = std::size_t{1} << 20;

}
