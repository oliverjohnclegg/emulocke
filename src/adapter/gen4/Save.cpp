#include "adapter/gen4/Save.hpp"

#include "adapter/ProgressFill.hpp"
#include "adapter/gen3/Codec.hpp"
#include "adapter/gen45/Pk.hpp"

#include <array>
#include <cstring>

namespace emulocke {
namespace {

constexpr uint32_t kFooterMagicOffDp = 12;
constexpr uint32_t kFooterCountOffDp = 4;
constexpr uint32_t kFooterMagicOffHg = 8;

int activePartition(std::span<const uint8_t> sav, std::size_t generalSize, std::size_t footerSize) {
    int best = -1;
    uint32_t bestCount = 0;
    for (int slot = 0; slot < 2; ++slot) {
        const std::size_t base = static_cast<std::size_t>(slot) * kGen4Partition;
        const std::size_t fo = base + generalSize - footerSize;
        if (fo + footerSize > sav.size()) {
            continue;
        }
        const uint32_t magicOff = footerSize == 0x10 ? kFooterMagicOffHg : kFooterMagicOffDp;
        if (load32(sav.data() + fo + magicOff) != kGen4Magic) {
            continue;
        }
        const uint32_t count = footerSize == 0x10 ? load32(sav.data() + fo) : load32(sav.data() + fo + kFooterCountOffDp);
        if (best < 0 || count >= bestCount) {
            best = slot;
            bestCount = count;
        }
    }
    return best;
}

void readTrainer(const uint8_t* general, std::size_t trainerOff, Trainer& trainer) {
    decodeGen4Text({general + trainerOff, 16}, trainer.name, sizeof(trainer.name));
    trainer.trainerId = load32(general + trainerOff + 0x10);
    trainer.gender = general[trainerOff + 0x18];
    trainer.playHours = load16(general + trainerOff + 0x22);
    trainer.playMinutes = general[trainerOff + 0x24];
    trainer.playSeconds = general[trainerOff + 0x25];
}

void readParty(const uint8_t* general, std::size_t partyOff, Party& party) {
    party.count = general[partyOff - 4];
    if (party.count > 6) {
        party.count = 6;
    }
    for (uint8_t i = 0; i < 6; ++i) {
        parsePk45({general + partyOff + i * kPk4PartySize, kPk4PartySize}, false, party.mons[i]);
    }
}

void readBoxes(const uint8_t* storage, bool padded, Boxes& boxes) {
    constexpr int kBoxCount = 18;
    constexpr std::size_t kPacked = 30 * kPkStoredSize;
    const std::size_t stride = padded ? 0x1000 : kPacked;
    if (padded) {
        boxes.current = storage[kBoxCount * stride];
    } else {
        boxes.current = storage[0];
    }
    const std::size_t data0 = padded ? 0 : 4;
    const std::size_t name0 = padded ? (kBoxCount * stride + 8) : (4 + kBoxCount * kPacked);
    for (int b = 0; b < kBoxCount; ++b) {
        decodeGen4Text({storage + name0 + static_cast<std::size_t>(b) * 40, 16}, boxes.boxes[b].name,
                       sizeof(boxes.boxes[b].name));
        for (int s = 0; s < 30; ++s) {
            const uint8_t* raw = storage + data0 + static_cast<std::size_t>(b) * stride + s * kPkStoredSize;
            parsePk45({raw, kPkStoredSize}, false, boxes.boxes[b].mons[s]);
        }
    }
}

}  // namespace

int activeGen4Slot(std::span<const uint8_t> sav, const Gen4Layout& layout) {
    return activePartition(sav, layout.generalSize, layout.footerSize);
}

bool readGen4Save(std::span<const uint8_t> sav, const Gen4Layout& layout, GameSnapshot& snap) {
    const int slot = activePartition(sav, layout.generalSize, layout.footerSize);
    if (slot < 0) {
        return false;
    }
    const std::size_t base = static_cast<std::size_t>(slot) * kGen4Partition;
    if (base + layout.storageStart + 0x1000 > sav.size()) {
        return false;
    }
    readTrainer(sav.data() + base, layout.trainerOff, snap.trainer);
    readParty(sav.data() + base, layout.partyOff, snap.party);
    readBoxes(sav.data() + base + layout.storageStart, layout.paddedBoxes, snap.boxes);
    const std::size_t badgeOff = base + layout.trainerOff + 0x1A;
    if (badgeOff < sav.size()) {
        fillGymsFromByte(snap, sav[badgeOff]);
    }
    if (layout.family == Gen4Family::HeartGoldSoulSilver) {
        static constexpr uint16_t kHg[] = {152, 155, 158};
        fillStarterSpecies(snap, kHg);
    } else {
        static constexpr uint16_t kDp[] = {387, 390, 393};
        fillStarterSpecies(snap, kDp);
    }
    snap.ok = true;
    return true;
}

bool fillGen4Live(const LiveMemory& mem, uint32_t partyAddr, GameSnapshot& snap) {
    uint8_t count = 0;
    if (!mem.read(partyAddr - 4, {&count, 1})) {
        return false;
    }
    if (count == 0 || count > 6) {
        return false;
    }
    snap.party.count = count;
    std::array<uint8_t, kPk4PartySize * 6> party{};
    if (!mem.read(partyAddr, party)) {
        return false;
    }
    int valid = 0;
    for (uint8_t i = 0; i < 6; ++i) {
        if (parsePk45({party.data() + i * kPk4PartySize, kPk4PartySize}, false, snap.party.mons[i])) {
            ++valid;
        }
    }
    snap.ok = valid > 0;
    if (snap.ok) {
        static constexpr uint16_t kStarters[] = {152, 155, 158, 387, 390, 393};
        fillStarterSpecies(snap, kStarters);
    }
    return snap.ok;
}

}
