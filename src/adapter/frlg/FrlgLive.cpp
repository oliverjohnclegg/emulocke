#include "adapter/frlg/FrlgLive.hpp"

#include "adapter/frlg/CfruExpanded.hpp"
#include "adapter/frlg/FrlgBattle.hpp"
#include "adapter/frlg/FrlgLayout.hpp"
#include "adapter/frlg/FrlgNames.hpp"
#include "adapter/frlg/FrlgSave.hpp"
#include "adapter/gen3/BoxMon.hpp"
#include "adapter/gen3/Codec.hpp"

#include <array>
#include <cstdio>
#include <span>

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

bool copy(const LiveMemory& mem, uint32_t addr, std::span<uint8_t> out) {
    return mem.read(addr, out);
}

}  // namespace

void fillSnapshotFromFrlgLive(const LiveMemory& mem, GameSnapshot& snap) {
    const uint32_t sb2 = livePtr(mem, kFrlgSaveBlock2Ptr, kFrlgSaveBlock2, kFrlgSaveBlock2Size);
    const uint32_t sb1 = livePtr(mem, kFrlgSaveBlock1Ptr, kFrlgSaveBlock1, kFrlgSaveBlock1Size);

    std::array<uint8_t, kFrlgSaveBlock2Size> block2{};
    if (copy(mem, sb2, block2)) {
        decodeGen3Text({block2.data(), 7}, snap.trainer.name, sizeof(snap.trainer.name));
        snap.trainer.gender = block2[8];
        snap.trainer.trainerId = load32(block2.data() + 0x0A);
        snap.trainer.playHours = load16(block2.data() + 0x0E);
        snap.trainer.playMinutes = block2[0x10];
        snap.trainer.playSeconds = block2[0x11];
    }

    auto pullParty = [&](uint32_t addr) {
        std::array<uint8_t, kPartyMonSize * 6> party{};
        if (!copy(mem, addr, party)) {
            return;
        }
        for (uint8_t i = 0; i < 6; ++i) {
            DecryptedMon dec;
            if (!decryptPartyMon({party.data() + i * kPartyMonSize, kPartyMonSize}, dec)) {
                continue;
            }
            snap.party.mons[i] = toSnapshotMon(dec);
        }
    };
    pullParty(kFrlgParty);
    uint8_t count = 0;
    mem.read(kFrlgPartyCount, {&count, 1});
    if (count > 6) {
        count = 6;
    }
    if (snap.party.mons[0].species == 0) {
        pullParty(sb1 + kFrlgPartyOff);
        count = 0;
        mem.read(sb1 + kFrlgPartyCountOff, {&count, 1});
        if (count > 6) {
            count = 6;
        }
    }
    if (count == 0) {
        for (uint8_t i = 0; i < 6; ++i) {
            if (snap.party.mons[i].species != 0) {
                count = static_cast<uint8_t>(i + 1);
            }
        }
    }
    snap.party.count = count;

    uint8_t loc[2]{};
    if (copy(mem, sb1 + kFrlgMapGroupOff, loc)) {
        snap.overworld.mapGroup = loc[0];
        snap.overworld.mapNum = loc[1];
        char scratch[32];
        std::snprintf(snap.overworld.mapName, sizeof(snap.overworld.mapName), "%s",
                      frlgMapName(loc[0], loc[1], scratch, sizeof(scratch)));
    }

    std::array<uint8_t, kFrlgSaveBlock1Size> block1{};
    if (copy(mem, sb1, block1)) {
        std::array<uint8_t, kFrlgStorageSize> pc{};
        const uint32_t storage = livePtr(mem, kFrlgStoragePtr, kFrlgStorage, kFrlgStorageSize);
        if (copy(mem, storage, pc)) {
            fillFrlgBoxes(pc, snap.boxes);
        }
        fillFrlgProgress(block1.data(), snap);
        snap.gyms.slots = kFrlgBadgeCount;
        snap.gyms.earned = block1[kFrlgBadgeByteOff];
    }
    fillFrlgBattle(mem, snap);
    fillCfruDifficultyLive(mem, snap);
    snap.ok = true;
}

}
