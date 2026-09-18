#pragma once

#include "adapter/LiveMemory.hpp"
#include "adapter/Snapshot.hpp"
#include "adapter/frlg/FrlgSave.hpp"

#include <cstdint>

namespace emulocke {

inline constexpr uint32_t kCfruExpandedFlagsAddr = 0x0203B174;
inline constexpr uint32_t kCfruExpandedVarsAddr = 0x0203B374;
inline constexpr uint16_t kUnboundDifficultyVar = 0x50DF;
inline constexpr uint16_t kRrFlagEasy = 0x1033;
inline constexpr uint16_t kRrFlagHardcore = 0x1034;
inline constexpr uint16_t kRrFlagRestrict = 0x103C;
inline constexpr uint32_t kUnboundSignature210 = 0x01121999;
inline constexpr uint32_t kUnboundSignature200 = 0x01121998;
inline constexpr uint32_t kUnboundSignature = 0x01122000;

inline bool unboundSave(uint32_t signature) {
    return signature == kUnboundSignature210 || signature == kUnboundSignature200 ||
           signature == kUnboundSignature;
}

void copyCfruParasite(const uint8_t* sector, uint16_t id, FrlgSaveBlocks& out);
void fillCfruDifficulty(const FrlgSaveBlocks& blocks, GameSnapshot& snap);
void fillCfruDifficultyLive(const LiveMemory& mem, GameSnapshot& snap);

}
