#include "adapter/Cartridge.hpp"
#include "adapter/GameAdapter.hpp"
#include "adapter/LiveMemory.hpp"
#include "adapter/frlg/FrlgLayout.hpp"
#include "adapter/frlg/FrlgSave.hpp"
#include "adapter/gen3/BoxMon.hpp"
#include "adapter/gen3/Codec.hpp"
#include "test/Check.hpp"

#include <array>
#include <cstring>
#include <string>
#include <vector>

namespace {

emulocke::DecryptedMon partyBulba() {
    emulocke::DecryptedMon mon;
    mon.personality = 0xA1B2C3D4;
    mon.otId = 0x11112222;
    mon.species = 1;
    mon.experience = 135;
    mon.level = 5;
    mon.hp = 20;
    mon.maxHp = 20;
    mon.metGame = emulocke::kVersionFireRed;
    mon.metLevel = 5;
    mon.ball = 4;
    mon.language = 2;
    std::strcpy(mon.nickname, "BULBASAUR");
    std::strcpy(mon.otName, "RED");
    return mon;
}

}  // namespace

void testFrlgAdapter() {
    emulocke::Cartridge rev2;
    std::memcpy(rev2.code, "BPRE", 4);
    rev2.revision = 2;
    REQUIRE(emulocke::adapterFor(rev2) == nullptr);

    emulocke::Cartridge fr10;
    std::memcpy(fr10.code, "BPRE", 4);
    fr10.revision = 0;
    REQUIRE(std::string(emulocke::adapterFor(fr10)->id()) == "firered-us-1.0");

    emulocke::Cartridge fr11;
    std::memcpy(fr11.code, "BPRE", 4);
    fr11.revision = 1;
    const emulocke::GameAdapter* fr = emulocke::adapterFor(fr11);
    REQUIRE(fr != nullptr);
    REQUIRE(std::string(fr->id()) == "firered-us-1.1");

    emulocke::Cartridge lg10;
    std::memcpy(lg10.code, "BPGE", 4);
    lg10.revision = 0;
    REQUIRE(std::string(emulocke::adapterFor(lg10)->id()) == "leafgreen-us-1.0");

    emulocke::Cartridge lg11;
    std::memcpy(lg11.code, "BPGE", 4);
    lg11.revision = 1;
    REQUIRE(std::string(emulocke::adapterFor(lg11)->id()) == "leafgreen-us-1.1");

    emulocke::FrlgSaveBlocks blocks;
    emulocke::encodeGen3Text("RED", {blocks.block2.data(), 8});
    blocks.block2[8] = 0;
    emulocke::store32(blocks.block2.data() + 0x0A, 0x12345678);
    emulocke::store16(blocks.block2.data() + 0x0E, 10);
    blocks.block2[0x10] = 20;
    blocks.block2[0x11] = 30;
    blocks.block1[emulocke::kFrlgMapGroupOff] = 3;
    blocks.block1[emulocke::kFrlgMapNumOff] = 0;
    blocks.block1[emulocke::kFrlgPartyCountOff] = 1;
    std::array<uint8_t, emulocke::kPartyMonSize> party{};
    REQUIRE(emulocke::encryptPartyMon(partyBulba(), party));
    std::memcpy(blocks.block1.data() + emulocke::kFrlgPartyOff, party.data(), party.size());

    emulocke::DecryptedMon boxMon = partyBulba();
    boxMon.species = 4;
    std::strcpy(boxMon.nickname, "CHARMANDER");
    std::array<uint8_t, emulocke::kBoxMonSize> boxed{};
    REQUIRE(emulocke::encryptBoxMon(boxMon, boxed));
    std::memcpy(blocks.storage.data() + emulocke::kFrlgBoxStart, boxed.data(), boxed.size());
    emulocke::encodeGen3Text("BOX 1", {blocks.storage.data() + emulocke::kFrlgBoxNameOff, 9});

    const std::vector<uint8_t> sav = emulocke::writeFrlgSave(blocks);
    const emulocke::GameAdapter* fromSave = emulocke::adapterForSave(sav);
    REQUIRE(fromSave != nullptr);
    const emulocke::GameSnapshot snap = fromSave->readSave(sav);
    REQUIRE(snap.ok);
    REQUIRE(std::string(snap.trainer.name) == "RED");
    REQUIRE((snap.trainer.trainerId & 0xFFFFu) == 0x5678);
    REQUIRE(snap.party.count == 1);
    REQUIRE(snap.party.mons[0].species == 1);
    REQUIRE(snap.party.mons[0].level == 5);
    REQUIRE(snap.overworld.mapGroup == 3);
    REQUIRE(std::string(snap.overworld.mapName) == "PALLET TOWN");
    REQUIRE(snap.boxes.boxes[0].mons[0].species == 4);

    std::vector<uint8_t> ewram(0x40000, 0);
    ewram[emulocke::kFrlgPartyCount - 0x02000000] = 1;
    std::memcpy(ewram.data() + (emulocke::kFrlgParty - 0x02000000), party.data(), party.size());
    std::memcpy(ewram.data() + (emulocke::kFrlgSaveBlock2 - 0x02000000), blocks.block2.data(), blocks.block2.size());
    std::memcpy(ewram.data() + (emulocke::kFrlgSaveBlock1 - 0x02000000), blocks.block1.data(), 16);
    emulocke::SpanMemory mem(0x02000000, ewram);
    const emulocke::GameSnapshot live = fr->readLive(mem);
    REQUIRE(live.ok);
    REQUIRE(live.party.mons[0].species == 1);
    REQUIRE(std::string(live.trainer.name) == "RED");
    REQUIRE(std::string(live.overworld.mapName) == "PALLET TOWN");
}