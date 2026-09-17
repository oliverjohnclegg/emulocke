#pragma once

#include "adapter/LiveMemory.hpp"
#include "adapter/Snapshot.hpp"

#include <cstddef>
#include <cstdint>
#include <span>

namespace emulocke {

inline constexpr std::size_t kBtlPokeparamSize = 548;
inline constexpr std::size_t kBtlPokeparamView = 400;
inline constexpr std::size_t kBtlPokeparamStat = 226;
inline constexpr std::size_t kBtlPokeparamLevel = 12;

bool readBtlHp(std::span<const uint8_t> raw, uint16_t maxHp, uint16_t seedHp, uint16_t& hp,
    uint16_t atk = 0, uint16_t def = 0);
bool readBtlCoreHp(std::span<const uint8_t> raw, uint16_t species, uint16_t& hp, uint16_t atk = 0,
    uint16_t def = 0);
bool readBtlLiveHp(std::span<const uint8_t> raw, uint16_t species, uint16_t maxHp, uint16_t seedHp,
    uint16_t& hp, uint16_t atk = 0, uint16_t def = 0);
bool considerBtl(BattleBattler& best, bool& got, uint16_t seedHp, uint16_t species, uint16_t hp,
    uint16_t maxHp);
bool readBtlPokeparam(std::span<const uint8_t> raw, uint16_t species, uint16_t maxHp,
    BattleBattler& out, uint16_t level = 0);
void overlayGen5Pokeparam(const LiveMemory& mem, GameSnapshot& snap);
void resetGen5Pokeparam();

}
