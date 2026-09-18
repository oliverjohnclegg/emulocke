#include "adapter/frlg/CfruBoxes.hpp"

#include "adapter/frlg/FrlgLayout.hpp"
#include "adapter/gen3/Codec.hpp"

#include <array>
#include <cstring>

namespace emulocke {
namespace {

void fillPackedMons(const uint8_t* raw, int nBoxes, int first, Boxes& boxes) {
    for (int b = 0; b < nBoxes; ++b) {
        const int box = first + b;
        if (box >= kMaxBoxes) {
            return;
        }
        for (int s = 0; s < 30; ++s) {
            DecryptedMon dec;
            const uint8_t* slot = raw + (static_cast<std::size_t>(b) * 30 + static_cast<std::size_t>(s)) * kCfruBoxMonSize;
            if (decodeCfruBoxMon({slot, kCfruBoxMonSize}, dec)) {
                boxes.boxes[static_cast<std::size_t>(box)].mons[static_cast<std::size_t>(s)] = toSnapshotMon(dec);
            }
        }
    }
}

}  // namespace

void fillCfruPackedBoxes(std::span<const uint8_t> storage, Boxes& boxes) {
    const std::size_t packedBytes = 4 + static_cast<std::size_t>(kCfruPackedBoxes) * kCfruBoxBytes;
    if (storage.size() < packedBytes) {
        return;
    }
    boxes.current = storage[0];
    for (int b = 0; b < kCfruBoxCount && b < kMaxBoxes; ++b) {
        const std::size_t off = b < 14 ? kFrlgBoxNameOff + static_cast<std::size_t>(b) * 9
                                       : kFrlgBoxNameOff - static_cast<std::size_t>(b - 13) * 9;
        if (off + 8 > storage.size()) {
            continue;
        }
        decodeGen3Text({storage.data() + off, 8}, boxes.boxes[static_cast<std::size_t>(b)].name,
                       sizeof(boxes.boxes[static_cast<std::size_t>(b)].name));
    }
    fillPackedMons(storage.data() + 4, kCfruPackedBoxes, 0, boxes);
}

void fillCfruSaveExtraBoxes(const FrlgSaveBlocks& blocks, Boxes& boxes) {
    std::array<uint8_t, 3 * kCfruBoxBytes> box20{};
    std::memcpy(box20.data(), blocks.flash30.data() + kCfruFlash30BoxOff, kCfruFlash30BoxLen);
    std::memcpy(box20.data() + kCfruFlash30BoxLen, blocks.flash31.data(), kCfruFlash31BoxLen);
    fillPackedMons(box20.data(), 3, 19, boxes);

    std::array<uint8_t, 2 * kCfruBoxBytes> box23{};
    const uint8_t* sec2 = blocks.block1.data() + kCfruSb1Chunk;
    std::memcpy(box23.data(), sec2 + kCfruBox23Sec2Off, kCfruBox23Sec2Head);
    std::memcpy(box23.data() + kCfruBox23Sec2Head, blocks.sector2Tail.data(), blocks.sector2Tail.size());
    std::memcpy(box23.data() + kCfruBox23Sec2Head + blocks.sector2Tail.size(),
                blocks.block1.data() + 2 * kCfruSb1Chunk, kCfruBox23Sec3Len);
    fillPackedMons(box23.data(), 2, 22, boxes);
    fillPackedMons(blocks.block2.data() + kCfruBox25Off, 1, 24, boxes);
}

void fillCfruLiveExtraBoxes(const LiveMemory& mem, Boxes& boxes) {
    std::array<uint8_t, 3 * kCfruBoxBytes> box20{};
    if (mem.read(kCfruBox20Live, box20)) {
        fillPackedMons(box20.data(), 3, 19, boxes);
    }
    std::array<uint8_t, 2 * kCfruBoxBytes> box23{};
    if (mem.read(kCfruBox23Live, box23)) {
        fillPackedMons(box23.data(), 2, 22, boxes);
    }
    std::array<uint8_t, kCfruBoxBytes> box25{};
    if (mem.read(kCfruBox25Live, box25)) {
        fillPackedMons(box25.data(), 1, 24, boxes);
    }
}

}
