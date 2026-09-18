#include "adapter/LiveMemory.hpp"
#include "adapter/gen3/Codec.hpp"
#include "adapter/gen45/NdsBattle.hpp"
#include "adapter/gen45/Pk.hpp"
#include "adapter/gen5/Battle.hpp"
#include "adapter/gen5/Pokeparam.hpp"
#include "adapter/gen5/Save.hpp"
#include "test/Check.hpp"

#include <array>
#include <cstring>
#include <vector>

namespace {

std::array<uint8_t, emulocke::kPk5PartySize> pk5(uint16_t species, uint32_t pid, uint16_t hp = 22,
    uint16_t maxHp = 22, uint16_t atk = 0, uint16_t def = 0, uint8_t level = 6) {
    std::array<uint8_t, emulocke::kPk5PartySize> plain{};
    emulocke::store32(plain.data(), pid);
    emulocke::store16(plain.data() + 8, species);
    emulocke::encodeUtf16Text("Mon", {plain.data() + 0x48, 22});
    emulocke::encodeUtf16Text("Raval", {plain.data() + 0x68, 16});
    plain[0x8C] = level;
    emulocke::store16(plain.data() + 0x8E, hp);
    emulocke::store16(plain.data() + 0x90, maxHp);
    emulocke::store16(plain.data() + 0x92, atk);
    emulocke::store16(plain.data() + 0x94, def);
    emulocke::store16(plain.data() + 0x98, 8);
    std::array<uint8_t, emulocke::kPk5PartySize> pk{};
    REQUIRE(emulocke::encryptPk45(plain, pk));
    return pk;
}

void plantLive(std::vector<uint8_t>& ram, uint32_t addr, uint16_t species, uint16_t maxHp, uint16_t hp,
    uint8_t level = 0) {
    uint8_t* p = ram.data() + (addr - 0x02000000);
    emulocke::store16(p, species);
    emulocke::store16(p + 2, maxHp);
    emulocke::store16(p + 4, hp);
    emulocke::store16(p + 6, 0);
    if (level >= 1 && level <= 100) {
        p[emulocke::kBtlPokeparamLevel] = level;
    }
}

void plantStats(std::vector<uint8_t>& ram, uint32_t addr, uint16_t atk, uint16_t def, uint16_t spa,
    uint16_t spd, uint16_t spe) {
    uint8_t* p = ram.data() + (addr - 0x02000000) + emulocke::kBtlPokeparamStat;
    emulocke::store16(p, atk);
    emulocke::store16(p + 2, def);
    emulocke::store16(p + 4, spa);
    emulocke::store16(p + 6, spd);
    emulocke::store16(p + 8, spe);
}

void plantParam(std::vector<uint8_t>& ram, uint32_t addr, uint16_t species, uint16_t hp, int atkStage) {
    uint8_t* p = ram.data() + (addr - 0x02000000);
    emulocke::store32(p, 0x02001000);
    emulocke::store32(p + 4, 0x022349B4);
    emulocke::store32(p + 8, 0x11112222);
    emulocke::store32(p + 12, 1000);
    emulocke::store16(p + 16, species);
    emulocke::store16(p + 18, 0);
    emulocke::store16(p + 20, 22);
    emulocke::store16(p + 22, hp);
    for (int i = 0; i < 7; ++i) {
        p[24 + i] = 6;
    }
    p[24] = static_cast<uint8_t>(6 + atkStage);
}

void plantParty(std::vector<uint8_t>& ram) {
    const uint32_t saveBase = emulocke::kBwPartyLive - 8 - static_cast<uint32_t>(emulocke::kGen5Party);
    ram[emulocke::kBwPartyLive - 0x02000000 - 4] = 1;
    const auto snivy = pk5(495, 0x11112222, 22, 22, 11, 12);
    std::memcpy(ram.data() + (emulocke::kBwPartyLive - 0x02000000), snivy.data(), snivy.size());
    emulocke::encodeUtf16Text("Raval", {ram.data() + (saveBase - 0x02000000) + emulocke::kGen5Trainer + 4, 16});
    ram[emulocke::kBwEnemyPartyLive - 0x02000000 - 4] = 1;
    const auto nincada = pk5(290, 0xAABBCCDD, 22, 22, 10, 16);
    std::memcpy(ram.data() + (emulocke::kBwEnemyPartyLive - 0x02000000), nincada.data(), nincada.size());
}

}  // namespace

