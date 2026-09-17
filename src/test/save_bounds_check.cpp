#include "adapter/gen3/Codec.hpp"
#include "adapter/gen4/Layout.hpp"
#include "adapter/gen4/Save.hpp"
#include "adapter/gen5/Save.hpp"
#include "test/Check.hpp"

#include <string>
#include <vector>

namespace {

std::vector<uint8_t> gen4SaveWithFooter(const emulocke::Gen4Layout& layout, std::size_t size) {
    std::vector<uint8_t> sav(size, 0);
    const std::size_t fo = layout.generalSize - layout.footerSize;
    if (layout.footerSize == 0x10) {
        emulocke::store32(sav.data() + fo, 1);
        emulocke::store32(sav.data() + fo + 8, emulocke::kGen4Magic);
    } else {
        emulocke::store32(sav.data() + fo + 4, 1);
        emulocke::store32(sav.data() + fo + 12, emulocke::kGen4Magic);
    }
    emulocke::encodeGen4Text("Juli", {sav.data() + layout.trainerOff, 16});
    return sav;
}

void checkGen4(const emulocke::Gen4Layout& layout) {
    const std::size_t needed = emulocke::gen4PartitionBytes(layout);
    REQUIRE(needed > layout.storageStart + 0x1000);
    REQUIRE(emulocke::activeGen4Slot(gen4SaveWithFooter(layout, layout.generalSize), layout) == 0);

    emulocke::GameSnapshot snap{};
    REQUIRE(!emulocke::readGen4Save(gen4SaveWithFooter(layout, layout.storageStart + 0x1001), layout, snap));
    REQUIRE(!emulocke::readGen4Save(gen4SaveWithFooter(layout, needed - 1), layout, snap));
    REQUIRE(emulocke::readGen4Save(gen4SaveWithFooter(layout, needed), layout, snap));
    REQUIRE(std::string(snap.trainer.name) == "Juli");
}

void checkGen5() {
    emulocke::GameSnapshot snap{};
    std::vector<uint8_t> tooShort(emulocke::kGen5MinSave - 1, 0);
    emulocke::encodeUtf16Text("Raval", {tooShort.data() + emulocke::kGen5Trainer + 4, 16});
    REQUIRE(!emulocke::readGen5Save(tooShort, snap));

    std::vector<uint8_t> exact(emulocke::kGen5MinSave, 0);
    emulocke::encodeUtf16Text("Raval", {exact.data() + emulocke::kGen5Trainer + 4, 16});
    REQUIRE(emulocke::readGen5Save(exact, snap));
    REQUIRE(std::string(snap.trainer.name) == "Raval");
    REQUIRE(emulocke::readGen5Save(exact, snap, true));
}

void checkPk45() {
    std::vector<uint8_t> plain(emulocke::kPk4PartySize, 0);
    emulocke::store32(plain.data(), 0x12345678);
    emulocke::store16(plain.data() + 8, 25);
    plain[0x8C] = 7;
    emulocke::store16(plain.data() + 0x8E, 20);
    emulocke::store16(plain.data() + 0x90, 20);
    std::vector<uint8_t> oversized(emulocke::kPk4PartySize + 64, 0);
    REQUIRE(emulocke::encryptPk45(plain, oversized));
    const std::span<const uint8_t> encrypted(oversized);
    emulocke::Mon mon{};
    REQUIRE(!emulocke::parsePk45(encrypted, false, mon));
    REQUIRE(emulocke::parsePk45(encrypted.first(emulocke::kPk4PartySize), false, mon));
    REQUIRE(mon.level == 7);
    REQUIRE(mon.maxHp == 20);
    REQUIRE(!emulocke::parsePk45(encrypted.first(emulocke::kPkStoredSize - 1), false, mon));
    REQUIRE(emulocke::parsePk45(encrypted.first(emulocke::kPkStoredSize), false, mon));
    REQUIRE(mon.level == 0);

    std::vector<uint8_t> unknown = plain;
    emulocke::store16(unknown.data() + 8, 9000);
    std::vector<uint8_t> unknownEnc(emulocke::kPk4PartySize, 0);
    REQUIRE(emulocke::encryptPk45(unknown, unknownEnc));
    REQUIRE(!emulocke::parsePk45(unknownEnc, false, mon));

    std::vector<uint8_t> noHp = plain;
    emulocke::store16(noHp.data() + 0x90, 0);
    std::vector<uint8_t> noHpEnc(emulocke::kPk4PartySize, 0);
    REQUIRE(emulocke::encryptPk45(noHp, noHpEnc));
    REQUIRE(!emulocke::parsePk45(noHpEnc, false, mon));
}

}  // namespace

void testSaveBounds() {
    checkGen4(emulocke::dpLayout());
    checkGen4(emulocke::ptLayout());
    checkGen4(emulocke::hgssLayout());
    checkGen5();
    checkPk45();
}
