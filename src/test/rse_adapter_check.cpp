#include "adapter/Cartridge.hpp"
#include "adapter/GameAdapter.hpp"
#include "adapter/LiveMemory.hpp"
#include "adapter/gen3/BoxMon.hpp"
#include "adapter/gen3/Codec.hpp"
#include "adapter/rse/RseLayout.hpp"
#include "adapter/rse/RseSave.hpp"
#include "test/Check.hpp"

#include <array>
#include <cstring>
#include <string>
#include <vector>

void testRseAdapter() {
    emulocke::Cartridge ruby1;
    std::memcpy(ruby1.code, "AXVE", 4);
    ruby1.revision = 1;
    REQUIRE(std::string(emulocke::adapterFor(ruby1)->id()) == "ruby-us-1.1");

    emulocke::Cartridge ruby2;
    std::memcpy(ruby2.code, "AXVE", 4);
    ruby2.revision = 2;
    REQUIRE(std::string(emulocke::adapterFor(ruby2)->id()) == "ruby-us");

    emulocke::Cartridge sap;
    std::memcpy(sap.code, "AXPE", 4);
    sap.revision = 2;
    REQUIRE(std::string(emulocke::adapterFor(sap)->id()) == "sapphire-us");

    emulocke::Cartridge em;
    std::memcpy(em.code, "BPEE", 4);
    REQUIRE(std::string(emulocke::adapterFor(em)->id()) == "emerald-us");

    emulocke::RseSaveBlocks blocks;
    emulocke::encodeGen3Text("MAY", {blocks.block2.data(), 8});
    blocks.block2[8] = 1;
    emulocke::store32(blocks.block2.data() + 0x0A, 0x22223333);
    emulocke::store16(blocks.block2.data() + 0x0E, 3);
    blocks.block1[emulocke::kRsePartyCountOff] = 1;
    emulocke::DecryptedMon mon;
    mon.personality = 0x11111111;
    mon.otId = 0x22223333;
    mon.species = 277;
    mon.level = 5;
    mon.hp = 18;
    mon.maxHp = 18;
    mon.metGame = emulocke::kVersionRuby;
    mon.language = 2;
    std::strcpy(mon.nickname, "TREECKO");
    std::strcpy(mon.otName, "MAY");
    std::array<uint8_t, emulocke::kPartyMonSize> party{};
    REQUIRE(emulocke::encryptPartyMon(mon, party));
    std::memcpy(blocks.block1.data() + emulocke::kRsePartyOff, party.data(), party.size());
    emulocke::encodeGen3Text("BOX 1", {blocks.storage.data() + emulocke::kRseBoxNameOff, 9});

    const std::vector<uint8_t> sav = emulocke::writeRseSave(blocks);
    const emulocke::GameAdapter* fromSave = emulocke::adapterForSave(sav);
    REQUIRE(fromSave != nullptr);
    const emulocke::GameSnapshot snap = fromSave->readSave(sav);
    REQUIRE(snap.ok);
    REQUIRE(std::string(snap.trainer.name) == "MAY");
    REQUIRE(snap.party.count == 1);
    REQUIRE(snap.party.mons[0].species == 277);
    REQUIRE(std::string(snap.party.mons[0].speciesName) == "TREECKO");

    std::vector<uint8_t> ewram(0x40000, 0);
    ewram[emulocke::kEmPartyCount - 0x02000000] = 1;
    std::memcpy(ewram.data() + (emulocke::kEmParty - 0x02000000), party.data(), party.size());
    std::memcpy(ewram.data() + (emulocke::kEmSaveBlock2 - 0x02000000), blocks.block2.data(), 32);
    emulocke::SpanMemory mem(0x02000000, ewram);
    const emulocke::GameSnapshot live = emulocke::adapterFor(em)->readLive(mem);
    REQUIRE(live.ok);
    REQUIRE(live.party.mons[0].species == 277);
    REQUIRE(std::string(live.trainer.name) == "MAY");
}
