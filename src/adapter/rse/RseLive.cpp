#include "adapter/rse/RseLive.hpp"

#include "adapter/gen3/BoxMon.hpp"
#include "adapter/gen3/Codec.hpp"
#include "adapter/rse/RseBattle.hpp"
#include "adapter/rse/RseLayout.hpp"
#include "adapter/rse/RseSave.hpp"

#include <array>

namespace emulocke {
namespace {

bool inEwram(uint32_t addr, std::size_t size) {
    return addr >= 0x02000000 && addr + size <= 0x02040000;
}

uint32_t livePtr(const LiveMemory& mem, uint32_t ptrAddr, uint32_t fallback, std::size_t size) {
    const uint32_t p = mem.read32(ptrAddr);
    if (inEwram(p, size)) {
        return p;
    }
    return fallback;
}

}  // namespace

void fillSnapshotFromRseLive(const LiveMemory& mem, GameSnapshot& snap, bool emerald) {
    const uint32_t sb2 = emerald ? livePtr(mem, kEmSaveBlock2Ptr, kEmSaveBlock2, kRseSaveBlock2Size) : kRsSaveBlock2;
    const uint32_t sb1 = emerald ? livePtr(mem, kEmSaveBlock1Ptr, kEmSaveBlock1, kRseSaveBlock1Size) : kRsSaveBlock1;
    const uint32_t partyAddr = emerald ? kEmParty : kRsParty;
    const uint32_t countAddr = emerald ? kEmPartyCount : kRsPartyCount;
    const uint32_t storage = emerald ? livePtr(mem, kEmStoragePtr, kEmStorage, kRseStorageSize) : kRsStorage;

    std::array<uint8_t, kRseSaveBlock2Size> block2{};
    if (mem.read(sb2, block2)) {
        decodeGen3Text({block2.data(), 7}, snap.trainer.name, sizeof(snap.trainer.name));
        snap.trainer.gender = block2[8];
        snap.trainer.trainerId = load32(block2.data() + 0x0A);
        snap.trainer.playHours = load16(block2.data() + 0x0E);
        snap.trainer.playMinutes = block2[0x10];
        snap.trainer.playSeconds = block2[0x11];
    }

    uint8_t count = 0;
    mem.read(countAddr, {&count, 1});
    if (count > 6) {
        count = 6;
    }
    snap.party.count = count;
    std::array<uint8_t, kPartyMonSize * 6> party{};
    if (mem.read(partyAddr, party)) {
        for (uint8_t i = 0; i < 6; ++i) {
            DecryptedMon dec;
            if (!decryptPartyMon({party.data() + i * kPartyMonSize, kPartyMonSize}, dec)) {
                continue;
            }
            snap.party.mons[i] = toSnapshotMon(dec);
        }
    }
    std::array<uint8_t, kRseSaveBlock1Size> block1{};
    if (mem.read(sb1, block1)) {
        fillRseMap(block1.data(), snap.overworld);
        fillRseProgress(snap, block1.data(), emerald);
    }
    std::array<uint8_t, kRseStorageSize> pc{};
    if (mem.read(storage, pc)) {
        fillRseBoxes(pc, snap.boxes);
    }
    fillRseBattle(mem, snap, emerald);
    snap.ok = snap.party.count > 0;
}

}
