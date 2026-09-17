#include "adapter/gen4/Save.hpp"

#include "adapter/ProgressFill.hpp"
#include "adapter/gen3/Codec.hpp"
#include "adapter/gen4/Battle.hpp"
#include "adapter/gen45/Pk.hpp"

#include <array>
#include <cstdio>
#include <cstring>
#include <vector>

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
    const std::size_t stride = padded ? kGen4PaddedBox : kGen4PackedBox;
    if (padded) {
        boxes.current = storage[kGen4BoxCount * stride];
    } else {
        boxes.current = storage[0];
    }
    const std::size_t data0 = padded ? 0 : 4;
    const std::size_t name0 = padded ? (kGen4BoxCount * stride + 8) : (4 + kGen4BoxCount * kGen4PackedBox);
    for (std::size_t b = 0; b < kGen4BoxCount; ++b) {
        decodeGen4Text({storage + name0 + b * kGen4BoxNameBytes, 16}, boxes.boxes[b].name,
                       sizeof(boxes.boxes[b].name));
        for (std::size_t s = 0; s < kGen4BoxSlots; ++s) {
            const uint8_t* raw = storage + data0 + b * stride + s * kPkStoredSize;
            parsePk45({raw, kPkStoredSize}, false, boxes.boxes[b].mons[s]);
        }
    }
}

void fillGen4Progress(const uint8_t* general, const Gen4Layout& layout, GameSnapshot& snap) {
    if (layout.eventFlagOff != 0) {
        fillFlagBank(snap, general + layout.eventFlagOff, kGen4FlagBytes);
    }
    if (layout.mapOff != 0) {
        const uint16_t map = load16(general + layout.mapOff);
        snap.overworld.mapNum = static_cast<uint8_t>(map & 0xFF);
        snap.overworld.mapGroup = static_cast<uint8_t>(map >> 8);
        std::snprintf(snap.overworld.mapName, sizeof(snap.overworld.mapName), "MAP %u", map);
    }
    fillGymsFromByte(snap, general[layout.trainerOff + 0x1A]);
    if (layout.family == Gen4Family::HeartGoldSoulSilver) {
        static constexpr uint16_t kHg[] = {152, 155, 158};
        fillStarterSpecies(snap, kHg);
    } else {
        static constexpr uint16_t kDp[] = {387, 390, 393};
        fillStarterSpecies(snap, kDp);
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
    if (base > sav.size() || sav.size() - base < gen4PartitionBytes(layout)) {
        return false;
    }
    readTrainer(sav.data() + base, layout.trainerOff, snap.trainer);
    readParty(sav.data() + base, layout.partyOff, snap.party);
    readBoxes(sav.data() + base + layout.storageStart, layout.paddedBoxes, snap.boxes);
    fillGen4Progress(sav.data() + base, layout, snap);
    snap.ok = true;
    return true;
}

bool fillGen4Live(const LiveMemory& mem, uint32_t partyAddr, const Gen4Layout& layout, GameSnapshot& snap) {
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
    if (!snap.ok) {
        return false;
    }
    const uint32_t general = partyAddr - static_cast<uint32_t>(layout.partyOff);
    std::array<uint8_t, kGen4TrainerBytes> trainer{};
    if (mem.read(general + static_cast<uint32_t>(layout.trainerOff), trainer)) {
        readTrainer(trainer.data(), 0, snap.trainer);
    }
    std::array<uint8_t, kGen4FlagBytes> flags{};
    if (layout.eventFlagOff != 0 &&
        mem.read(general + static_cast<uint32_t>(layout.eventFlagOff), flags)) {
        fillFlagBank(snap, flags.data(), flags.size());
    }
    uint8_t mapRaw[2]{};
    if (layout.mapOff != 0 && mem.read(general + static_cast<uint32_t>(layout.mapOff), mapRaw)) {
        const uint16_t map = static_cast<uint16_t>(mapRaw[0] | (mapRaw[1] << 8));
        snap.overworld.mapNum = static_cast<uint8_t>(map & 0xFF);
        snap.overworld.mapGroup = static_cast<uint8_t>(map >> 8);
        std::snprintf(snap.overworld.mapName, sizeof(snap.overworld.mapName), "MAP %u", map);
    }
    uint8_t badge = 0;
    if (mem.read(general + static_cast<uint32_t>(layout.trainerOff + 0x1A), {&badge, 1})) {
        fillGymsFromByte(snap, badge);
    }
    const std::size_t boxBytes = gen4StorageBytes(layout.paddedBoxes);
    std::vector<uint8_t> storage(boxBytes);
    if (mem.read(general + static_cast<uint32_t>(layout.storageStart), storage)) {
        readBoxes(storage.data(), layout.paddedBoxes, snap.boxes);
    }
    if (layout.family == Gen4Family::HeartGoldSoulSilver) {
        static constexpr uint16_t kHg[] = {152, 155, 158};
        fillStarterSpecies(snap, kHg);
    } else {
        static constexpr uint16_t kDp[] = {387, 390, 393};
        fillStarterSpecies(snap, kDp);
    }
    fillGen4Battle(mem, partyAddr, layout, snap);
    return true;
}

}
