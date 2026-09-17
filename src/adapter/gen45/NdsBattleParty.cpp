#include "adapter/gen45/NdsBattle.hpp"

#include "adapter/gen45/Pk.hpp"

#include <array>

namespace emulocke {

bool fillFoePartyFromPk(const LiveMemory& mem, uint32_t addr, std::size_t pkSize, bool utf16,
    GameSnapshot& snap) {
    if (pkSize != kPk4PartySize && pkSize != kPk5PartySize) {
        return false;
    }
    if (!ndsRamRange(addr, pkSize) || addr == 0) {
        return false;
    }
    uint8_t count = 0;
    if (!mem.read(addr - 4, {&count, 1}) || count == 0 || count > 6) {
        count = 6;
    }
    uint8_t got = 0;
    for (uint8_t i = 0; i < count; ++i) {
        std::array<uint8_t, kPk4PartySize> raw{};
        if (!mem.read(addr + i * static_cast<uint32_t>(pkSize), {raw.data(), pkSize})) {
            break;
        }
        Mon mon{};
        if (!parsePk45({raw.data(), pkSize}, utf16, mon)) {
            break;
        }
        if (got == 0 && snap.party.count > 0 && mon.personality == snap.party.mons[0].personality &&
            mon.species == snap.party.mons[0].species) {
            return false;
        }
        snap.battle.foeSpecies[i] = mon.species;
        snap.battle.foeLevel[i] = mon.level;
        snap.battle.foeHp[i] = mon.hp;
        snap.battle.foeMaxHp[i] = mon.maxHp;
        snap.battle.foeAtk[i] = mon.attack;
        snap.battle.foeDef[i] = mon.defense;
        snap.battle.foeSpa[i] = mon.spAttack;
        snap.battle.foeSpd[i] = mon.spDefense;
        snap.battle.foeSpe[i] = mon.speed;
        if (got == 0 || (snap.battle.foe.hp == 0 && mon.hp > 0)) {
            snap.battle.foe.species = mon.species;
            snap.battle.foe.hp = mon.hp;
            snap.battle.foe.maxHp = mon.maxHp;
            snap.battle.foe.status = mon.status;
            snap.battle.foe.partyIndex = i;
        }
        got = static_cast<uint8_t>(i + 1);
    }
    if (got == 0) {
        return false;
    }
    snap.battle.foeCount = got;
    snap.battle.inBattle = true;
    return true;
}

}
