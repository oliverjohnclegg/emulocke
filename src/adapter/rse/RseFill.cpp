#include "adapter/rse/RseSave.hpp"

#include "adapter/ProgressFill.hpp"
#include "adapter/gen3/BoxMon.hpp"
#include "adapter/gen3/Codec.hpp"
#include "adapter/rse/RseLayout.hpp"

#include <cstdio>
#include <cstring>
#include <span>

namespace emulocke {
namespace {

void readTrainer(const uint8_t* block2, Trainer& trainer) {
    decodeGen3Text({block2, 7}, trainer.name, sizeof(trainer.name));
    trainer.gender = block2[8];
    trainer.trainerId = load32(block2 + 0x0A);
    trainer.playHours = load16(block2 + 0x0E);
    trainer.playMinutes = block2[0x10];
    trainer.playSeconds = block2[0x11];
}

void readParty(const uint8_t* block1, Party& party) {
    party.count = block1[kRsePartyCountOff];
    if (party.count > 6) {
        party.count = 6;
    }
    for (uint8_t i = 0; i < 6; ++i) {
        DecryptedMon dec;
        if (!decryptPartyMon({block1 + kRsePartyOff + i * kPartyMonSize, kPartyMonSize}, dec)) {
            continue;
        }
        party.mons[i] = toSnapshotMon(dec);
    }
}

}  // namespace

void fillRseBoxes(std::span<const uint8_t> storage, Boxes& boxes) {
    if (storage.size() < kRseStorageSize) {
        return;
    }
    boxes.current = storage[0];
    for (int b = 0; b < 14; ++b) {
        decodeGen3Text({storage.data() + kRseBoxNameOff + b * 9, 8}, boxes.boxes[b].name,
            sizeof(boxes.boxes[b].name));
        for (int s = 0; s < 30; ++s) {
            DecryptedMon dec;
            const uint8_t* raw = storage.data() + kRseBoxStart + (b * 30 + s) * kBoxMonSize;
            if (!decryptBoxMon({raw, kBoxMonSize}, dec)) {
                continue;
            }
            boxes.boxes[b].mons[s] = toSnapshotMon(dec);
        }
    }
}

void fillRseMap(const uint8_t* block1, Overworld& overworld) {
    overworld.mapGroup = block1[kRseMapGroupOff];
    overworld.mapNum = block1[kRseMapNumOff];
    std::snprintf(overworld.mapName, sizeof(overworld.mapName), "MAP %u-%u", overworld.mapGroup,
        overworld.mapNum);
}

void fillRseProgress(GameSnapshot& snap, const uint8_t* block1, bool emerald) {
    const std::size_t flagsOff = emerald ? kRseFlagsOffEm : kRseFlagsOffRs;
    fillFlagBank(snap, block1 + flagsOff, kFlagBankBytes);
    const uint16_t badge1 = emerald ? kRseBadge1Em : kRseBadge1Rs;
    uint8_t earned = 0;
    for (uint8_t i = 0; i < 8; ++i) {
        if (progressFlag(snap.progress, static_cast<uint16_t>(badge1 + i))) {
            earned = static_cast<uint8_t>(earned | (1u << i));
        }
    }
    fillGymsFromByte(snap, earned);
    if (emerald) {
        const uint16_t code = load16(block1 + kRseVarsOffEm + static_cast<std::size_t>(kRseDifficultyVar - 0x4000) * 2);
        if (code <= 3) {
            writeDifficultyCode(snap, static_cast<uint8_t>(code));
        }
    }
    static constexpr uint16_t kNat[] = {252, 255, 258};
    static constexpr uint16_t kInt[] = {277, 280, 283};
    fillStarterSpecies(snap, kNat);
    if (snap.progress.starterSpecies == 0) {
        fillStarterSpecies(snap, kInt);
        if (snap.progress.starterSpecies >= 277 && snap.progress.starterSpecies <= 411) {
            snap.progress.starterSpecies = static_cast<uint16_t>(snap.progress.starterSpecies - 25);
        }
    }
}

void fillSnapshotFromRse(const RseSaveBlocks& blocks, GameSnapshot& snap, bool emerald) {
    readTrainer(blocks.block2.data(), snap.trainer);
    readParty(blocks.block1.data(), snap.party);
    fillRseBoxes(blocks.storage, snap.boxes);
    fillRseMap(blocks.block1.data(), snap.overworld);
    fillRseProgress(snap, blocks.block1.data(), emerald);
    snap.ok = true;
}

}