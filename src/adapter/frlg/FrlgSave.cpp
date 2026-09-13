#include "adapter/frlg/FrlgSave.hpp"

#include "adapter/frlg/FrlgLayout.hpp"
#include "adapter/gen3/Codec.hpp"

#include <cstring>

namespace emulocke {
namespace {

constexpr uint32_t kSignature = 0x08012025;
constexpr int kSectorSize = 0x1000;
constexpr int kSectorData = 3968;
constexpr int kPerSlot = 14;
constexpr uint16_t kChunkSize[14] = {
    0xF24, 3968, 3968, 3968, 3816, 3968, 3968, 3968, 3968, 3968, 3968, 3968, 3968, 2000,
};

uint16_t sectorChecksum(const uint8_t* data, uint16_t size) {
    uint32_t sum = 0;
    for (uint16_t i = 0; i < size / 4; ++i) {
        sum += load32(data + i * 4);
    }
    return static_cast<uint16_t>((sum >> 16) + sum);
}

const uint8_t* sectorBytes(std::span<const uint8_t> sav, int physical) {
    return sav.data() + static_cast<std::size_t>(physical) * kSectorSize;
}

bool sectorFooterOk(const uint8_t* sec, uint16_t expectId) {
    const uint32_t sig = load32(sec + 0xFF8);
    return sig != 0 && sig != 0xFFFFFFFFu && load16(sec + 0xFF4) == expectId;
}

bool sectorChecksumOk(const uint8_t* sec, uint16_t expectId) {
    return load16(sec + 0xFF6) == sectorChecksum(sec, kChunkSize[expectId]);
}

bool validSector(const uint8_t* sec, uint16_t expectId, bool needChecksum) {
    if (!sectorFooterOk(sec, expectId)) {
        return false;
    }
    return !needChecksum || sectorChecksumOk(sec, expectId);
}

void chunkDest(FrlgSaveBlocks& blocks, int id, uint8_t*& dest, uint16_t& size) {
    size = kChunkSize[id];
    if (id == 0) {
        dest = blocks.block2.data();
    } else if (id <= 4) {
        dest = blocks.block1.data() + static_cast<std::size_t>(id - 1) * kSectorData;
    } else {
        dest = blocks.storage.data() + static_cast<std::size_t>(id - 5) * kSectorData;
    }
}

int pickFrlgSlot(std::span<const uint8_t> sav, bool needChecksum) {
    int bestSlot = -1;
    uint32_t bestCounter = 0;
    for (int slot = 0; slot < 2; ++slot) {
        uint32_t counter = 0;
        bool ok = true;
        for (int id = 0; id < kPerSlot; ++id) {
            bool found = false;
            for (int i = 0; i < kPerSlot; ++i) {
                const uint8_t* sec = sectorBytes(sav, slot * kPerSlot + i);
                if (!validSector(sec, static_cast<uint16_t>(id), needChecksum)) {
                    continue;
                }
                counter = load32(sec + 0xFFC);
                found = true;
                break;
            }
            if (!found) {
                ok = false;
                break;
            }
        }
        if (ok && (bestSlot < 0 || counter >= bestCounter)) {
            bestSlot = slot;
            bestCounter = counter;
        }
    }
    return bestSlot;
}

}  // namespace

bool readFrlgSave(std::span<const uint8_t> sav, FrlgSaveBlocks& out) {
    if (sav.size() < kFrlgSaveSize) {
        return false;
    }
    int bestSlot = pickFrlgSlot(sav, true);
    if (bestSlot < 0) {
        bestSlot = pickFrlgSlot(sav, false);
    }
    if (bestSlot < 0) {
        return false;
    }
    out = FrlgSaveBlocks{};
    for (int i = 0; i < kPerSlot; ++i) {
        const uint8_t* sec = sectorBytes(sav, bestSlot * kPerSlot + i);
        const uint16_t id = load16(sec + 0xFF4);
        if (id >= kPerSlot || !sectorFooterOk(sec, id)) {
            continue;
        }
        uint8_t* dest = nullptr;
        uint16_t size = 0;
        chunkDest(out, id, dest, size);
        std::memcpy(dest, sec, size);
    }
    return true;
}

std::vector<uint8_t> writeFrlgSave(const FrlgSaveBlocks& blocks) {
    std::vector<uint8_t> sav(kFrlgSaveSize, 0);
    for (int id = 0; id < kPerSlot; ++id) {
        uint8_t* dest = sav.data() + static_cast<std::size_t>(id) * kSectorSize;
        uint8_t* src = nullptr;
        uint16_t size = 0;
        FrlgSaveBlocks copy = blocks;
        chunkDest(copy, id, src, size);
        std::memcpy(dest, src, size);
        store16(dest + 0xFF4, static_cast<uint16_t>(id));
        store16(dest + 0xFF6, sectorChecksum(dest, size));
        store32(dest + 0xFF8, kSignature);
        store32(dest + 0xFFC, 0);
    }
    return sav;
}

}