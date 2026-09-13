#include "adapter/Cartridge.hpp"
#include "adapter/GameAdapter.hpp"
#include "adapter/LiveMemory.hpp"
#include "adapter/gen3/Codec.hpp"
#include "adapter/gen4/Layout.hpp"
#include "adapter/gen45/Pk.hpp"
#include "test/Check.hpp"

#include <array>
#include <cstring>
#include <string>
#include <vector>

namespace {

std::vector<uint8_t> makeDpSave(const uint8_t* pk, std::size_t pkSize) {
    std::vector<uint8_t> sav(0x80000, 0);
    emulocke::encodeGen4Text("Juli", {sav.data() + emulocke::kDpTrainer, 16});
    emulocke::store32(sav.data() + emulocke::kDpTrainer + 0x10, 12345);
    sav[emulocke::kDpParty - 4] = 1;
    std::memcpy(sav.data() + emulocke::kDpParty, pk, pkSize);
    const std::size_t fo = emulocke::kDpGeneral - 0x14;
    emulocke::store32(sav.data() + fo + 4, 1);
    emulocke::store32(sav.data() + fo + 8, emulocke::kDpGeneral);
    emulocke::store32(sav.data() + fo + 12, emulocke::kGen4Magic);
    emulocke::encodeGen4Text("BOX 1", {sav.data() + emulocke::kDpGeneral + 4 + 18 * 30 * emulocke::kPkStoredSize, 16});
    return sav;
}

}  // namespace

void testGen4Adapter() {
    emulocke::Cartridge dia;
    std::memcpy(dia.code, "ADAE", 4);
    dia.revision = 13;
    REQUIRE(std::string(emulocke::adapterFor(dia)->id()) == "diamond-us");

    emulocke::Cartridge pt;
    std::memcpy(pt.code, "CPUE", 4);
    pt.revision = 1;
    REQUIRE(std::string(emulocke::adapterFor(pt)->id()) == "platinum-us-1.1");

    emulocke::Cartridge hg;
    std::memcpy(hg.code, "IPKE", 4);
    REQUIRE(std::string(emulocke::adapterFor(hg)->id()) == "heartgold-us");

    std::array<uint8_t, emulocke::kPk4PartySize> plain{};
    emulocke::store32(plain.data(), 0x12345678);
    emulocke::store16(plain.data() + 8, 25);
    emulocke::store32(plain.data() + 0x0C, 12345);
    emulocke::encodeGen4Text("PIKACHU", {plain.data() + 0x48, 22});
    emulocke::encodeGen4Text("Juli", {plain.data() + 0x68, 16});
    plain[0x8C] = 5;
    emulocke::store16(plain.data() + 0x8E, 20);
    emulocke::store16(plain.data() + 0x90, 20);
    std::array<uint8_t, emulocke::kPk4PartySize> pk{};
    REQUIRE(emulocke::encryptPk45(plain, pk));
    emulocke::Mon round;
    REQUIRE(emulocke::parsePk45(pk, false, round));
    REQUIRE(round.species == 25);
    REQUIRE(std::string(round.speciesName) == "PIKACHU");
    REQUIRE(std::string(round.nickname) == "PIKACHU");

    const std::vector<uint8_t> sav = makeDpSave(pk.data(), pk.size());
    const emulocke::GameAdapter* fromSave = emulocke::adapterForSave(sav);
    REQUIRE(fromSave != nullptr);
    REQUIRE(std::string(fromSave->id()) == "diamond-us");
    const emulocke::GameSnapshot snap = fromSave->readSave(sav);
    REQUIRE(snap.ok);
    REQUIRE(std::string(snap.trainer.name) == "Juli");
    REQUIRE(snap.party.count == 1);
    REQUIRE(snap.party.mons[0].species == 25);
    REQUIRE(snap.party.mons[0].level == 5);

    std::vector<uint8_t> ram(0x200000, 0);
    emulocke::store32(ram.data() + (emulocke::kDpSavePtr - 0x02000000), 0x02001000);
    ram[0x1000 + emulocke::kDpPartyFromSave - 4] = 1;
    std::memcpy(ram.data() + 0x1000 + emulocke::kDpPartyFromSave, pk.data(), pk.size());
    emulocke::SpanMemory mem(0x02000000, ram);
    const emulocke::GameSnapshot live = emulocke::adapterFor(dia)->readLive(mem);
    REQUIRE(live.ok);
    REQUIRE(live.party.count == 1);
    REQUIRE(live.party.mons[0].species == 25);
}