void testGen5Battle() {
    uint16_t hp = 0;
    std::array<uint8_t, 8> decoy{};
    emulocke::store16(decoy.data(), 20);
    emulocke::store16(decoy.data() + 2, 16);
    emulocke::store16(decoy.data() + 4, 8);
    emulocke::store16(decoy.data() + 6, 8);
    REQUIRE(!emulocke::readBtlHp(decoy, 20, 20, hp, 10, 16));

    std::array<uint8_t, 8> pkOrder{};
    emulocke::store16(pkOrder.data(), 14);
    emulocke::store16(pkOrder.data() + 2, 20);
    emulocke::store16(pkOrder.data() + 4, 10);
    emulocke::store16(pkOrder.data() + 6, 16);
    REQUIRE(emulocke::readBtlHp(pkOrder, 20, 20, hp, 10, 16));
    REQUIRE(hp == 14);

    std::array<uint8_t, 8> vsOrder{};
    emulocke::store16(vsOrder.data(), 20);
    emulocke::store16(vsOrder.data() + 2, 14);
    emulocke::store16(vsOrder.data() + 4, 10);
    emulocke::store16(vsOrder.data() + 6, 16);
    REQUIRE(emulocke::readBtlHp(vsOrder, 20, 20, hp, 10, 16));
    REQUIRE(hp == 14);

    std::array<uint8_t, 24> mixed{};
    emulocke::store16(mixed.data(), 20);
    emulocke::store16(mixed.data() + 2, 16);
    emulocke::store16(mixed.data() + 4, 8);
    emulocke::store16(mixed.data() + 6, 8);
    emulocke::store16(mixed.data() + 8, 14);
    emulocke::store16(mixed.data() + 10, 20);
    emulocke::store16(mixed.data() + 12, 10);
    emulocke::store16(mixed.data() + 14, 16);
    REQUIRE(emulocke::readBtlHp(mixed, 20, 20, hp, 10, 16));
    REQUIRE(hp == 14);

    std::array<uint8_t, 8> live{};
    emulocke::store16(live.data(), 22);
    emulocke::store16(live.data() + 2, 18);
    emulocke::store16(live.data() + 4, 99);
    emulocke::store16(live.data() + 6, 99);
    REQUIRE(emulocke::readBtlHp(live, 22, 22, hp, 11, 12));
    REQUIRE(hp == 18);

    std::array<uint8_t, 16> hpIsDef{};
    emulocke::store16(hpIsDef.data(), 290);
    emulocke::store16(hpIsDef.data() + 2, 0);
    emulocke::store16(hpIsDef.data() + 4, 20);
    emulocke::store16(hpIsDef.data() + 6, 16);
    emulocke::store16(hpIsDef.data() + 8, 99);
    emulocke::store16(hpIsDef.data() + 10, 99);
    REQUIRE(emulocke::readBtlHp(hpIsDef, 20, 20, hp, 10, 16));
    REQUIRE(hp == 16);
    REQUIRE(emulocke::readBtlCoreHp(hpIsDef, 290, hp, 10, 16));
    REQUIRE(hp == 16);

    std::array<uint8_t, 16> unrankedZero{};
    emulocke::store16(unrankedZero.data(), 495);
    emulocke::store16(unrankedZero.data() + 4, 22);
    REQUIRE(!emulocke::readBtlLiveHp(unrankedZero, 495, 22, 22, hp, 11, 12));
    std::array<uint8_t, 16> rankedZero{};
    emulocke::store16(rankedZero.data(), 495);
    emulocke::store16(rankedZero.data() + 4, 22);
    for (int i = 0; i < 7; ++i) {
        rankedZero[static_cast<std::size_t>(8 + i)] = 6;
    }
    REQUIRE(emulocke::readBtlLiveHp(rankedZero, 495, 22, 22, hp, 11, 12));
    REQUIRE(hp == 0);
    std::array<uint8_t, 16> liveCore{};
    emulocke::store16(liveCore.data(), 495);
    emulocke::store16(liveCore.data() + 4, 22);
    emulocke::store16(liveCore.data() + 6, 18);
    REQUIRE(emulocke::readBtlLiveHp(liveCore, 495, 22, 22, hp, 11, 12));
    REQUIRE(hp == 18);

    std::array<uint8_t, 16> liveHpIsAtk{};
    emulocke::store16(liveHpIsAtk.data(), 16);
    emulocke::store16(liveHpIsAtk.data() + 2, 21);
    emulocke::store16(liveHpIsAtk.data() + 4, 11);
    emulocke::store16(liveHpIsAtk.data() + 6, 0);
    emulocke::store16(liveHpIsAtk.data() + 8, 10);
    REQUIRE(emulocke::readBtlCoreHp(liveHpIsAtk, 16, hp, 11, 10));
    REQUIRE(hp == 11);

    std::array<uint8_t, 8> liveBw{};
    emulocke::store16(liveBw.data(), 495);
    emulocke::store16(liveBw.data() + 2, 24);
    emulocke::store16(liveBw.data() + 4, 24);
    REQUIRE(emulocke::readBtlCoreHp(liveBw, 495, hp, 11, 12));
    REQUIRE(hp == 24);
    REQUIRE(emulocke::readBtlLiveHp(liveBw, 495, 22, 22, hp, 11, 12));
    REQUIRE(hp == 24);
    emulocke::store16(liveBw.data() + 4, 12);
    REQUIRE(emulocke::readBtlLiveHp(liveBw, 495, 22, 22, hp, 11, 12));
    REQUIRE(hp == 12);
    emulocke::store16(liveBw.data() + 4, 0);
    REQUIRE(emulocke::readBtlLiveHp(liveBw, 495, 22, 22, hp, 11, 12));
    REQUIRE(hp == 0);

    std::array<uint8_t, 8> faintLive{};
    emulocke::store16(faintLive.data(), 22);
    emulocke::store16(faintLive.data() + 2, 0);
    emulocke::store16(faintLive.data() + 4, 99);
    emulocke::store16(faintLive.data() + 6, 99);
    REQUIRE(emulocke::readBtlHp(faintLive, 22, 22, hp, 11, 12));
    REQUIRE(hp == 0);

    std::array<uint8_t, 16> faintThenPk{};
    emulocke::store16(faintThenPk.data(), 22);
    emulocke::store16(faintThenPk.data() + 2, 0);
    emulocke::store16(faintThenPk.data() + 4, 99);
    emulocke::store16(faintThenPk.data() + 6, 99);
    emulocke::store16(faintThenPk.data() + 8, 22);
    emulocke::store16(faintThenPk.data() + 10, 22);
    emulocke::store16(faintThenPk.data() + 12, 11);
    emulocke::store16(faintThenPk.data() + 14, 12);
    REQUIRE(emulocke::readBtlHp(faintThenPk, 22, 22, hp, 11, 12));
    REQUIRE(hp == 0);

    std::array<uint8_t, 16> laterZero{};
    emulocke::store16(laterZero.data(), 22);
    emulocke::store16(laterZero.data() + 2, 18);
    emulocke::store16(laterZero.data() + 4, 99);
    emulocke::store16(laterZero.data() + 6, 99);
    emulocke::store16(laterZero.data() + 8, 22);
    emulocke::store16(laterZero.data() + 10, 0);
    REQUIRE(emulocke::readBtlHp(laterZero, 22, 22, hp, 11, 12));
    REQUIRE(hp == 18);

    emulocke::BattleBattler b;
    std::array<uint8_t, 7> tiny{};
    REQUIRE(!emulocke::readBtlPokeparam(tiny, 495, 22, b));

    std::array<uint8_t, 8> over{};
    emulocke::store16(over.data(), 495);
    emulocke::store16(over.data() + 4, 22);
    emulocke::store16(over.data() + 6, 40);
    REQUIRE(!emulocke::readBtlPokeparam(over, 495, 22, b));

    std::array<uint8_t, 8> zero{};
    emulocke::store16(zero.data(), 495);
    REQUIRE(!emulocke::readBtlPokeparam(zero, 495, 22, b));

    std::array<uint8_t, 16> ok{};
    emulocke::store16(ok.data(), 495);
    emulocke::store16(ok.data() + 4, 22);
    emulocke::store16(ok.data() + 6, 9);
    for (int i = 0; i < 7; ++i) {
        ok[8 + i] = 6;
    }
    ok[8] = 8;
    REQUIRE(emulocke::readBtlPokeparam(ok, 495, 22, b));
    REQUIRE(b.hp == 9);
    REQUIRE(b.stages[1] == 2);

    std::vector<uint8_t> ram(0x400000, 0);
    plantParty(ram);
    plantParam(ram, 0x02100000, 495, 22, 0);
    plantParam(ram, 0x02100000 + emulocke::kBtlPokeparamSize, 290, 22, 0);
    plantParam(ram, 0x02240000, 495, 18, 2);
    plantParam(ram, 0x02240000 + emulocke::kBtlPokeparamSize, 290, 9, -1);
    emulocke::store16(ram.data() + (0x02180000 - 0x02000000), 495);
    ram[0x02180000 - 0x02000000 + emulocke::kNdsBattleMonLevel] = 6;
    emulocke::store32(ram.data() + (0x02180000 - 0x02000000) + emulocke::kNdsBattleMonHp, 1);
    emulocke::store32(ram.data() + (0x02180000 - 0x02000000) + emulocke::kNdsBattleMonMaxHp, 22);

    emulocke::SpanMemory mem(0x02000000, ram);
    emulocke::GameSnapshot snap;
    REQUIRE(emulocke::fillGen5Live(mem, emulocke::kBwPartyLive, snap));
    REQUIRE(snap.battle.inBattle);
    REQUIRE(snap.battle.player.species == 495);
    REQUIRE(snap.battle.player.hp == 18);
    REQUIRE(snap.battle.player.maxHp == 22);
    REQUIRE(snap.battle.foe.species == 290);
    REQUIRE(snap.battle.foe.hp == 9);
    REQUIRE(snap.battle.foe.maxHp == 22);
    REQUIRE(snap.battle.foeCount == 1);
    REQUIRE(snap.party.mons[0].hp == 22);
    REQUIRE(snap.party.mons[0].maxHp == 22);

    plantParam(ram, 0x02100000, 495, 18, 0);
    plantParam(ram, 0x02100000 + emulocke::kBtlPokeparamSize, 290, 9, 0);
    emulocke::GameSnapshot hurt;
    REQUIRE(emulocke::fillGen5Live(mem, emulocke::kBwPartyLive, hurt));
    REQUIRE(hurt.battle.player.hp == 18);
    REQUIRE(hurt.battle.foe.hp == 9);
    REQUIRE(hurt.party.mons[0].hp == 22);

    std::vector<uint8_t> keep(0x400000, 0);
    plantParty(keep);
    plantParam(keep, 0x02100000, 495, 22, 0);
    plantParam(keep, 0x02100000 + emulocke::kBtlPokeparamSize, 290, 22, 0);
    plantParam(keep, 0x02240000, 495, 22, 0);
    plantParam(keep, 0x02240000 + emulocke::kBtlPokeparamSize, 290, 22, 0);
    emulocke::resetGen5Pokeparam();
    emulocke::SpanMemory keepMem(0x02000000, keep);
    emulocke::GameSnapshot keepSnap;
    REQUIRE(emulocke::fillGen5Live(keepMem, emulocke::kBwPartyLive, keepSnap));
    plantParam(keep, 0x02240000, 495, 18, 0);
    plantParam(keep, 0x02240000 + emulocke::kBtlPokeparamSize, 290, 9, 0);
    REQUIRE(emulocke::fillGen5Live(keepMem, emulocke::kBwPartyLive, keepSnap));
    REQUIRE(keepSnap.battle.player.hp == 18);
    REQUIRE(keepSnap.battle.foe.hp == 9);
    REQUIRE(keepSnap.party.mons[0].hp == 22);

    std::vector<uint8_t> liveRam(0x400000, 0);
    plantParty(liveRam);
    liveRam[emulocke::kBwPartyLive - 0x02000000 - 4] = 2;
    const auto pidgeyLive = pk5(16, 0x22223333, 17, 17, 10, 10, 4);
    std::memcpy(liveRam.data() + (emulocke::kBwPartyLive - 0x02000000) + emulocke::kPk5PartySize,
        pidgeyLive.data(), pidgeyLive.size());
    plantParam(liveRam, 0x02100000, 495, 22, 0);
    plantParam(liveRam, 0x02100000 + emulocke::kBtlPokeparamSize, 290, 22, 0);
    plantLive(liveRam, 0x0226D6B0, 495, 24, 24);
    plantLive(liveRam, 0x0226D6B0 + emulocke::kBtlPokeparamSize, 16, 17, 17);
    plantLive(liveRam, 0x0226D6B0 + 2 * emulocke::kBtlPokeparamSize, 290, 20, 20);
    plantLive(liveRam, 0x0226D6B0 + 5 * emulocke::kBtlPokeparamSize, 495, 24, 24);
    plantLive(liveRam, 0x0226D6B0 + 6 * emulocke::kBtlPokeparamSize, 16, 17, 17);
    plantLive(liveRam, 0x0226D6B0 + 7 * emulocke::kBtlPokeparamSize, 290, 20, 20);
    emulocke::resetGen5Pokeparam();
    emulocke::SpanMemory liveMem(0x02000000, liveRam);
    emulocke::GameSnapshot liveSnap;
    REQUIRE(emulocke::fillGen5Live(liveMem, emulocke::kBwPartyLive, liveSnap));
    REQUIRE(liveSnap.battle.player.hp == 24);
    REQUIRE(liveSnap.battle.player.maxHp == 24);
    REQUIRE(liveSnap.battle.foe.hp == 20);
    REQUIRE(liveSnap.battle.foe.maxHp == 20);
    plantLive(liveRam, 0x0226D6B0, 495, 24, 12);
    plantLive(liveRam, 0x0226D6B0 + 2 * emulocke::kBtlPokeparamSize, 290, 20, 16);
    REQUIRE(emulocke::fillGen5Live(liveMem, emulocke::kBwPartyLive, liveSnap));
    REQUIRE(liveSnap.battle.player.hp == 12);
    REQUIRE(liveSnap.battle.player.maxHp == 24);
    REQUIRE(liveSnap.battle.foe.hp == 16);
    REQUIRE(liveSnap.battle.foe.maxHp == 20);
    REQUIRE(liveSnap.party.mons[0].hp == 22);

    plantLive(liveRam, 0x0226D6B0, 495, 24, 0);
    plantLive(liveRam, 0x0226D6B0 + emulocke::kBtlPokeparamSize, 16, 21, 11, 6);
    plantLive(liveRam, 0x0226D6B0 + 2 * emulocke::kBtlPokeparamSize, 290, 20, 0);
    plantLive(liveRam, 0x0226D6B0 + 5 * emulocke::kBtlPokeparamSize, 495, 24, 0);
    plantLive(liveRam, 0x0226D6B0 + 6 * emulocke::kBtlPokeparamSize, 16, 21, 21, 6);
    plantLive(liveRam, 0x0226D6B0 + 7 * emulocke::kBtlPokeparamSize, 290, 20, 0);
    plantStats(liveRam, 0x0226D6B0 + emulocke::kBtlPokeparamSize, 10, 10, 10, 10, 12);
    plantStats(liveRam, 0x0226D6B0 + 6 * emulocke::kBtlPokeparamSize, 10, 10, 10, 10, 12);
    plantStats(liveRam, 0x0226D6B0 + 2 * emulocke::kBtlPokeparamSize, 10, 16, 7, 8, 11);
    plantStats(liveRam, 0x0226D6B0 + 7 * emulocke::kBtlPokeparamSize, 10, 16, 7, 8, 11);
    REQUIRE(emulocke::fillGen5Live(liveMem, emulocke::kBwPartyLive, liveSnap));
    REQUIRE(liveSnap.party.mons[0].hp == 0);
    REQUIRE(liveSnap.party.mons[0].pkHp == 22);
    REQUIRE(liveSnap.battle.player.species == 16);
    REQUIRE(liveSnap.battle.player.hp == 11);
    REQUIRE(liveSnap.battle.player.maxHp == 21);
    REQUIRE(liveSnap.battle.player.level == 6);
    REQUIRE(liveSnap.party.mons[1].level == 6);
    REQUIRE(liveSnap.party.mons[1].maxHp == 21);
    REQUIRE(liveSnap.party.mons[1].pkHp == 17);
    REQUIRE(liveSnap.party.mons[1].spAttack == 10);
    REQUIRE(liveSnap.party.mons[1].speed == 12);
    REQUIRE(liveSnap.battle.foeHp[0] == 0);
    REQUIRE(liveSnap.battle.foeSpe[0] == 11);
    REQUIRE(liveSnap.battle.foe.species == 290);

    plantLive(liveRam, 0x02300000, 16, 16, 16);
    REQUIRE(emulocke::fillGen5Live(liveMem, emulocke::kBwPartyLive, liveSnap));
    REQUIRE(liveSnap.battle.player.species == 16);
    REQUIRE(liveSnap.battle.player.hp == 11);
    REQUIRE(liveSnap.party.mons[0].hp == 0);
    REQUIRE(liveSnap.battle.foeHp[0] == 0);

    plantLive(liveRam, 0x0226D6B0 + 2 * emulocke::kBtlPokeparamSize, 56, 21, 21);
    plantLive(liveRam, 0x0226D6B0 + 7 * emulocke::kBtlPokeparamSize, 56, 21, 21);
    REQUIRE(emulocke::fillGen5Live(liveMem, emulocke::kBwPartyLive, liveSnap));
    REQUIRE(liveSnap.party.mons[0].hp == 0);
    REQUIRE(liveSnap.battle.player.hp == 11);
    REQUIRE(liveSnap.battle.foeHp[0] == 0);

    emulocke::resetGen5Pokeparam();
    std::vector<uint8_t> defHit(0x400000, 0);
    plantParty(defHit);
    plantParam(defHit, 0x02240000, 495, 22, 0);
    plantParam(defHit, 0x02240000 + emulocke::kBtlPokeparamSize, 290, 22, 0);
    emulocke::SpanMemory defMem(0x02000000, defHit);
    emulocke::GameSnapshot defSnap;
    REQUIRE(emulocke::fillGen5Live(defMem, emulocke::kBwPartyLive, defSnap));
    plantParam(defHit, 0x02240000, 495, 18, 0);
    plantParam(defHit, 0x02240000 + emulocke::kBtlPokeparamSize, 290, 16, 0);
    REQUIRE(emulocke::fillGen5Live(defMem, emulocke::kBwPartyLive, defSnap));
    REQUIRE(defSnap.battle.player.hp == 18);
    REQUIRE(defSnap.battle.foe.hp == 16);
    REQUIRE(defSnap.battle.foe.maxHp == 22);
    REQUIRE(defSnap.party.mons[0].hp == 22);

    std::vector<uint8_t> foeFirst(0x400000, 0);
    plantParty(foeFirst);
    plantParam(foeFirst, 0x02240000, 290, 22, 0);
    plantParam(foeFirst, 0x02240000 + emulocke::kBtlPokeparamSize, 495, 22, 0);
    emulocke::SpanMemory firstMem(0x02000000, foeFirst);
    emulocke::GameSnapshot firstSnap;
    REQUIRE(emulocke::fillGen5Live(firstMem, emulocke::kBwPartyLive, firstSnap));
    plantParam(foeFirst, 0x02240000, 290, 16, 0);
    plantParam(foeFirst, 0x02240000 + emulocke::kBtlPokeparamSize, 495, 18, 0);
    REQUIRE(emulocke::fillGen5Live(firstMem, emulocke::kBwPartyLive, firstSnap));
    REQUIRE(firstSnap.battle.player.hp == 18);
    REQUIRE(firstSnap.battle.foe.hp == 16);
    REQUIRE(firstSnap.party.mons[0].hp == 22);

    std::vector<uint8_t> split(0x400000, 0);
    plantParty(split);
    plantParam(split, 0x02240000, 290, 22, 0);
    plantParam(split, 0x02240000 + emulocke::kBtlPokeparamSize, 495, 22, 0);
    emulocke::SpanMemory splitMem(0x02000000, split);
    emulocke::GameSnapshot splitSnap;
    REQUIRE(emulocke::fillGen5Live(splitMem, emulocke::kBwPartyLive, splitSnap));
    plantParam(split, 0x02240000, 290, 16, 0);
    plantParam(split, 0x02240000 + emulocke::kBtlPokeparamSize, 495, 18, 0);
    REQUIRE(emulocke::fillGen5Live(splitMem, emulocke::kBwPartyLive, splitSnap));
    REQUIRE(splitSnap.battle.player.hp == 18);
    REQUIRE(splitSnap.battle.foe.hp == 16);
    REQUIRE(splitSnap.party.mons[0].hp == 22);

    ram[0x02100000 - 0x02000000 + 24] = 13;
    emulocke::GameSnapshot stale;
    REQUIRE(emulocke::fillGen5Live(mem, emulocke::kBwPartyLive, stale));
    REQUIRE(stale.battle.inBattle);
    REQUIRE(stale.battle.player.hp == 18);
    REQUIRE(stale.battle.player.stages[1] == 0);

    std::memcpy(ram.data() + (emulocke::kBwEnemyPartyLive - 0x02000000), pk5(495, 0x11112222).data(),
        emulocke::kPk5PartySize);
    emulocke::GameSnapshot copy;
    REQUIRE(emulocke::fillGen5Live(mem, emulocke::kBwPartyLive, copy));
    REQUIRE(!copy.battle.inBattle);

    std::vector<uint8_t> junk(0x400000, 0);
    plantParty(junk);
    emulocke::store16(junk.data() + 0x1000, 495);
    emulocke::store16(junk.data() + 0x1004, 22);
    emulocke::store16(junk.data() + 0x2000, 22);
    emulocke::store16(junk.data() + 0x2000 + emulocke::kBtlPokeparamSize, 22);
    junk[0x3008] = 11;
    emulocke::SpanMemory junkMem(0x02000000, junk);
    emulocke::GameSnapshot quiet;
    REQUIRE(emulocke::fillGen5Live(junkMem, emulocke::kBwPartyLive, quiet));
    REQUIRE(quiet.battle.inBattle);
    REQUIRE(quiet.battle.player.hp == 22);
    REQUIRE(quiet.battle.player.stages[1] == 0);
    REQUIRE(quiet.battle.foe.hp == 22);
    REQUIRE(quiet.battle.foe.stages[1] == 0);

    std::vector<uint8_t> junkZero(0x400000, 0);
    plantParty(junkZero);
    emulocke::store16(junkZero.data() + (0x02100000 - 0x02000000), 495);
    emulocke::store16(junkZero.data() + (0x02100000 - 0x02000000) + 4, 22);
    emulocke::store16(junkZero.data() + (0x02100000 - 0x02000000) + 548, 290);
    emulocke::store16(junkZero.data() + (0x02100000 - 0x02000000) + 552, 22);
    plantParam(junkZero, 0x02240000, 495, 18, 0);
    plantParam(junkZero, 0x02240000 + emulocke::kBtlPokeparamSize, 290, 16, 0);
    emulocke::SpanMemory junkZeroMem(0x02000000, junkZero);
    emulocke::GameSnapshot fromJunkZero;
    REQUIRE(emulocke::fillGen5Live(junkZeroMem, emulocke::kBwPartyLive, fromJunkZero));
    REQUIRE(fromJunkZero.battle.player.hp == 18);
    REQUIRE(fromJunkZero.battle.foe.hp == 16);
    REQUIRE(fromJunkZero.party.mons[0].hp == 22);

    std::vector<uint8_t> staleZero(0x400000, 0);
    plantParty(staleZero);
    plantParam(staleZero, 0x02100000, 495, 0, 0);
    plantParam(staleZero, 0x02100000 + emulocke::kBtlPokeparamSize, 290, 0, 0);
    plantParam(staleZero, 0x02300000, 495, 18, 0);
    plantParam(staleZero, 0x02300000 + emulocke::kBtlPokeparamSize, 290, 16, 0);
    emulocke::SpanMemory staleZeroMem(0x02000000, staleZero);
    emulocke::GameSnapshot fromStaleZero;
    REQUIRE(emulocke::fillGen5Live(staleZeroMem, emulocke::kBwPartyLive, fromStaleZero));
    REQUIRE(fromStaleZero.battle.player.hp == 18);
    REQUIRE(fromStaleZero.battle.foe.hp == 16);
    REQUIRE(fromStaleZero.party.mons[0].hp == 22);

    std::vector<uint8_t> startHurt(0x400000, 0);
    plantParty(startHurt);
    plantParam(startHurt, 0x02100000, 495, 21, 0);
    plantParam(startHurt, 0x02100000 + emulocke::kBtlPokeparamSize, 290, 6, 0);
    plantParam(startHurt, 0x02240000, 495, 22, 0);
    plantParam(startHurt, 0x02240000 + emulocke::kBtlPokeparamSize, 290, 22, 0);
    emulocke::SpanMemory startHurtMem(0x02000000, startHurt);
    emulocke::GameSnapshot fromStart;
    REQUIRE(emulocke::fillGen5Live(startHurtMem, emulocke::kBwPartyLive, fromStart));
    REQUIRE(fromStart.battle.player.hp == 22);
    REQUIRE(fromStart.battle.foe.hp == 22);
    REQUIRE(fromStart.party.mons[0].hp == 22);

    std::vector<uint8_t> tagged(0x400000, 0);
    plantParty(tagged);
    std::memcpy(tagged.data() + 0x200000, "N.pokeparty.c", 13);
    const auto hurtUs = pk5(495, 0x11112222, 22);
    std::memcpy(tagged.data() + 0x200000 + 32, hurtUs.data(), hurtUs.size());
    std::memcpy(tagged.data() + 0x201000, "N.pokeparty.c", 13);
    const auto hurtFoe = pk5(290, 0xAABBCCDD, 22);
    std::memcpy(tagged.data() + 0x201000 + 32, hurtFoe.data(), hurtFoe.size());
    emulocke::SpanMemory taggedMem(0x02000000, tagged);
    emulocke::GameSnapshot fromTag;
    REQUIRE(emulocke::fillGen5Live(taggedMem, emulocke::kBwPartyLive, fromTag));
    REQUIRE(fromTag.battle.player.hp == 22);
    REQUIRE(fromTag.battle.foe.hp == 22);
    REQUIRE(fromTag.party.mons[0].hp == 22);

    std::vector<uint8_t> pinRam(0x400000, 0);
    plantParty(pinRam);
    const auto snivyPin = pk5(495, 0x11112222, 24, 24, 13, 13);
    std::memcpy(pinRam.data() + (emulocke::kBwPartyLive - 0x02000000), snivyPin.data(), snivyPin.size());
    const auto nincadaPin = pk5(290, 0xAABBCCDD, 20, 20, 10, 16);
    std::memcpy(pinRam.data() + (emulocke::kBwEnemyPartyLive - 0x02000000), nincadaPin.data(),
        nincadaPin.size());
    uint8_t* pair = pinRam.data() + (0x02240000 - 0x02000000);
    emulocke::store16(pair, 495);
    emulocke::store16(pair + 2, 0);
    emulocke::store16(pair + 4, 24);
    emulocke::store16(pair + 6, 24);
    emulocke::store16(pair + 8, 13);
    emulocke::store16(pair + 10, 13);
    emulocke::store16(pair + 548, 290);
    emulocke::store16(pair + 550, 0);
    emulocke::store16(pair + 552, 20);
    emulocke::store16(pair + 554, 20);
    emulocke::store16(pair + 556, 10);
    emulocke::store16(pair + 558, 16);
    emulocke::SpanMemory pinMem(0x02000000, pinRam);
    emulocke::GameSnapshot pinned;
    REQUIRE(emulocke::fillGen5Live(pinMem, emulocke::kBwPartyLive, pinned));
    emulocke::store16(pair + 6, 12);
    emulocke::store16(pair + 554, 14);
    REQUIRE(emulocke::fillGen5Live(pinMem, emulocke::kBwPartyLive, pinned));
    REQUIRE(pinned.battle.foeAtk[0] == 10);
    REQUIRE(pinned.battle.foeDef[0] == 16);
    REQUIRE(pinned.battle.player.hp == 12);
    REQUIRE(pinned.battle.player.maxHp == 24);
    REQUIRE(pinned.battle.foe.hp == 14);
    REQUIRE(pinned.battle.foe.maxHp == 20);
    REQUIRE(pinned.party.mons[0].hp == 24);

    std::vector<uint8_t> bench(0x400000, 0);
    plantParty(bench);
    bench[emulocke::kBwEnemyPartyLive - 0x02000000 - 4] = 2;
    const auto purrloin = pk5(509, 0x55667788, 17, 17, 8, 8);
    std::memcpy(bench.data() + (emulocke::kBwEnemyPartyLive - 0x02000000) + emulocke::kPk5PartySize,
        purrloin.data(), purrloin.size());
    plantParam(bench, 0x02100000, 495, 22, 0);
    plantParam(bench, 0x02100000 + emulocke::kBtlPokeparamSize, 509, 17, 0);
    plantParam(bench, 0x02240000, 495, 18, 0);
    plantParam(bench, 0x02240000 + emulocke::kBtlPokeparamSize, 290, 9, 0);
    emulocke::SpanMemory benchMem(0x02000000, bench);
    emulocke::GameSnapshot fromBench;
    REQUIRE(emulocke::fillGen5Live(benchMem, emulocke::kBwPartyLive, fromBench));
    REQUIRE(fromBench.battle.foe.species == 290);
    REQUIRE(fromBench.battle.foe.partyIndex == 0);
    REQUIRE(fromBench.battle.foe.hp == 9);
    REQUIRE(fromBench.battle.foe.maxHp == 22);
    REQUIRE(fromBench.battle.player.hp == 18);
    REQUIRE(fromBench.battle.player.maxHp == 22);
    REQUIRE(fromBench.party.mons[0].hp == 22);

    std::vector<uint8_t> steal(0x400000, 0);
    plantParty(steal);
    steal[emulocke::kBwEnemyPartyLive - 0x02000000 - 4] = 2;
    std::memcpy(steal.data() + (emulocke::kBwEnemyPartyLive - 0x02000000) + emulocke::kPk5PartySize,
        purrloin.data(), purrloin.size());
    plantParam(steal, 0x02240000, 495, 18, 0);
    plantParam(steal, 0x02240000 + emulocke::kBtlPokeparamSize, 509, 17, 0);
    emulocke::SpanMemory stealMem(0x02000000, steal);
    emulocke::GameSnapshot stolen;
    REQUIRE(emulocke::fillGen5Live(stealMem, emulocke::kBwPartyLive, stolen));
    REQUIRE(stolen.battle.foe.species == 290);
    REQUIRE(stolen.battle.foe.partyIndex == 0);
    REQUIRE(stolen.battle.player.maxHp == 22);

    std::vector<uint8_t> ko(0x400000, 0);
    plantParty(ko);
    plantParam(ko, 0x02240000, 495, 22, 0);
    plantParam(ko, 0x02240000 + emulocke::kBtlPokeparamSize, 290, 22, 0);
    emulocke::SpanMemory koMem(0x02000000, ko);
    emulocke::GameSnapshot koSnap;
    REQUIRE(emulocke::fillGen5Live(koMem, emulocke::kBwPartyLive, koSnap));
    plantParam(ko, 0x02240000, 495, 0, 0);
    plantParam(ko, 0x02240000 + emulocke::kBtlPokeparamSize, 290, 0, 0);
    REQUIRE(emulocke::fillGen5Live(koMem, emulocke::kBwPartyLive, koSnap));
    REQUIRE(koSnap.battle.player.hp == 0);
    REQUIRE(koSnap.party.mons[0].hp == 0);
    REQUIRE(koSnap.battle.foe.hp == 0);
    REQUIRE(koSnap.battle.foeHp[0] == 0);

    std::vector<uint8_t> vs(0x400000, 0);
    plantParty(vs);
    vs[emulocke::kBwPartyLive - 0x02000000 - 4] = 2;
    const auto snivyDown = pk5(495, 0x11112222, 0, 22, 11, 12);
    std::memcpy(vs.data() + (emulocke::kBwPartyLive - 0x02000000), snivyDown.data(), snivyDown.size());
    const auto pidgey = pk5(16, 0x22223333, 22, 22, 10, 10);
    std::memcpy(vs.data() + (emulocke::kBwPartyLive - 0x02000000) + emulocke::kPk5PartySize,
        pidgey.data(), pidgey.size());
    vs[emulocke::kBwEnemyPartyLive - 0x02000000 - 4] = 2;
    const auto nincadaDown = pk5(290, 0xAABBCCDD, 0, 22, 10, 16);
    std::memcpy(vs.data() + (emulocke::kBwEnemyPartyLive - 0x02000000), nincadaDown.data(),
        nincadaDown.size());
    const auto mankey = pk5(56, 0x33445566, 22, 22, 14, 9);
    std::memcpy(vs.data() + (emulocke::kBwEnemyPartyLive - 0x02000000) + emulocke::kPk5PartySize,
        mankey.data(), mankey.size());
    plantParam(vs, 0x02240000, 16, 22, 0);
    plantParam(vs, 0x02240000 + emulocke::kBtlPokeparamSize, 56, 22, 0);
    emulocke::SpanMemory vsMem(0x02000000, vs);
    emulocke::GameSnapshot vsSnap;
    REQUIRE(emulocke::fillGen5Live(vsMem, emulocke::kBwPartyLive, vsSnap));
    REQUIRE(vsSnap.battle.player.species == 16);
    REQUIRE(vsSnap.battle.player.hp == 22);
    REQUIRE(vsSnap.party.mons[0].hp == 0);
    REQUIRE(vsSnap.battle.foe.species == 56);
    REQUIRE(vsSnap.battle.foe.hp == 22);
    REQUIRE(vsSnap.battle.foeHp[0] == 0);
}

