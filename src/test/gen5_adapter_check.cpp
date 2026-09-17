#include "adapter/Cartridge.hpp"
#include "adapter/GameAdapter.hpp"
#include "adapter/LiveMemory.hpp"
#include "adapter/gen3/Codec.hpp"
#include "adapter/gen45/Pk.hpp"
#include "adapter/gen5/Save.hpp"
#include "test/Check.hpp"

#include <array>
#include <cstring>
#include <string>
#include <vector>

namespace {

std::array<uint8_t, emulocke::kPk5PartySize> makePk5(uint16_t species, uint16_t met = 0) {
    std::array<uint8_t, emulocke::kPk5PartySize> plain{};
    emulocke::store32(plain.data(), 0x11112222);
    emulocke::store16(plain.data() + 8, species);
    emulocke::encodeUtf16Text("Eevee", {plain.data() + 0x48, 22});
    emulocke::encodeUtf16Text("Raval", {plain.data() + 0x68, 16});
    emulocke::store16(plain.data() + 0x46, 99);
    emulocke::store16(plain.data() + 0x80, met);
    plain[0x8C] = 17;
    plain[0x41] = 12;
    emulocke::store16(plain.data() + 0x8E, 40);
    emulocke::store16(plain.data() + 0x90, 40);
    std::array<uint8_t, emulocke::kPk5PartySize> pk{};
    emulocke::encryptPk45(plain, pk);
    return pk;
}

void plantGen5Live(std::vector<uint8_t>& ram, uint32_t partyAddr, const std::array<uint8_t, emulocke::kPk5PartySize>& pk,
    uint8_t badges, bool trainer) {
    const uint32_t saveBase = partyAddr - 8 - static_cast<uint32_t>(emulocke::kGen5Party);
    const uint32_t off = saveBase - 0x02000000;
    ram[partyAddr - 0x02000000 - 4] = 1;
    std::memcpy(ram.data() + (partyAddr - 0x02000000), pk.data(), pk.size());
    if (trainer) {
        emulocke::encodeUtf16Text("Raval", {ram.data() + off + emulocke::kGen5Trainer + 4, 16});
    }
    std::memcpy(ram.data() + off + emulocke::kGen5Box, pk.data(), emulocke::kPkStoredSize);
    emulocke::store16(ram.data() + off + emulocke::kGen5Position, 14);
    ram[off + emulocke::kBwEventWork + emulocke::kBwFlagStart] = 1;
    ram[off + emulocke::kBwBadgeOff] = badges;
}

}  // namespace

