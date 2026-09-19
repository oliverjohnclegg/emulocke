#include "adapter/gen4/Battle.hpp"

#include "adapter/gen45/NdsBattle.hpp"
#include "adapter/gen45/Pk.hpp"

#include <array>

namespace emulocke {
namespace {

uint32_t savePtrAddr(const Gen4Layout& layout, uint32_t partyAddr) {
    if (layout.family == Gen4Family::Platinum) {
        return kPtSavePtr;
    }
    if (layout.family == Gen4Family::HeartGoldSoulSilver) {
        return partyAddr == kSsPartyLive ? kSsSavePtr : kHgSavePtr;
    }
    return kDpSavePtr;
}

void foeLayout(const Gen4Layout& layout, uint32_t& enemyPtrOff, uint32_t& enemyAdd, uint32_t& wildOff,
    uint32_t& foeHpOff) {
    if (layout.family == Gen4Family::Platinum) {
        enemyPtrOff = kPtEnemyPtrOff;
        enemyAdd = kPtEnemyPartyAdd;
        wildOff = kPtWildPartyOff;
        foeHpOff = kPtFoeHpOff;
        return;
    }
    if (layout.family == Gen4Family::HeartGoldSoulSilver) {
        enemyPtrOff = kHgEnemyPtrOff;
        enemyAdd = kHgEnemyPartyAdd;
        wildOff = kHgWildPartyOff;
        foeHpOff = kHgFoeHpOff;
        return;
    }
    enemyPtrOff = kDpEnemyPtrOff;
    enemyAdd = kDpEnemyPartyAdd;
    wildOff = kDpWildPartyOff;
    foeHpOff = kDpFoeHpOff;
}

void overlayFromFoeHp(const LiveMemory& mem, uint32_t foeHpAddr, GameSnapshot& snap) {
    if (!ndsRamRange(foeHpAddr, 2) || foeHpAddr < kNdsBattleMonHp + kNdsBattleMonSize) {
        return;
    }
    const uint32_t foeMon = foeHpAddr - static_cast<uint32_t>(kNdsBattleMonHp);
    const uint32_t playerMon = foeMon - static_cast<uint32_t>(kNdsBattleMonSize);
    std::array<uint8_t, kNdsBattleMonSize> raw{};
    BattleBattler b;
    if (ndsRamRange(playerMon, kNdsBattleMonSize) && mem.read(playerMon, raw) && readNdsBattleMon(raw, b) &&
        b.species == snap.battle.player.species) {
        const uint8_t idx = snap.battle.player.partyIndex;
        snap.battle.player = b;
        snap.battle.player.partyIndex = idx;
    }
    if (mem.read(foeMon, raw) && readNdsBattleMon(raw, b) && b.species == snap.battle.foe.species) {
        const uint8_t idx = snap.battle.foe.partyIndex;
        snap.battle.foe = b;
        snap.battle.foe.partyIndex = idx;
        if (idx < 6) {
            snap.battle.foeHp[idx] = b.hp;
            snap.battle.foeMaxHp[idx] = b.maxHp;
        }
    }
}

}  // namespace

void fillGen4Battle(const LiveMemory& mem, uint32_t partyAddr, const Gen4Layout& layout, GameSnapshot& snap) {
    uint32_t enemyPtrOff = 0;
    uint32_t enemyAdd = 0;
    uint32_t wildOff = 0;
    uint32_t foeHpOff = 0;
    foeLayout(layout, enemyPtrOff, enemyAdd, wildOff, foeHpOff);
    const uint32_t ptr = mem.read32(savePtrAddr(layout, partyAddr));
    if (ndsRamRange(ptr, 4)) {
        const uint32_t heap = mem.read32(ptr + enemyPtrOff);
        if (ndsRamRange(heap, enemyAdd + kPk4PartySize)) {
            fillFoePartyFromPk(mem, heap + enemyAdd, kPk4PartySize, false, snap);
        }
        if (!snap.battle.inBattle) {
            fillFoePartyFromPk(mem, ptr + wildOff, kPk4PartySize, false, snap);
        }
    }
    if (!snap.battle.inBattle) {
        return;
    }
    seedPlayerBattler(snap);
    if (ndsRamRange(ptr, foeHpOff + 4)) {
        overlayFromFoeHp(mem, ptr + foeHpOff, snap);
    }
    bindBattleSlots(snap);
    const uint8_t foeIdx = snap.battle.foe.partyIndex;
    if (snap.battle.foe.maxHp && foeIdx < 6) {
        snap.battle.foeHp[foeIdx] = snap.battle.foe.hp;
        snap.battle.foeMaxHp[foeIdx] = snap.battle.foe.maxHp;
    }
}

}
