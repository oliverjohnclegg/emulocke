#include "adapter/frlg/FrlgBattle.hpp"

#include "adapter/frlg/FrlgLayout.hpp"
#include "adapter/gen3/BoxMon.hpp"

#include <array>

namespace emulocke {
namespace {

void readBattler(const LiveMemory& mem, uint32_t addr, BattleBattler& out) {
    uint8_t raw[kFrlgBattleMonSize]{};
    if (!mem.read(addr, raw)) {
        return;
    }
    out.species = static_cast<uint16_t>(raw[0] | (raw[1] << 8));
    out.hp = static_cast<uint16_t>(raw[0x28] | (raw[0x29] << 8));
    out.maxHp = static_cast<uint16_t>(raw[0x2C] | (raw[0x2D] << 8));
    out.status = static_cast<uint32_t>(raw[0x4C] | (raw[0x4D] << 8) | (raw[0x4E] << 16) | (raw[0x4F] << 24));
    for (int i = 0; i < 8; ++i) {
        out.stages[i] = static_cast<int8_t>(raw[0x18 + i] - 6);
    }
}

}  // namespace

void fillFrlgBattle(const LiveMemory& mem, GameSnapshot& snap) {
    const uint32_t flags = mem.read32(kFrlgBattleTypeFlags);
    if ((flags & kFrlgBattleTypeTrainer) == 0) {
        return;
    }
    snap.battle.inBattle = true;
    const uint16_t weather = static_cast<uint16_t>(mem.read32(kFrlgBattleWeather) & 0xFFFFu);
    if (weather & 0x7) {
        snap.battle.weather = 1;
    } else if (weather & 0x18) {
        snap.battle.weather = 2;
    } else if (weather & 0x60) {
        snap.battle.weather = 3;
    } else if (weather & 0x80) {
        snap.battle.weather = 4;
    }
    readBattler(mem, kFrlgBattleMons, snap.battle.player);
    readBattler(mem, kFrlgBattleMons + kFrlgBattleMonSize, snap.battle.foe);
    for (uint8_t i = 0; i < snap.party.count; ++i) {
        if (snap.party.mons[i].species == snap.battle.player.species) {
            snap.battle.player.partyIndex = i;
            break;
        }
    }
    uint8_t count = 0;
    mem.read(kFrlgEnemyPartyCount, {&count, 1});
    if (count > 6) {
        count = 6;
    }
    snap.battle.foeCount = count;
    std::array<uint8_t, kPartyMonSize * 6> party{};
    if (!mem.read(kFrlgEnemyParty, party)) {
        return;
    }
    bool foundFoe = false;
    for (uint8_t i = 0; i < 6; ++i) {
        const uint8_t* mon = party.data() + i * kPartyMonSize;
        snap.battle.foeHp[i] = static_cast<uint16_t>(mon[kFrlgPartyHpOff] | (mon[kFrlgPartyHpOff + 1] << 8));
        snap.battle.foeMaxHp[i] =
            static_cast<uint16_t>(mon[kFrlgPartyMaxHpOff] | (mon[kFrlgPartyMaxHpOff + 1] << 8));
        snap.battle.foeLevel[i] = mon[kFrlgPartyLevelOff];
        DecryptedMon dec;
        if (decryptPartyMon({mon, kPartyMonSize}, dec)) {
            snap.battle.foeSpecies[i] = dec.species;
            snap.battle.foeLevel[i] = dec.level;
        }
        if (!foundFoe && snap.battle.foeSpecies[i] == snap.battle.foe.species) {
            snap.battle.foe.partyIndex = i;
            foundFoe = true;
        }
    }
}

}
