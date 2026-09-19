#include "adapter/Cartridge.hpp"
#include "adapter/GameAdapter.hpp"
#include "adapter/LiveMemory.hpp"
#include "adapter/gen3/Codec.hpp"
#include "adapter/gen4/Battle.hpp"
#include "adapter/gen4/Layout.hpp"
#include "adapter/gen45/NdsBattle.hpp"
#include "adapter/gen45/Pk.hpp"
#include "test/Check.hpp"

#include <array>
#include <cstring>
#include <vector>

namespace {

std::array<uint8_t, emulocke::kPk4PartySize> pk4(uint16_t species, uint32_t pid) {
    std::array<uint8_t, emulocke::kPk4PartySize> plain{};
    emulocke::store32(plain.data(), pid);
    emulocke::store16(plain.data() + 8, species);
    emulocke::store32(plain.data() + 0x0C, 12345);
    emulocke::encodeGen4Text("MON", {plain.data() + 0x48, 22});
    emulocke::encodeGen4Text("Juli", {plain.data() + 0x68, 16});
    plain[0x8C] = 5;
    emulocke::store16(plain.data() + 0x8E, 20);
    emulocke::store16(plain.data() + 0x90, 20);
    std::array<uint8_t, emulocke::kPk4PartySize> pk{};
    REQUIRE(emulocke::encryptPk45(plain, pk));
    return pk;
}

void plantMon(std::vector<uint8_t>& ram, uint32_t addr, uint16_t species, uint16_t hp, int atkStage) {
    uint8_t* p = ram.data() + (addr - 0x02000000);
    emulocke::store16(p, species);
    for (int i = 0; i < 5; ++i) {
        emulocke::store16(p + 2 + i * 2, 40);
    }
    p[emulocke::kNdsBattleMonLevel] = 5;
    for (int i = 0; i < 8; ++i) {
        p[emulocke::kNdsBattleMonStages + i] = 6;
    }
    p[emulocke::kNdsBattleMonStages + 1] = static_cast<uint8_t>(6 + atkStage);
    emulocke::store32(p + emulocke::kNdsBattleMonHp, hp);
    emulocke::store32(p + emulocke::kNdsBattleMonMaxHp, 20);
}

}  // namespace

void testGen4Battle() {
    std::vector<uint8_t> ram(0x200000, 0);
    emulocke::store32(ram.data() + (emulocke::kDpSavePtr - 0x02000000), 0x02001000);
    ram[0x1000 + emulocke::kDpPartyFromSave - 4] = 1;
    const auto pika = pk4(25, 0x12345678);
    std::memcpy(ram.data() + 0x1000 + emulocke::kDpPartyFromSave, pika.data(), pika.size());
    const uint32_t heap = 0x02008000;
    emulocke::store32(ram.data() + (0x02001000 + emulocke::kDpEnemyPtrOff - 0x02000000), heap);
    ram[heap + emulocke::kDpEnemyPartyAdd - 0x02000000 - 4] = 1;
    const auto foe = pk4(399, 0x99AABBCC);
    std::memcpy(ram.data() + (heap + emulocke::kDpEnemyPartyAdd - 0x02000000), foe.data(), foe.size());
    const uint32_t foeHp = 0x02001000 + emulocke::kDpFoeHpOff;
    const uint32_t foeMon = foeHp - emulocke::kNdsBattleMonHp;
    plantMon(ram, foeMon - emulocke::kNdsBattleMonSize, 25, 11, 1);
    plantMon(ram, foeMon, 399, 7, 3);

    emulocke::Cartridge dia;
    std::memcpy(dia.code, "ADAE", 4);
    dia.revision = 13;
    emulocke::Cartridge pt;
    std::memcpy(pt.code, "CPUE", 4);
    pt.revision = 1;
    emulocke::SpanMemory mem(0x02000000, ram);
    const emulocke::GameSnapshot live = emulocke::adapterFor(dia)->readLive(mem);
    REQUIRE(live.ok);
    REQUIRE(live.battle.inBattle);
    REQUIRE(live.battle.player.species == 25);
    REQUIRE(live.battle.player.hp == 11);
    REQUIRE(live.battle.player.stages[1] == 1);
    REQUIRE(live.battle.foe.species == 399);
    REQUIRE(live.battle.foe.hp == 7);
    REQUIRE(live.battle.foe.stages[1] == 3);
    REQUIRE(live.battle.foeSpecies[0] == 399);

    std::vector<uint8_t> ptRam(0x200000, 0);
    emulocke::store32(ptRam.data() + (emulocke::kPtSavePtr - 0x02000000), 0x02001000);
    ptRam[0x1000 + emulocke::kPtPartyFromSave - 4] = 1;
    std::memcpy(ptRam.data() + 0x1000 + emulocke::kPtPartyFromSave, pika.data(), pika.size());
    emulocke::store32(ptRam.data() + (0x02001000 + emulocke::kPtEnemyPtrOff - 0x02000000), heap);
    ptRam[heap + emulocke::kPtEnemyPartyAdd - 0x02000000 - 4] = 1;
    std::memcpy(ptRam.data() + (heap + emulocke::kPtEnemyPartyAdd - 0x02000000), foe.data(), foe.size());
    const uint32_t ptFoeHp = 0x02001000 + emulocke::kPtFoeHpOff;
    const uint32_t ptFoeMon = ptFoeHp - emulocke::kNdsBattleMonHp;
    plantMon(ptRam, ptFoeMon - emulocke::kNdsBattleMonSize, 25, 11, 1);
    plantMon(ptRam, ptFoeMon, 399, 7, 3);
    emulocke::SpanMemory ptMem(0x02000000, ptRam);
    const emulocke::GameSnapshot ptLive = emulocke::adapterFor(pt)->readLive(ptMem);
    REQUIRE(ptLive.ok);
    REQUIRE(ptLive.battle.inBattle);
    REQUIRE(ptLive.battle.player.species == 25);
    REQUIRE(ptLive.battle.foe.species == 399);
    REQUIRE(ptLive.battle.foeSpecies[0] == 399);
}
