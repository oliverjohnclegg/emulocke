#pragma once

#include "adapter/Snapshot.hpp"

#include <array>
#include <cstdint>
#include <span>
#include <vector>

namespace emulocke {

struct RseSaveBlocks {
    std::array<uint8_t, 0xF80> block2{};
    std::array<uint8_t, 0x3D88> block1{};
    std::array<uint8_t, 0x83D0> storage{};
};

bool readRseSave(std::span<const uint8_t> sav, RseSaveBlocks& out);
std::vector<uint8_t> writeRseSave(const RseSaveBlocks& blocks);
void fillSnapshotFromRse(const RseSaveBlocks& blocks, GameSnapshot& snap);

}
