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
    std::array<uint8_t, 0x200> expandedFlags{};
    std::array<uint8_t, 0x200> expandedVars{};
    uint32_t fileSignature{};
};

bool readFrlgSave(std::span<const uint8_t> sav, FrlgSaveBlocks& out);
std::vector<uint8_t> writeFrlgSave(const FrlgSaveBlocks& blocks);
void fillFrlgBoxes(std::span<const uint8_t> storage, Boxes& boxes);
void fillFrlgProgress(const uint8_t* block1, GameSnapshot& snap);
void fillSnapshotFromFrlg(const FrlgSaveBlocks& blocks, GameSnapshot& snap);

}