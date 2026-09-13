#include "adapter/gen5/Save.hpp"

#include "adapter/gen3/Codec.hpp"
#include "adapter/gen45/Pk.hpp"

#include <array>

namespace emulocke {
namespace {

void readTrainer(const uint8_t* t, Trainer& trainer) {
    decodeUtf16Text({t + 4, 16}, trainer.name, sizeof(trainer.name));
    trainer.trainerId = load32(t + 0x14);
    trainer.gender = t[0x21];
    trainer.playHours = load16(t + 0x24);
    trainer.playMinutes = t[0x26];
    trainer.playSeconds = t[0x27];
}

void readParty(const uint8_t* sav, Party& party) {
    party.count = sav[kGen5Party + 4];
    if (party.count > 6) {
        party.count = 6;
    }
    for (uint8_t i = 0; i < 6; ++i) {
        parsePk45({sav + kGen5Party + 8 + i * kPk5PartySize, kPk5PartySize}, true, party.mons[i]);
    }
}

void readBoxes(const uint8_t* sav, Boxes& boxes) {
    boxes.current = sav[0];
    for (int b = 0; b < 24; ++b) {
        decodeUtf16Text({sav + 4 + static_cast<std::size_t>(b) * 0x28, 20}, boxes.boxes[b].name,
                        sizeof(boxes.boxes[b].name));
        const std::size_t boxOff = kGen5Box + static_cast<std::size_t>(b) * (kPkStoredSize * 30 + 0x10);
        for (int s = 0; s < 30; ++s) {
            parsePk45({sav + boxOff + s * kPkStoredSize, kPkStoredSize}, true, boxes.boxes[b].mons[s]);
        }
    }
}

}  // namespace

bool readGen5Save(std::span<const uint8_t> sav, GameSnapshot& snap) {
    if (sav.size() < kGen5Trainer + 0x30) {
        return false;
    }
    readTrainer(sav.data() + kGen5Trainer, snap.trainer);
    readParty(sav.data(), snap.party);
    readBoxes(sav.data(), snap.boxes);
    snap.ok = snap.trainer.name[0] != 0 || snap.party.count > 0;
    return snap.ok;
}

bool fillGen5Live(const LiveMemory& mem, uint32_t partyAddr, GameSnapshot& snap) {
    uint8_t count = 0;
    if (!mem.read(partyAddr + 4, {&count, 1}) || count == 0 || count > 6) {
        return false;
    }
    snap.party.count = count;
    std::array<uint8_t, kPk5PartySize * 6> party{};
    if (!mem.read(partyAddr + 8, party)) {
        return false;
    }
    int valid = 0;
    for (uint8_t i = 0; i < 6; ++i) {
        if (parsePk45({party.data() + i * kPk5PartySize, kPk5PartySize}, true, snap.party.mons[i])) {
            ++valid;
        }
    }
    snap.ok = valid > 0;
    return snap.ok;
}

}
