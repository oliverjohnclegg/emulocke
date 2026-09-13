#include "adapter/gen3/BoxCrypt.hpp"
#include "adapter/gen3/BoxMon.hpp"
#include "adapter/gen3/Codec.hpp"
#include "adapter/frlg/FrlgNames.hpp"
#include "test/Check.hpp"

#include <array>
#include <cstring>
#include <string>

namespace {

emulocke::DecryptedMon sampleMon() {
    emulocke::DecryptedMon mon;
    mon.personality = 0x13579BDF;
    mon.otId = 0x02468ACE;
    mon.species = 1;
    mon.heldItem = 0;
    mon.experience = 135;
    mon.moves[0] = 33;
    mon.pp[0] = 35;
    mon.ivHp = 10;
    mon.ivAtk = 20;
    mon.level = 5;
    mon.hp = 19;
    mon.maxHp = 20;
    mon.attack = 11;
    mon.defense = 11;
    mon.speed = 11;
    mon.spAttack = 13;
    mon.spDefense = 13;
    mon.metGame = 4;
    mon.metLevel = 5;
    mon.ball = 4;
    mon.language = 2;
    std::strcpy(mon.nickname, "BULBASAUR");
    std::strcpy(mon.otName, "RED");
    return mon;
}

}  // namespace

void testGen3Codec() {
    char text[12];
    uint8_t encoded[10];
    emulocke::encodeGen3Text("RED", encoded);
    emulocke::decodeGen3Text(encoded, text, sizeof(text));
    REQUIRE(std::string(text) == "RED");

    REQUIRE(emulocke::natureOf(25) == 0);
    REQUIRE(emulocke::natureOf(1) == 1);
    REQUIRE(emulocke::isShiny(0, 0));
    REQUIRE(!emulocke::isShiny(0x12345678, 0x13579BDF));

    const auto src = sampleMon();
    std::array<uint8_t, emulocke::kPartyMonSize> raw{};
    REQUIRE(emulocke::encryptPartyMon(src, raw));
    emulocke::DecryptedMon out;
    REQUIRE(emulocke::decryptPartyMon(raw, out));
    REQUIRE(out.species == 1);
    REQUIRE(out.level == 5);
    REQUIRE(out.hp == 19);
    REQUIRE(out.maxHp == 20);
    REQUIRE(out.moves[0] == 33);
    REQUIRE(out.ivHp == 10);
    REQUIRE(out.ivAtk == 20);
    REQUIRE(out.metGame == 4);
    REQUIRE(std::string(out.nickname) == "BULBASAUR");
    REQUIRE(std::string(out.otName) == "RED");
    REQUIRE(out.checksumOk);

    std::array<uint8_t, emulocke::kBoxMonSize> box{};
    REQUIRE(emulocke::encryptBoxMon(src, box));
    emulocke::DecryptedMon boxed;
    REQUIRE(emulocke::decryptBoxMon(box, boxed));
    REQUIRE(boxed.species == 1);
    REQUIRE(std::string(emulocke::frlgSpeciesName(1)) == "BULBASAUR");
    REQUIRE(std::string(emulocke::frlgSpeciesName(151)) == "MEW");
    REQUIRE(std::string(emulocke::frlgSpeciesName(251)) == "CELEBI");
    REQUIRE(std::string(emulocke::frlgSpeciesName(277)) == "TREECKO");
    REQUIRE(std::string(emulocke::frlgSpeciesName(921)) == "SPRIGATITO");
    REQUIRE(std::string(emulocke::frlgSpeciesName(923)) == "MEOWSCARADA");
    REQUIRE(std::string(emulocke::frlgSpeciesName(1100)) == "DUDUNSPARCE");
    REQUIRE(std::string(emulocke::frlgSpeciesName(1268)) == "BASCULEGION");
    REQUIRE(std::string(emulocke::frlgSpeciesName(1374)) == "GOUGING FIRE");

    std::array<uint8_t, emulocke::kPartyMonSize> plain = raw;
    uint8_t data[48];
    std::memcpy(data, plain.data() + 0x20, 48);
    emulocke::xorBoxData(data, src.personality, src.otId);
    uint8_t g[12], a[12], e[12], m[12];
    emulocke::unshuffleBoxData(data, src.personality, g, a, e, m);
    std::memcpy(plain.data() + 0x20, g, 12);
    std::memcpy(plain.data() + 0x2C, a, 12);
    std::memcpy(plain.data() + 0x38, e, 12);
    std::memcpy(plain.data() + 0x44, m, 12);
    emulocke::store16(plain.data() + 0x1C, 0);
    emulocke::DecryptedMon fromPlain;
    REQUIRE(emulocke::decryptPartyMon(plain, fromPlain));
    REQUIRE(fromPlain.species == 1);
    REQUIRE(fromPlain.moves[0] == 33);
    REQUIRE(fromPlain.level == 5);
}