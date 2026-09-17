#include "adapter/gen5/Pokeparam.hpp"

#include "adapter/gen3/Codec.hpp"
#include "adapter/gen45/Pk.hpp"

#include <array>
#include <cstring>
#include <span>

namespace emulocke {
namespace {

bool hasSpecies(std::span<const uint8_t> raw, uint16_t species) {
    for (std::size_t i = 0; i + 2 <= raw.size(); i += 2) {
        if (load16(raw.data() + i) == species) {
            return true;
        }
    }
    return false;
}

}  // namespace

void overlayGen5Tags(const LiveMemory& mem, uint32_t addr, std::span<const uint8_t> chunk,
    GameSnapshot& snap, BattleBattler& bestP, bool& gotP, BattleBattler& bestF, bool& gotF) {
    const uint16_t playerSp = snap.battle.player.species;
    const uint16_t playerMax = snap.battle.player.maxHp;
    const uint16_t playerHp = snap.battle.player.hp;
    const uint16_t foeSp = snap.battle.foe.species;
    const uint16_t foeMax = snap.battle.foe.maxHp;
    const uint16_t foeHp = snap.battle.foe.hp;
    uint16_t playerAtk = 0;
    uint16_t playerDef = 0;
    uint16_t foeAtk = 0;
    uint16_t foeDef = 0;
    const uint8_t pIdx = snap.battle.player.partyIndex;
    const uint8_t fIdx = snap.battle.foe.partyIndex;
    if (pIdx < snap.party.count) {
        playerAtk = snap.party.mons[pIdx].attack;
        playerDef = snap.party.mons[pIdx].defense;
    }
    if (fIdx < 6) {
        foeAtk = snap.battle.foeAtk[fIdx];
        foeDef = snap.battle.foeDef[fIdx];
    }
    static constexpr char kParty[] = "pokeparty.c";
    static constexpr char kParam[] = "pokeparam.c";
    static constexpr uint32_t kPad[] = {30, 32};
    const uint32_t n = static_cast<uint32_t>(chunk.size());
    for (uint32_t i = 0; i + 11 < n; ++i) {
        const bool party = std::memcmp(chunk.data() + i, kParty, 11) == 0;
        if (!party && std::memcmp(chunk.data() + i, kParam, 11) != 0) {
            continue;
        }
        for (uint32_t pad : kPad) {
            const uint32_t data = addr + i + pad;
            if (party) {
                for (uint8_t s = 0; s < 6; ++s) {
                    std::array<uint8_t, kPk5PartySize> raw{};
                    Mon mon{};
                    if (!mem.read(data + s * static_cast<uint32_t>(kPk5PartySize), raw) ||
                        !parsePk45(raw, true, mon)) {
                        break;
                    }
                    if (mon.species == playerSp && mon.maxHp == playerMax) {
                        considerBtl(bestP, gotP, playerHp, playerSp, mon.hp, mon.maxHp);
                    }
                    if (mon.species == foeSp && mon.maxHp == foeMax) {
                        considerBtl(bestF, gotF, foeHp, foeSp, mon.hp, mon.maxHp);
                    }
                }
                continue;
            }
            for (uint8_t s = 0; s < 12; ++s) {
                std::array<uint8_t, kBtlPokeparamSize> rec{};
                if (!mem.read(data + s * static_cast<uint32_t>(kBtlPokeparamSize), rec)) {
                    break;
                }
                uint16_t hp = 0;
                if (hasSpecies(rec, playerSp) &&
                    readBtlHp(rec, playerMax, playerHp, hp, playerAtk, playerDef)) {
                    considerBtl(bestP, gotP, playerHp, playerSp, hp, playerMax);
                }
                if (hasSpecies(rec, foeSp) && readBtlHp(rec, foeMax, foeHp, hp, foeAtk, foeDef)) {
                    considerBtl(bestF, gotF, foeHp, foeSp, hp, foeMax);
                }
            }
        }
    }
}

}