void testGen5Adapter() {
    emulocke::Cartridge black;
    std::memcpy(black.code, "IRBO", 4);
    REQUIRE(std::string(emulocke::adapterFor(black)->id()) == "black-us");

    emulocke::Cartridge white;
    std::memcpy(white.code, "IRAO", 4);
    REQUIRE(std::string(emulocke::adapterFor(white)->id()) == "white-us");

    emulocke::Cartridge b2;
    std::memcpy(b2.code, "IREO", 4);
    REQUIRE(std::string(emulocke::adapterFor(b2)->id()) == "black2-us");

    const auto pk = makePk5(133, 14);
    emulocke::Mon parsed{};
    REQUIRE(emulocke::parsePk45(pk, true, parsed));
    REQUIRE(parsed.species == 133);
    REQUIRE(parsed.level == 17);
    REQUIRE(parsed.metLocation == 14);

    const auto junk = makePk5(9000);
    REQUIRE(!emulocke::parsePk45(junk, true, parsed));

    std::vector<uint8_t> sav(0x80000, 0);
    emulocke::encodeUtf16Text("BOX 1", {sav.data() + 4, 16});
    sav[emulocke::kGen5Party + 4] = 1;
    std::memcpy(sav.data() + emulocke::kGen5Party + 8, pk.data(), pk.size());
    emulocke::encodeUtf16Text("Raval", {sav.data() + emulocke::kGen5Trainer + 4, 16});
    emulocke::store32(sav.data() + emulocke::kGen5Trainer + 0x14, 45932);
    sav[emulocke::kGen5Trainer + 0x1F] = emulocke::kVersionBlack;

    const emulocke::GameAdapter* fromSave = emulocke::adapterForSave(sav);
    REQUIRE(fromSave != nullptr);
    REQUIRE(std::string(fromSave->id()) == "black-us");
    const emulocke::GameSnapshot snap = fromSave->readSave(sav);
    REQUIRE(snap.ok);
    REQUIRE(std::string(snap.trainer.name) == "Raval");
    REQUIRE(snap.party.count == 1);
    REQUIRE(snap.party.mons[0].species == 133);
    REQUIRE(std::string(snap.party.mons[0].speciesName) == "EEVEE");
    REQUIRE(std::string(snap.boxes.boxes[0].name) == "BOX 1");
    REQUIRE(snap.gyms.slots == 8);
    REQUIRE(snap.gyms.earned == 0);
    REQUIRE(snap.party.mons[0].nature == 12);
    REQUIRE(std::string(fromSave->species(133).slug) == "eevee");

    sav[emulocke::kBwBadgeOff] = 1;
    const emulocke::GameSnapshot badged = fromSave->readSave(sav);
    REQUIRE(badged.gyms.earned == 1);

    std::vector<uint8_t> erased(0x80000, 0xFF);
    const emulocke::GameSnapshot blank = fromSave->readSave(erased);
    REQUIRE(!blank.ok);
    REQUIRE(blank.gyms.earned == 0);
    REQUIRE(blank.gyms.slots == 0);

    std::vector<uint8_t> noise(0x10000, 0xA5);
    emulocke::SpanMemory noiseMem(0x02000000, noise);
    emulocke::GameSnapshot noiseSnap;
    REQUIRE(!emulocke::fillGen5Live(noiseMem, emulocke::kBwPartyLive, noiseSnap));
    REQUIRE(!noiseSnap.ok);
    REQUIRE(noiseSnap.gyms.slots == 0);
    REQUIRE(noiseSnap.party.count == 0);

    std::vector<uint8_t> stray(0x200000, 0);
    plantGen5Live(stray, 0x02100000, pk, 4, false);
    emulocke::SpanMemory strayMem(0x02000000, stray);
    emulocke::GameSnapshot straySnap;
    REQUIRE(!emulocke::fillGen5Live(strayMem, emulocke::kBwPartyLive, straySnap));
    REQUIRE(straySnap.gyms.slots == 0);

    std::vector<uint8_t> ram(0x200000, 0);
    plantGen5Live(ram, 0x02100000, pk, 1, true);
    emulocke::SpanMemory mem(0x02000000, ram);
    emulocke::GameSnapshot live;
    REQUIRE(emulocke::fillGen5Live(mem, emulocke::kBwPartyLive, live));
    REQUIRE(live.party.count == 1);
    REQUIRE(live.party.mons[0].species == 133);
    REQUIRE(!live.battle.inBattle);
    REQUIRE(live.boxes.boxes[0].mons[0].species == 133);
    REQUIRE(live.gyms.slots == 8);
    REQUIRE(live.gyms.earned == 1);
    REQUIRE(emulocke::progressFlag(live.progress, 0));

    std::vector<uint8_t> home(0x400000, 0);
    plantGen5Live(home, emulocke::kBwPartyLive, makePk5(498), 0, true);
    emulocke::SpanMemory homeMem(0x02000000, home);
    emulocke::GameSnapshot homeSnap;
    REQUIRE(emulocke::fillGen5Live(homeMem, emulocke::kBwPartyLive, homeSnap));
    REQUIRE(homeSnap.party.mons[0].species == 498);
    REQUIRE(homeSnap.progress.starterSpecies == 498);
    REQUIRE(homeSnap.gyms.slots == 8);
    REQUIRE(homeSnap.gyms.earned == 0);
}
