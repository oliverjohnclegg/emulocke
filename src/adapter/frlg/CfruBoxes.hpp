#pragma once

#include "adapter/LiveMemory.hpp"
#include "adapter/frlg/FrlgSave.hpp"
#include "adapter/gen3/BoxMon.hpp"

#include <cstddef>
#include <cstdint>
#include <span>

namespace emulocke {

inline constexpr std::size_t kCfruBoxMonSize = 58;
inline constexpr int kCfruPackedBoxes = 19;
inline constexpr int kCfruBoxCount = 25;
inline constexpr std::size_t kCfruBoxBytes = 30 * kCfruBoxMonSize;
inline constexpr uint32_t kCfruBox20Live = 0x0203CB44;
inline constexpr uint32_t kCfruBox23Live = 0x02027434;
inline constexpr uint32_t kCfruBox25Live = 0x02024638;
inline constexpr std::size_t kCfruFlash30BoxOff = 0xB0C;
inline constexpr std::size_t kCfruFlash30BoxLen = 0x4E4;
inline constexpr std::size_t kCfruFlash31BoxLen = 0xF80;
inline constexpr std::size_t kCfruBox25Off = 0xB0;
inline constexpr std::size_t kCfruSb1Chunk = 3968;
inline constexpr std::size_t kCfruBox23Sec2Off = 0xF18;
inline constexpr std::size_t kCfruBox23Sec2Head = 0x68;
inline constexpr std::size_t kCfruBox23Sec3Len = 0xCC0;

bool decodeCfruBoxMon(std::span<const uint8_t> raw, DecryptedMon& out);
bool cfruPackedMon(std::span<const uint8_t> raw);
bool cfruPackedStorage(std::span<const uint8_t> storage);
void fillCfruPackedBoxes(std::span<const uint8_t> storage, Boxes& boxes);
void fillCfruSaveExtraBoxes(const FrlgSaveBlocks& blocks, Boxes& boxes);
void fillCfruLiveExtraBoxes(const LiveMemory& mem, Boxes& boxes);

}
