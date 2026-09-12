#pragma once

#include <cstdint>

namespace emulocke {

enum class Button : uint32_t {
    A = 1u << 0,
    B = 1u << 1,
    Select = 1u << 2,
    Start = 1u << 3,
    Right = 1u << 4,
    Left = 1u << 5,
    Up = 1u << 6,
    Down = 1u << 7,
    R = 1u << 8,
    L = 1u << 9,
    X = 1u << 10,
    Y = 1u << 11,
};

inline constexpr uint32_t kReleasedMask = 0xFFF;

enum class ConsoleKind { None, Gba, Nds };

}