#pragma once

#include "calc/Field.hpp"
#include "calc/Pokemon.hpp"

#include <cstdint>

namespace emulocke {

inline constexpr uint32_t kAiCheckBadMove = 1u << 0;
inline constexpr uint32_t kAiCheckViability = 1u << 1;
inline constexpr uint32_t kAiTryToFaint = 1u << 2;
inline constexpr uint32_t kAiPreferStrongest = 1u << 5;

void moveUsePct(uint8_t dmgGen, uint8_t chart, uint32_t aiFlags, const Pokemon& foe,
    const Pokemon& player, const uint16_t moveIds[4], const Field& field, int pct[4]);

}