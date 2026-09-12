#pragma once

#include "adapter/Snapshot.hpp"

#include <array>
#include <cstdint>
#include <span>
#include <vector>

namespace emulocke {

struct FrlgSaveBlocks {
    std::array<uint8_t, 0xF24> block2{};
    std::array<uint8_t, 0x3D68> block1{};
    std::array<uint8_t, 0x83D0> storage{};
};

bool readFrlgSave(std::span<const uint8_t> sav, FrlgSaveBlocks& out);
std::vector<uint8_t> writeFrlgSave(const FrlgSaveBlocks& blocks);
void fillSnapshotFromFrlg(const FrlgSaveBlocks& blocks, GameSnapshot& snap);

}