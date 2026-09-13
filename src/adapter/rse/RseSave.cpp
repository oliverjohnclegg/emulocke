#include "adapter/rse/RseSave.hpp"

#include "adapter/gen3/Codec.hpp"
#include "adapter/rse/RseLayout.hpp"

#include <cstring>

namespace emulocke {
namespace {

constexpr uint32_t kSignature = 0x08012025;
constexpr int kSectorSize = 0x1000;
constexpr int kSectorData = 3968;
constexpr int kPerSlot = 14;

uint16_t sectorChecksum(const uint8_t* data) {
    uint32_t sum = 0;
    for (int i = 0; i < 0xF80 / 4; ++i) {
        sum += load32(data + i * 4);
    }
    return static_cast<uint16_t>((sum >> 16) + sum);
}

bool validSector(const uint8_t* sec, uint16_t expectId) {
    return load32(sec + 0xFF8) == kSignature && load16(sec + 0xFF4) == expectId &&
           load16(sec + 0xFF6) == sectorChecksum(sec);
}

void chunkDest(RseSaveBlocks& blocks, int id, uint8_t*& dest, uint16_t& size) {
    if (id == 0) {
        dest = blocks.block2.data();
        size = static_cast<uint16_t>(blocks.block2.size());
    } else if (id <= 4) {
        dest = blocks.block1.data() + static_cast<std::size_t>(id - 1) * kSectorData;
        const std::size_t remain = blocks.block1.size() - static_cast<std::size_t>(id - 1) * kSectorData;
        size = static_cast<uint16_t>(remain < kSectorData ? remain : kSectorData);
    } else {
        dest = blocks.storage.data() + static_cast<std::size_t>(id - 5) * kSectorData;
        const std::size_t remain = blocks.storage.size() - static_cast<std::size_t>(id - 5) * kSectorData;
        size = static_cast<uint16_t>(remain < kSectorData ? remain : kSectorData);
    }
}

}  // namespace

bool readRseSave(std::span<const uint8_t> sav, RseSaveBlocks& out) {
    if (sav.size() < kRseSaveSize) {
        return false;
    }
    int bestSlot = -1;
    uint32_t bestCounter = 0;
    for (int slot = 0; slot < 2; ++slot) {
        uint32_t counter = 0;
        bool ok = true;
        for (int id = 0; id < kPerSlot; ++id) {
            bool found = false;
            for (int i = 0; i < kPerSlot; ++i) {
                const uint8_t* sec = sav.data() + static_cast<std::size_t>(slot * kPerSlot + i) * kSectorSize;
                if (!validSector(sec, static_cast<uint16_t>(id))) {
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
    if (bestSlot < 0) {
        return false;
    }
    out = RseSaveBlocks{};
    for (int i = 0; i < kPerSlot; ++i) {
        const uint8_t* sec = sav.data() + static_cast<std::size_t>(bestSlot * kPerSlot + i) * kSectorSize;
        const uint16_t id = load16(sec + 0xFF4);
        if (id >= kPerSlot || !validSector(sec, id)) {
            continue;
        }
        uint8_t* dest = nullptr;
        uint16_t size = 0;
        chunkDest(out, id, dest, size);
        std::memcpy(dest, sec, size);
    }
    return true;
}

std::vector<uint8_t> writeRseSave(const RseSaveBlocks& blocks) {
    std::vector<uint8_t> sav(kRseSaveSize, 0);
    for (int id = 0; id < kPerSlot; ++id) {
        uint8_t* dest = sav.data() + static_cast<std::size_t>(id) * kSectorSize;
        uint8_t* src = nullptr;
        uint16_t size = 0;
        RseSaveBlocks copy = blocks;
        chunkDest(copy, id, src, size);
        std::memcpy(dest, src, size);
        store16(dest + 0xFF4, static_cast<uint16_t>(id));
        store16(dest + 0xFF6, sectorChecksum(dest));
        store32(dest + 0xFF8, kSignature);
        store32(dest + 0xFFC, 0);
    }
    return sav;
}

}
