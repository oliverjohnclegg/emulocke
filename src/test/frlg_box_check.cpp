#include "adapter/frlg/CfruBoxes.hpp"
#include "adapter/frlg/CfruExpanded.hpp"
#include "adapter/frlg/FrlgAdapter.hpp"
#include "adapter/frlg/FrlgLayout.hpp"
#include "adapter/frlg/FrlgSave.hpp"
#include "adapter/gen3/BoxFields.hpp"
#include "adapter/gen3/BoxMon.hpp"
#include "adapter/gen3/Codec.hpp"
#include "test/Check.hpp"

#include <array>
#include <cstring>
#include <string>
#include <vector>

namespace {

void packCfru(std::span<uint8_t> raw, emulocke::DecryptedMon in) {
    std::memset(raw.data(), 0, emulocke::kCfruBoxMonSize);
    if (in.language == 0) {
        in.language = 2;
    }
    emulocke::pushHeader(raw.data(), in);
    emulocke::store16(raw.data() + 28, in.species);
    emulocke::store16(raw.data() + 30, in.heldItem);
    emulocke::store32(raw.data() + 32, in.experience);
    raw[38] = in.ball ? in.ball : 4;
    uint64_t moves = 0;
    for (int i = 0; i < 4; ++i) {
        moves |= static_cast<uint64_t>(in.moves[i] & 0x3FFu) << (10 * i);
    }
    emulocke::store32(raw.data() + 39, static_cast<uint32_t>(moves));
    raw[43] = static_cast<uint8_t>(moves >> 32);
    raw[44] = in.evHp;
    raw[45] = in.evAtk;
    raw[46] = in.evDef;
    raw[47] = in.evSpe;
    raw[48] = in.evSpa;
    raw[49] = in.evSpd;
    uint8_t misc[12];
    emulocke::pushMisc(misc, in);
    std::memcpy(raw.data() + 50, misc, 8);
}

emulocke::DecryptedMon cfruMon(uint16_t species, const char* nick) {
    emulocke::DecryptedMon mon;
    mon.personality = 0xA1B2C3D4;
    mon.otId = 0x11112222;
    mon.species = species;
    mon.experience = 125000;
    mon.moves[0] = 33;
    mon.language = 2;
    mon.ball = 4;
    std::strcpy(mon.nickname, nick);
    std::strcpy(mon.otName, "RED");
    return mon;
}

void setSig(std::vector<uint8_t>& sav, uint32_t sig) {
    for (int i = 0; i < 14; ++i) {
        emulocke::store32(sav.data() + static_cast<std::size_t>(i) * 0x1000 + 0xFF8, sig);
    }
}

emulocke::GameSnapshot readSav(const std::vector<uint8_t>& sav) {
    emulocke::FrlgAdapter fr(emulocke::FrlgEdition::FireRed, 1);
    return fr.readSave(sav);
}

}  // namespace

void testFrlgBoxes() {
    emulocke::FrlgSaveBlocks blocks;
    std::array<uint8_t, emulocke::kCfruBoxMonSize> sealeo{};
    std::array<uint8_t, emulocke::kCfruBoxMonSize> servine{};
    packCfru(sealeo, cfruMon(342, "SEALEO"));
    packCfru(servine, cfruMon(549, "SERVINE"));
    std::memcpy(blocks.storage.data() + 4, sealeo.data(), sealeo.size());
    std::memcpy(blocks.storage.data() + 4 + emulocke::kCfruBoxMonSize, servine.data(), servine.size());

    emulocke::DecryptedMon asVanilla;
    const bool vanillaHit = emulocke::decryptBoxMon({blocks.storage.data() + 4, emulocke::kBoxMonSize}, asVanilla);
    REQUIRE(!(vanillaHit && asVanilla.species == 342));

    std::vector<uint8_t> sav = emulocke::writeFrlgSave(blocks);
    setSig(sav, emulocke::kUnboundSignature210);
    emulocke::GameSnapshot snap = readSav(sav);
    REQUIRE(snap.boxes.boxes[0].mons[0].species == 342);
    REQUIRE(snap.boxes.boxes[0].mons[1].species == 549);
    REQUIRE(snap.boxes.boxes[0].mons[0].species != 281);
    REQUIRE(std::string(snap.boxes.boxes[0].mons[0].speciesName) == "SEALEO");
    REQUIRE(std::string(snap.boxes.boxes[0].mons[1].speciesName) == "SERVINE");

    sav = emulocke::writeFrlgSave(blocks);
    snap = readSav(sav);
    REQUIRE(snap.boxes.boxes[0].mons[0].species == 342);
    REQUIRE(snap.boxes.boxes[0].mons[1].species == 549);

    std::array<uint8_t, emulocke::kCfruBoxMonSize> skorupi{};
    packCfru(skorupi, cfruMon(504, "SKORUPI"));
    std::memcpy(blocks.flash30.data() + emulocke::kCfruFlash30BoxOff, skorupi.data(), skorupi.size());
    packCfru({blocks.block2.data() + emulocke::kCfruBox25Off, emulocke::kCfruBoxMonSize}, cfruMon(1, "BULBASAUR"));
    emulocke::GameSnapshot extra;
    extra.adapterId = "firered-us-1.1";
    extra.origin = emulocke::SnapshotOrigin::Save;
    blocks.fileSignature = emulocke::kUnboundSignature210;
    emulocke::fillSnapshotFromFrlg(blocks, extra);
    REQUIRE(extra.boxes.boxes[19].mons[0].species == 504);
    REQUIRE(extra.boxes.boxes[24].mons[0].species == 1);

    std::vector<uint8_t> ewram(0x40000, 0);
    std::memcpy(ewram.data() + (emulocke::kFrlgStorage + 4 - 0x02000000), sealeo.data(), sealeo.size());
    std::memcpy(ewram.data() + (emulocke::kFrlgStorage + 4 - 0x02000000) + emulocke::kCfruBoxMonSize, servine.data(),
                servine.size());
    std::memcpy(ewram.data() + (emulocke::kCfruBox20Live - 0x02000000), skorupi.data(), skorupi.size());
    emulocke::SpanMemory mem(0x02000000, ewram);
    emulocke::FrlgAdapter fr(emulocke::FrlgEdition::FireRed, 1);
    const emulocke::GameSnapshot live = fr.readLive(mem);
    REQUIRE(live.boxes.boxes[0].mons[0].species == 342);
    REQUIRE(live.boxes.boxes[0].mons[1].species == 549);
    REQUIRE(live.boxes.boxes[0].mons[0].species != 281);
    REQUIRE(live.boxes.boxes[19].mons[0].species == 504);
}
