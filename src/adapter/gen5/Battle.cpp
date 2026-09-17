#include "adapter/gen5/Battle.hpp"

#include "adapter/gen45/NdsBattle.hpp"
#include "adapter/gen45/Pk.hpp"
#include "adapter/gen5/Pokeparam.hpp"

namespace emulocke {

void fillGen5Battle(const LiveMemory& mem, uint32_t partyAddr, GameSnapshot& snap) {
    static constexpr uint32_t kFixed[] = {kBwEnemyPartyLive, kWhiteEnemyPartyLive, kBw2EnemyPartyLive,
        kWhite2EnemyPartyLive, kBwWildPartyLive, kWhiteWildPartyLive, kBw2WildPartyLive, kWhite2WildPartyLive};
    static constexpr uint32_t kRel[] = {0x36340, 0x25424, 0x3A448, 0x29570};
    auto take = [&](uint32_t addr) {
        return addr != partyAddr && fillFoePartyFromPk(mem, addr, kPk5PartySize, true, snap);
    };
    for (uint32_t addr : kFixed) {
        if (take(addr)) {
            break;
        }
    }
    if (!snap.battle.inBattle) {
        for (uint32_t rel : kRel) {
            if (take(partyAddr + rel)) {
                break;
            }
        }
    }
    if (!snap.battle.inBattle) {
        resetGen5Pokeparam();
        return;
    }
    seedPlayerBattler(snap);
    overlayGen5Pokeparam(mem, snap);
    bindBattleSlots(snap);
}

}
