#include "adapter/rse/RseSave.hpp"

#include "adapter/gen3/BoxMon.hpp"
#include "adapter/gen3/Codec.hpp"
#include "adapter/rse/RseLayout.hpp"

#include <cstring>

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

void readBoxes(const uint8_t* storage, Boxes& boxes) {
    boxes.current = storage[0];
    for (int b = 0; b < 14; ++b) {
        decodeGen3Text({storage + kRseBoxNameOff + b * 9, 8}, boxes.boxes[b].name, sizeof(boxes.boxes[b].name));
        for (int s = 0; s < 30; ++s) {
            DecryptedMon dec;
            const uint8_t* raw = storage + kRseBoxStart + (b * 30 + s) * kBoxMonSize;
            if (!decryptBoxMon({raw, kBoxMonSize}, dec)) {
                continue;
            }
            boxes.boxes[b].mons[s] = toSnapshotMon(dec);
        }
    }
}

}  // namespace

void fillSnapshotFromRse(const RseSaveBlocks& blocks, GameSnapshot& snap) {
    readTrainer(blocks.block2.data(), snap.trainer);
    readParty(blocks.block1.data(), snap.party);
    readBoxes(blocks.storage.data(), snap.boxes);
    snap.ok = true;
}

}
