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

    std::array<uint8_t, emulocke::kPk5PartySize> plain{};
    emulocke::store32(plain.data(), 0x11112222);
    emulocke::store16(plain.data() + 8, 133);
    emulocke::encodeUtf16Text("Eevee", {plain.data() + 0x48, 22});
    emulocke::encodeUtf16Text("Raval", {plain.data() + 0x68, 16});
    plain[0x8C] = 17;
    emulocke::store16(plain.data() + 0x8E, 40);
    emulocke::store16(plain.data() + 0x90, 40);
    std::array<uint8_t, emulocke::kPk5PartySize> pk{};
    REQUIRE(emulocke::encryptPk45(plain, pk));

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

    sav[emulocke::kBwBadgeOff] = 1;
    const emulocke::GameSnapshot badged = fromSave->readSave(sav);
    REQUIRE(badged.gyms.earned == 1);

    std::vector<uint8_t> erased(0x80000, 0xFF);
    const emulocke::GameSnapshot blank = fromSave->readSave(erased);
    REQUIRE(!blank.ok);
    REQUIRE(blank.gyms.earned == 0);
    REQUIRE(blank.gyms.slots == 0);

    std::vector<uint8_t> ram(0x200000, 0);
    const uint32_t alt = 0x02100000;
    ram[alt - 0x02000000 + 4] = 1;
    std::memcpy(ram.data() + (alt - 0x02000000 + 8), pk.data(), pk.size());
    emulocke::SpanMemory mem(0x02000000, ram);
    emulocke::GameSnapshot live;
    REQUIRE(emulocke::fillGen5Live(mem, emulocke::kBwPartyLive, live));
    REQUIRE(live.party.count == 1);
    REQUIRE(live.party.mons[0].species == 133);
}
