#include "adapter/gen45/NdsBattle.hpp"

#include "adapter/gen3/Codec.hpp"

namespace emulocke {

bool ndsRamRange(uint32_t addr, std::size_t n) {
    if (addr < kNdsRam) {
        return false;
    }
    const uint32_t off = addr - kNdsRam;
    return off < kNdsRamBytes && n <= kNdsRamBytes - off;
}

bool readNdsBattleMon(std::span<const uint8_t> raw, BattleBattler& out) {
    if (raw.size() < kNdsBattleMonSize) {
        return false;
    }
    const uint16_t species = load16(raw.data());
    if (species == 0 || species > 649) {
        return false;
    }
    const uint8_t level = raw[kNdsBattleMonLevel];
    if (level < 1 || level > 100) {
        return false;
    }
    int32_t hp = static_cast<int32_t>(load32(raw.data() + kNdsBattleMonHp));
    uint32_t maxHp = load32(raw.data() + kNdsBattleMonMaxHp);
    if (maxHp == 0 || maxHp > 999 || hp < 0 || static_cast<uint32_t>(hp) > maxHp) {
        hp = load16(raw.data() + kNdsBattleMonHp);
        maxHp = load16(raw.data() + kNdsBattleMonHp + 2);
        if (maxHp == 0 || maxHp > 999 || hp < 0 || static_cast<uint32_t>(hp) > maxHp) {
            return false;
        }
    }
    for (int i = 0; i < 8; ++i) {
        if (raw[kNdsBattleMonStages + static_cast<std::size_t>(i)] > 12) {
            return false;
        }
    }
    out = {};
    out.species = species;
    out.hp = static_cast<uint16_t>(hp);
    out.maxHp = static_cast<uint16_t>(maxHp);
    out.status = load32(raw.data() + kNdsBattleMonStatus);
    for (int i = 0; i < 8; ++i) {
        out.stages[i] = static_cast<int8_t>(raw[kNdsBattleMonStages + static_cast<std::size_t>(i)] - 6);
    }
    return true;
}

void seedPlayerBattler(GameSnapshot& snap) {
    for (uint8_t i = 0; i < snap.party.count; ++i) {
        const Mon& mon = snap.party.mons[i];
        if (!mon.species) {
            continue;
        }
        snap.battle.player.species = mon.species;
        snap.battle.player.hp = mon.hp;
        snap.battle.player.maxHp = mon.maxHp;
        snap.battle.player.status = mon.status;
        snap.battle.player.partyIndex = i;
        if (mon.hp > 0) {
            break;
        }
    }
}

void bindBattleSlots(GameSnapshot& snap) {
    for (uint8_t i = 0; i < snap.party.count; ++i) {
        if (snap.party.mons[i].species == snap.battle.player.species) {
            snap.battle.player.partyIndex = i;
            break;
        }
    }
    for (uint8_t i = 0; i < snap.battle.foeCount; ++i) {
        if (snap.battle.foeSpecies[i] == snap.battle.foe.species) {
            snap.battle.foe.partyIndex = i;
            break;
        }
    }
}

}
