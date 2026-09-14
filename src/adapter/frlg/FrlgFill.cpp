#include "adapter/frlg/FrlgSave.hpp"

#include "adapter/frlg/CfruExpanded.hpp"
#include "adapter/frlg/FrlgLayout.hpp"
#include "adapter/frlg/FrlgNames.hpp"
#include "adapter/gen3/BoxMon.hpp"
#include "adapter/gen3/Codec.hpp"

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
    party.count = block1[kFrlgPartyCountOff];
    if (party.count > 6) {
        party.count = 6;
    }
    for (uint8_t i = 0; i < 6; ++i) {
        DecryptedMon dec;
        if (!decryptPartyMon({block1 + kFrlgPartyOff + i * kPartyMonSize, kPartyMonSize}, dec)) {
            continue;
        }
        party.mons[i] = toSnapshotMon(dec);
    }
}

void readGyms(const uint8_t* block1, Gyms& gyms) {
    gyms.slots = kFrlgBadgeCount;
    gyms.earned = block1[kFrlgBadgeByteOff];
}

}  // namespace

void fillFrlgBoxes(std::span<const uint8_t> storage, Boxes& boxes) {
    if (storage.size() < kFrlgStorageSize) {
        return;
    }
    boxes.current = storage[0];
    for (int b = 0; b < 14; ++b) {
        decodeGen3Text({storage.data() + kFrlgBoxNameOff + b * 9, 8}, boxes.boxes[b].name,
                       sizeof(boxes.boxes[b].name));
        for (int s = 0; s < 30; ++s) {
            DecryptedMon dec;
            const uint8_t* raw = storage.data() + kFrlgBoxStart + (b * 30 + s) * kBoxMonSize;
            if (!decryptBoxMon({raw, kBoxMonSize}, dec)) {
                continue;
            }
            boxes.boxes[b].mons[s] = toSnapshotMon(dec);
        }
    }
}

void fillFrlgProgress(const uint8_t* block1, GameSnapshot& snap) {
    std::memcpy(snap.progress.flags.data(), block1 + kFrlgFlagsOff, kFrlgFlagBytes);
    snap.progress.badges = 0;
    for (uint8_t i = 0; i < 8; ++i) {
        if (progressFlag(snap.progress, static_cast<uint16_t>(kFrlgFlagBadge1 + i))) {
            snap.progress.badges = static_cast<uint8_t>(snap.progress.badges | (1u << i));
        }
    }
    snap.progress.starterSpecies = 0;
    auto take = [&](const Mon& mon) {
        if (snap.progress.starterSpecies != 0 || mon.egg) {
            return;
        }
        if (mon.species == 1 || mon.species == 4 || mon.species == 7) {
            snap.progress.starterSpecies = mon.species;
        }
    };
    for (uint8_t i = 0; i < snap.party.count; ++i) {
        take(snap.party.mons[i]);
    }
    for (const PcBox& box : snap.boxes.boxes) {
        for (const Mon& mon : box.mons) {
            take(mon);
        }
    }
}

void fillSnapshotFromFrlg(const FrlgSaveBlocks& blocks, GameSnapshot& snap) {
    readTrainer(blocks.block2.data(), snap.trainer);
    readParty(blocks.block1.data(), snap.party);
    fillFrlgBoxes(blocks.storage, snap.boxes);
    readGyms(blocks.block1.data(), snap.gyms);
    snap.overworld.mapGroup = blocks.block1[kFrlgMapGroupOff];
    snap.overworld.mapNum = blocks.block1[kFrlgMapNumOff];
    char scratch[32];
    const char* name = frlgMapName(snap.overworld.mapGroup, snap.overworld.mapNum, scratch, sizeof(scratch));
    std::snprintf(snap.overworld.mapName, sizeof(snap.overworld.mapName), "%s", name);
    fillFrlgProgress(blocks.block1.data(), snap);
    fillCfruDifficulty(blocks, snap);
    snap.ok = true;
}

}
