#include "adapter/gen5/Save.hpp"

#include "adapter/ProgressFill.hpp"
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
    uint8_t stored = sav[kGen5Party + 4];
    uint8_t parsed = 0;
    for (uint8_t i = 0; i < 6; ++i) {
        if (parsePk45({sav + kGen5Party + 8 + i * kPk5PartySize, kPk5PartySize}, true, party.mons[i])) {
            parsed = static_cast<uint8_t>(i + 1);
        }
    }
    party.count = (stored > 0 && stored <= 6) ? stored : parsed;
}

void readBoxes(const uint8_t* sav, Boxes& boxes) {
    boxes.current = sav[0];
    for (std::size_t b = 0; b < kGen5BoxCount; ++b) {
        decodeUtf16Text({sav + 4 + b * kGen5BoxNameStride, 20}, boxes.boxes[b].name, sizeof(boxes.boxes[b].name));
        const std::size_t boxOff = kGen5Box + b * kGen5BoxStride;
        for (int s = 0; s < 30; ++s) {
            parsePk45({sav + boxOff + s * kPkStoredSize, kPkStoredSize}, true, boxes.boxes[b].mons[s]);
        }
    }
}

bool pullGen5Party(const LiveMemory& mem, uint32_t partyAddr, GameSnapshot& snap) {
    uint8_t count = 0;
    if (!mem.read(partyAddr + 4, {&count, 1}) || count == 0 || count > 6) {
        return false;
    }
    std::array<uint8_t, kPk5PartySize * 6> party{};
    if (!mem.read(partyAddr + 8, party)) {
        return false;
    }
    Party tmp{};
    int valid = 0;
    for (uint8_t i = 0; i < count; ++i) {
        if (parsePk45({party.data() + i * kPk5PartySize, kPk5PartySize}, true, tmp.mons[i])) {
            ++valid;
        }
    }
    if (valid == 0) {
        return false;
    }
    tmp.count = count;
    snap.party = tmp;
    return true;
}

uint32_t scanGen5Party(const LiveMemory& mem, GameSnapshot& snap) {
    static constexpr uint32_t kRam = 0x02000000;
    static constexpr uint32_t kRamEnd = 0x02400000;
    static constexpr uint32_t kChunk = 0x1000;
    static constexpr uint32_t kPartyBytes = 8 + kPk5PartySize * 6;
    std::array<uint8_t, kChunk> chunk{};
    for (uint32_t addr = kRam; addr < kRamEnd; addr += kChunk - kPartyBytes) {
        const uint32_t n = addr + kChunk > kRamEnd ? kRamEnd - addr : kChunk;
        if (n < kPartyBytes || !mem.read(addr, {chunk.data(), n})) {
            continue;
        }
        for (uint32_t i = 0; i + 4 < n; i += 4) {
            const uint8_t count = chunk[i + 4];
            if (count == 0 || count > 6) {
                continue;
            }
            if (pullGen5Party(mem, addr + i, snap)) {
                return addr + i;
            }
        }
    }
    return 0;
}

}  // namespace

bool readGen5Save(std::span<const uint8_t> sav, GameSnapshot& snap, bool bw2) {
    if (sav.size() < kGen5MinSave) {
        return false;
    }
    readTrainer(sav.data() + kGen5Trainer, snap.trainer);
    readParty(sav.data(), snap.party);
    readBoxes(sav.data(), snap.boxes);
    const std::size_t badgeOff = bw2 ? kBw2BadgeOff : kBwBadgeOff;
    if (snap.trainer.name[0] && sav.size() > badgeOff) {
        fillGymsFromByte(snap, sav[badgeOff]);
    }
    static constexpr uint16_t kStarters[] = {495, 498, 501};
    fillStarterSpecies(snap, kStarters);
    snap.ok = snap.trainer.name[0] != 0 || snap.party.count > 0;
    return snap.ok;
}

bool fillGen5Live(const LiveMemory& mem, uint32_t partyAddr, GameSnapshot& snap) {
    static uint32_t cached = 0;
    static constexpr uint16_t kStarters[] = {495, 498, 501};
    auto take = [&](uint32_t addr) {
        if (!pullGen5Party(mem, addr, snap)) {
            return false;
        }
        cached = addr;
        snap.ok = true;
        fillStarterSpecies(snap, kStarters);
        return true;
    };
    if (take(partyAddr)) {
        return true;
    }
    if (cached != 0 && cached != partyAddr && take(cached)) {
        return true;
    }
    static uint8_t wait = 0;
    if (wait > 0) {
        --wait;
        return false;
    }
    const uint32_t found = scanGen5Party(mem, snap);
    if (found == 0) {
        wait = 30;
        return false;
    }
    cached = found;
    snap.ok = true;
    fillStarterSpecies(snap, kStarters);
    return true;
}

}
