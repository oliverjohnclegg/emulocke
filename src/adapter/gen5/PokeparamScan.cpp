#include "adapter/gen5/Pokeparam.hpp"

#include "adapter/gen3/Codec.hpp"
#include "adapter/gen45/NdsBattle.hpp"

#include <array>

namespace emulocke {
namespace {

uint32_t gBase;
uint8_t gDeadParty;
uint8_t gDeadFoe;

struct Hit {
    uint32_t addr{};
    uint16_t hp{};
    uint16_t liveMax{};
    uint16_t atk{};
    uint16_t def{};
    uint16_t spa{};
    uint16_t spd{};
    uint16_t spe{};
    uint8_t level{};
    int8_t stages[8]{};
    bool live{};
    bool ranks{};
};

bool liveCore(const uint8_t* p) {
    const uint16_t a = load16(p + 2);
    const uint16_t b = load16(p + 4);
    const uint16_t c = load16(p + 6);
    return c == 0 && a >= 1 && a <= 999 && b <= a;
}

bool fromAddr(const LiveMemory& mem, uint32_t addr, uint16_t sp, uint16_t maxHp, uint16_t seed,
    uint16_t atk, uint16_t def, Hit& hit) {
    if (!addr || !ndsRamRange(addr, 64)) {
        return false;
    }
    std::array<uint8_t, 64> buf{};
    if (!mem.read(addr, buf) || load16(buf.data()) != sp) {
        return false;
    }
    uint16_t hp = 0;
    if (!readBtlLiveHp(buf, sp, maxHp, seed, hp, atk, def)) {
        return false;
    }
    hit.addr = addr;
    hit.hp = hp;
    hit.live = liveCore(buf.data());
    hit.ranks = false;
    for (int i = 0; i < 8; ++i) {
        hit.stages[i] = 0;
    }
    if (hit.live) {
        hit.liveMax = load16(buf.data() + 2);
        const uint8_t lv = buf[kBtlPokeparamLevel];
        if (lv >= 1 && lv <= 100) {
            hit.level = lv;
        }
    } else {
        const uint16_t b = load16(buf.data() + 4);
        hit.liveMax = b >= 1 && b <= 999 ? b : maxHp;
        hit.ranks = readBtlRanks(buf, 8, hit.stages);
    }
    return true;
}

bool pullStats(const LiveMemory& mem, Hit& hit) {
    if (!hit.live || !hit.addr) {
        return false;
    }
    const uint32_t addr = hit.addr + static_cast<uint32_t>(kBtlPokeparamStat);
    if (!ndsRamRange(addr, 10)) {
        return false;
    }
    std::array<uint8_t, 10> buf{};
    if (!mem.read(addr, buf)) {
        return false;
    }
    const uint16_t atk = load16(buf.data());
    const uint16_t def = load16(buf.data() + 2);
    const uint16_t spa = load16(buf.data() + 4);
    const uint16_t spd = load16(buf.data() + 6);
    const uint16_t spe = load16(buf.data() + 8);
    if (atk < 1 || atk > 999 || def < 1 || def > 999 || spa < 1 || spa > 999 || spd < 1 ||
        spd > 999 || spe < 1 || spe > 999) {
        return false;
    }
    hit.atk = atk;
    hit.def = def;
    hit.spa = spa;
    hit.spd = spd;
    hit.spe = spe;
    return true;
}

int stagedStat(int stat, int8_t stage) {
    if (stage >= 0) {
        return stat * (2 + stage) / 2;
    }
    return stat * 2 / (2 - stage);
}

bool statsAlreadyBoosted(uint16_t atk, uint16_t def, uint16_t spa, uint16_t spd, uint16_t spe,
    const Hit& hit) {
    if (!hit.ranks || !hit.spe) {
        return false;
    }
    return hit.atk == static_cast<uint16_t>(stagedStat(atk, hit.stages[1])) &&
        hit.def == static_cast<uint16_t>(stagedStat(def, hit.stages[2])) &&
        hit.spa == static_cast<uint16_t>(stagedStat(spa, hit.stages[4])) &&
        hit.spd == static_cast<uint16_t>(stagedStat(spd, hit.stages[5])) &&
        hit.spe == static_cast<uint16_t>(stagedStat(spe, hit.stages[3]));
}

bool pullRanks(const LiveMemory& mem, Hit& hit) {
    if (!hit.live || !hit.addr) {
        return false;
    }
    const uint32_t addr = hit.addr + static_cast<uint32_t>(kBtlPokeparamRank);
    if (!ndsRamRange(addr, 7)) {
        return false;
    }
    std::array<uint8_t, 7> buf{};
    if (!mem.read(addr, buf)) {
        return false;
    }
    hit.ranks = readBtlRanks(buf, 0, hit.stages);
    return hit.ranks;
}

void copyStages(BattleBattler& b, const Hit& hit) {
    if (!hit.ranks) {
        return;
    }
    for (int i = 0; i < 8; ++i) {
        b.stages[i] = hit.stages[i];
    }
}

bool isMirror(uint32_t earlier, uint32_t later) {
    if (later <= earlier) {
        return false;
    }
    const uint32_t d = later - earlier;
    return d % kBtlPokeparamSize == 0 && d / kBtlPokeparamSize <= 12;
}

bool nearMax(const Hit& hit, uint16_t seedMax) {
    if (!hit.live || seedMax == 0 || hit.liveMax == seedMax) {
        return true;
    }
    return hit.liveMax >= seedMax && hit.liveMax - seedMax <= 12;
}

void takeHit(Hit& best, const Hit& hit) {
    if (!hit.addr) {
        return;
    }
    if (best.addr == 0) {
        best = hit;
        return;
    }
    if (best.live && hit.live && isMirror(best.addr, hit.addr)) {
        return;
    }
    if (hit.live && hit.hp > 0 && (!best.live || best.hp == 0)) {
        best = hit;
        return;
    }
    if (best.live && best.hp > 0 && hit.live && hit.hp == 0) {
        return;
    }
    if (hit.live && hit.hp == 0) {
        best = hit;
        return;
    }
    if (best.live && best.hp == 0) {
        return;
    }
    if (hit.live) {
        if (!best.live || hit.liveMax > best.liveMax) {
            best = hit;
        }
        return;
    }
    if (hit.hp == 0 || best.live) {
        return;
    }
    best = hit;
}

uint16_t livingFoeSpecies(const GameSnapshot& snap) {
    for (uint8_t i = 0; i < snap.battle.foeCount && i < 6; ++i) {
        if (!(gDeadFoe & (1u << i)) && snap.battle.foeSpecies[i]) {
            return snap.battle.foeSpecies[i];
        }
    }
    return 0;
}

uint16_t secondSpecies(const GameSnapshot& snap) {
    if (snap.party.count > 1 && snap.party.mons[1].species != 0) {
        return snap.party.mons[1].species;
    }
    if (const uint16_t living = livingFoeSpecies(snap)) {
        return living;
    }
    return snap.battle.foeSpecies[0];
}

bool slotAt(const LiveMemory& mem, uint32_t base, uint8_t slot, uint16_t sp, uint16_t maxHp,
    uint16_t seed, uint16_t atk, uint16_t def, Hit& hit) {
    return fromAddr(mem, base + slot * static_cast<uint32_t>(kBtlPokeparamSize), sp, maxHp, seed, atk,
        def, hit);
}

bool foeStats(const GameSnapshot& snap, uint16_t sp, uint16_t& maxHp, uint16_t& seed, uint16_t& atk,
    uint16_t& def) {
    for (uint8_t i = 0; i < snap.battle.foeCount && i < 6; ++i) {
        if (snap.battle.foeSpecies[i] == sp) {
            maxHp = snap.battle.foeMaxHp[i];
            seed = snap.battle.foeHp[i];
            atk = snap.battle.foeAtk[i];
            def = snap.battle.foeDef[i];
            return true;
        }
    }
    return false;
}

bool baseHasSpecies(const LiveMemory& mem, uint32_t base, const GameSnapshot& snap, uint16_t sp) {
    uint16_t maxHp = 0;
    uint16_t seed = 0;
    uint16_t atk = 0;
    uint16_t def = 0;
    if (!foeStats(snap, sp, maxHp, seed, atk, def)) {
        for (uint8_t i = 0; i < snap.party.count; ++i) {
            const Mon& mon = snap.party.mons[i];
            if (mon.species == sp) {
                maxHp = mon.maxHp;
                seed = mon.hp;
                atk = mon.attack;
                def = mon.defense;
                break;
            }
        }
    }
    Hit hit{};
    for (uint8_t slot = 0; slot < 7; ++slot) {
        if (slotAt(mem, base, slot, sp, maxHp, seed, atk, def, hit)) {
            return true;
        }
    }
    return false;
}

bool baseOk(const LiveMemory& mem, uint32_t base, const GameSnapshot& snap, bool needSecond) {
    if (snap.party.count == 0 || !snap.party.mons[0].species) {
        return false;
    }
    const Mon& lead = snap.party.mons[0];
    Hit hit{};
    if (!slotAt(mem, base, 0, lead.species, lead.maxHp, lead.hp, lead.attack, lead.defense, hit)) {
        return false;
    }
    const uint16_t next = secondSpecies(snap);
    if (!needSecond || !next) {
        return true;
    }
    uint16_t nMax = 0;
    uint16_t nSeed = 0;
    uint16_t nAtk = 0;
    uint16_t nDef = 0;
    if (snap.party.count > 1 && snap.party.mons[1].species == next) {
        const Mon& mon = snap.party.mons[1];
        nMax = mon.maxHp;
        nSeed = mon.hp;
        nAtk = mon.attack;
        nDef = mon.defense;
    } else if (!foeStats(snap, next, nMax, nSeed, nAtk, nDef)) {
        nMax = snap.battle.foeMaxHp[0];
        nSeed = snap.battle.foeHp[0];
        nAtk = snap.battle.foeAtk[0];
        nDef = snap.battle.foeDef[0];
    }
    for (uint8_t slot = 1; slot < 7; ++slot) {
        if (slotAt(mem, base, slot, next, nMax, nSeed, nAtk, nDef, hit)) {
            return true;
        }
    }
    return false;
}

uint8_t slotCount(const GameSnapshot& snap) {
    uint8_t n = static_cast<uint8_t>(snap.party.count + snap.battle.foeCount);
    if (n < 2) {
        n = 2;
    }
    return n > 12 ? uint8_t{12} : n;
}

void noteDead(uint8_t& bits, uint8_t i, uint16_t hp) {
    if (hp == 0 && i < 6) {
        bits = static_cast<uint8_t>(bits | (1u << i));
    }
}

void stampMon(Mon& mon, const Hit& hit) {
    if (hit.live && hit.level >= 1 && hit.level <= 100) {
        mon.level = hit.level;
    }
    if (hit.live && hit.liveMax != 0) {
        mon.maxHp = hit.liveMax;
    }
    if (hit.spe &&
        !statsAlreadyBoosted(mon.attack, mon.defense, mon.spAttack, mon.spDefense, mon.speed, hit)) {
        mon.attack = hit.atk;
        mon.defense = hit.def;
        mon.spAttack = hit.spa;
        mon.spDefense = hit.spd;
        mon.speed = hit.spe;
    }
}

Hit firstSlot(const LiveMemory& mem, uint32_t base, uint8_t slots, uint16_t sp, uint16_t maxHp,
    uint16_t seed, uint16_t atk, uint16_t def) {
    Hit best{};
    for (uint8_t slot = 0; slot < slots; ++slot) {
        Hit hit{};
        if (slotAt(mem, base, slot, sp, maxHp, seed, atk, def, hit)) {
            pullStats(mem, hit);
            pullRanks(mem, hit);
            takeHit(best, hit);
        }
    }
    return best;
}

void setPlayer(GameSnapshot& snap, const std::array<Hit, 6>& hits) {
    uint8_t use = 0xff;
    for (uint8_t i = 0; i < snap.party.count; ++i) {
        if (hits[i].addr && !(gDeadParty & (1u << i)) && hits[i].hp > 0) {
            use = i;
            break;
        }
    }
    if (use == 0xff) {
        for (uint8_t i = 0; i < snap.party.count; ++i) {
            if (hits[i].addr) {
                use = i;
                break;
            }
        }
    }
    if (use == 0xff) {
        return;
    }
    snap.battle.player.species = snap.party.mons[use].species;
    snap.battle.player.hp = (gDeadParty & (1u << use)) ? uint16_t{0} : hits[use].hp;
    snap.battle.player.maxHp =
        hits[use].liveMax != 0 ? hits[use].liveMax : snap.party.mons[use].maxHp;
    snap.battle.player.partyIndex = use;
    if (hits[use].level >= 1 && hits[use].level <= 100) {
        snap.battle.player.level = hits[use].level;
    }
    copyStages(snap.battle.player, hits[use]);
}

void setFoes(GameSnapshot& snap, const std::array<Hit, 6>& hits) {
    for (uint8_t i = 0; i < snap.battle.foeCount && i < 6; ++i) {
        if (hits[i].addr) {
            noteDead(gDeadFoe, i, hits[i].hp);
            if (!(gDeadFoe & (1u << i))) {
                snap.battle.foeHp[i] = hits[i].hp;
                if (hits[i].liveMax != 0) {
                    snap.battle.foeMaxHp[i] = hits[i].liveMax;
                }
                if (hits[i].level >= 1 && hits[i].level <= 100) {
                    snap.battle.foeLevel[i] = hits[i].level;
                }
            }
        }
        if (gDeadFoe & (1u << i)) {
            snap.battle.foeHp[i] = 0;
        }
        if (hits[i].spe &&
            !statsAlreadyBoosted(snap.battle.foeAtk[i], snap.battle.foeDef[i], snap.battle.foeSpa[i],
                snap.battle.foeSpd[i], snap.battle.foeSpe[i], hits[i])) {
            snap.battle.foeAtk[i] = hits[i].atk;
            snap.battle.foeDef[i] = hits[i].def;
            snap.battle.foeSpa[i] = hits[i].spa;
            snap.battle.foeSpd[i] = hits[i].spd;
            snap.battle.foeSpe[i] = hits[i].spe;
        }
    }
    uint8_t use = snap.battle.foe.partyIndex;
    if (use >= snap.battle.foeCount || snap.battle.foeHp[use] == 0) {
        use = 0xff;
        for (uint8_t i = 0; i < snap.battle.foeCount && i < 6; ++i) {
            if (snap.battle.foeHp[i] > 0) {
                use = i;
                break;
            }
        }
    }
    if (use < 6) {
        snap.battle.foe.partyIndex = use;
        copyStages(snap.battle.foe, hits[use]);
    }
}

void overlayBase(const LiveMemory& mem, GameSnapshot& snap) {
    const uint8_t slots = slotCount(snap);
    std::array<Hit, 6> hits{};
    for (uint8_t i = 0; i < snap.party.count; ++i) {
        Mon& mon = snap.party.mons[i];
        if (!mon.species) {
            continue;
        }
        hits[i] = firstSlot(mem, gBase, slots, mon.species, mon.maxHp, mon.hp, mon.attack,
            mon.defense);
        if (hits[i].addr) {
            noteDead(gDeadParty, i, hits[i].hp);
        }
        if (gDeadParty & (1u << i)) {
            mon.hp = 0;
        }
        stampMon(mon, hits[i]);
    }
    setPlayer(snap, hits);
    std::array<Hit, 6> foeHits{};
    for (uint8_t i = 0; i < snap.battle.foeCount && i < 6; ++i) {
        foeHits[i] = firstSlot(mem, gBase, slots, snap.battle.foeSpecies[i], snap.battle.foeMaxHp[i],
            snap.battle.foeHp[i], snap.battle.foeAtk[i], snap.battle.foeDef[i]);
    }
    setFoes(snap, foeHits);
}

void overlayScan(const LiveMemory& mem, GameSnapshot& snap) {
    std::array<Hit, 6> partyHit{};
    std::array<Hit, 6> foeHit{};
    static constexpr uint32_t kChunk = 0x8000;
    std::array<uint8_t, kChunk> chunk{};
    const uint32_t end = kNdsRam + kNdsRamBytes;
    for (uint32_t addr = kNdsRam; addr < end; addr += kChunk) {
        const uint32_t n = addr + kChunk > end ? end - addr : kChunk;
        if (n < 16 || !mem.read(addr, {chunk.data(), n})) {
            continue;
        }
        for (uint32_t i = 0; i + 8 <= n; i += 2) {
            const uint16_t sp = load16(chunk.data() + i);
            const uint32_t here = addr + i;
            Hit hit{};
            for (uint8_t p = 0; p < snap.party.count; ++p) {
                const Mon& mon = snap.party.mons[p];
                if (mon.species != sp) {
                    continue;
                }
                if (fromAddr(mem, here, sp, mon.maxHp, mon.hp, mon.attack, mon.defense, hit) &&
                    nearMax(hit, mon.maxHp)) {
                    pullStats(mem, hit);
                    pullRanks(mem, hit);
                    takeHit(partyHit[p], hit);
                }
            }
            for (uint8_t f = 0; f < snap.battle.foeCount && f < 6; ++f) {
                if (snap.battle.foeSpecies[f] != sp) {
                    continue;
                }
                if (fromAddr(mem, here, sp, snap.battle.foeMaxHp[f], snap.battle.foeHp[f],
                        snap.battle.foeAtk[f], snap.battle.foeDef[f], hit) &&
                    nearMax(hit, snap.battle.foeMaxHp[f])) {
                    pullStats(mem, hit);
                    pullRanks(mem, hit);
                    takeHit(foeHit[f], hit);
                }
            }
        }
    }
    for (uint8_t i = 0; i < snap.party.count; ++i) {
        if (partyHit[i].addr) {
            noteDead(gDeadParty, i, partyHit[i].hp);
        }
        if (gDeadParty & (1u << i)) {
            snap.party.mons[i].hp = 0;
        }
        stampMon(snap.party.mons[i], partyHit[i]);
    }
    setPlayer(snap, partyHit);
    setFoes(snap, foeHit);
}

bool missingLivingFoe(const LiveMemory& mem, uint32_t base, const GameSnapshot& snap) {
    const uint16_t living = livingFoeSpecies(snap);
    return living != 0 && (base == 0 || !baseHasSpecies(mem, base, snap, living));
}

uint32_t findBase(const LiveMemory& mem, const GameSnapshot& snap) {
    static constexpr uint32_t kChunk = 0x8000;
    std::array<uint8_t, kChunk> chunk{};
    const uint32_t end = kNdsRam + kNdsRamBytes;
    const uint16_t lead = snap.party.mons[0].species;
    uint32_t livePick = 0;
    uint32_t formPick = 0;
    for (uint32_t addr = kNdsRam; addr < end; addr += kChunk) {
        const uint32_t n = addr + kChunk > end ? end - addr : kChunk;
        if (n < 16 || !mem.read(addr, {chunk.data(), n})) {
            continue;
        }
        for (uint32_t i = 0; i + 8 <= n; i += 2) {
            if (load16(chunk.data() + i) != lead) {
                continue;
            }
            const uint32_t here = addr + i;
            if (!baseOk(mem, here, snap, true)) {
                continue;
            }
            if (gDeadFoe && missingLivingFoe(mem, here, snap)) {
                continue;
            }
            Hit hit{};
            const Mon& leadMon = snap.party.mons[0];
            const bool live = fromAddr(mem, here, lead, leadMon.maxHp, leadMon.hp, leadMon.attack,
                                  leadMon.defense, hit) &&
                hit.live;
            if (live) {
                if (livePick != 0 && isMirror(livePick, here)) {
                    continue;
                }
                livePick = here;
            } else {
                formPick = here;
            }
        }
    }
    return livePick != 0 ? livePick : formPick;
}

void applyOverlay(const LiveMemory& mem, GameSnapshot& snap) {
    if (gBase != 0 && !baseOk(mem, gBase, snap, false)) {
        gBase = 0;
    }
    if (gBase != 0 && gDeadFoe && missingLivingFoe(mem, gBase, snap)) {
        gBase = 0;
    }
    if (gBase == 0) {
        gBase = findBase(mem, snap);
    }
    if (gBase != 0) {
        overlayBase(mem, snap);
    } else {
        overlayScan(mem, snap);
    }
}

}  // namespace

void resetGen5Pokeparam() {
    gBase = 0;
    gDeadParty = 0;
    gDeadFoe = 0;
}

void overlayGen5Pokeparam(const LiveMemory& mem, GameSnapshot& snap) {
    if (!snap.battle.inBattle || snap.party.count == 0 || !snap.party.mons[0].species ||
        !snap.battle.foe.species) {
        return;
    }
    applyOverlay(mem, snap);
    if (gDeadFoe && missingLivingFoe(mem, gBase, snap)) {
        gBase = 0;
        applyOverlay(mem, snap);
    }
    const uint8_t fIdx = snap.battle.foe.partyIndex;
    if (fIdx < 6) {
        snap.battle.foe.hp = snap.battle.foeHp[fIdx];
        snap.battle.foe.maxHp = snap.battle.foeMaxHp[fIdx];
        snap.battle.foe.species = snap.battle.foeSpecies[fIdx];
    }
}

}
