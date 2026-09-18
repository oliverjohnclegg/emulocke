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
#include <cstdio>
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

int boxedCount(const emulocke::GameSnapshot& snap) {
    int n = 0;
    for (const emulocke::PcBox& box : snap.boxes.boxes) {
        for (const emulocke::Mon& mon : box.mons) {
            if (mon.species != 0) {
                ++n;
            }
        }
    }
    return n;
}

bool namedBoxMon(const emulocke::GameSnapshot& snap) {
    for (const emulocke::PcBox& box : snap.boxes.boxes) {
        for (const emulocke::Mon& mon : box.mons) {
            if (std::strncmp(mon.nickname, "BOX ", 4) == 0) {
                return true;
            }
        }
    }
    return false;
}

}  // namespace

void testFrlgBoxes() {
    emulocke::FrlgSaveBlocks blocks;
    std::array<uint8_t, emulocke::kCfruBoxMonSize> sealeo{};
    std::array<uint8_t, emulocke::kCfruBoxMonSize> servine{};
    std::array<uint8_t, emulocke::kCfruBoxMonSize> floette{};
    packCfru(sealeo, cfruMon(342, "SEALEO"));
    packCfru(servine, cfruMon(549, "SERVINE"));
    packCfru(floette, cfruMon(847, "FLOETTE"));
    std::memcpy(blocks.storage.data() + 4, sealeo.data(), sealeo.size());
    std::memcpy(blocks.storage.data() + 4 + emulocke::kCfruBoxMonSize, servine.data(), servine.size());
    std::memcpy(blocks.storage.data() + 4 + 2 * emulocke::kCfruBoxMonSize, floette.data(), floette.size());

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
    REQUIRE(snap.boxes.boxes[0].mons[2].species == 847);
    REQUIRE(std::string(snap.boxes.boxes[0].mons[2].speciesName) == "FLOETTE");

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

    emulocke::DecryptedMon pidgey = cfruMon(16, "PIDGEY");
    pidgey.metLocation = 2;
    packCfru(sealeo, pidgey);
    std::memcpy(blocks.storage.data() + 4, sealeo.data(), sealeo.size());
    emulocke::GameSnapshot met;
    met.adapterId = "firered-us-1.1";
    blocks.fileSignature = emulocke::kUnboundSignature210;
    emulocke::fillSnapshotFromFrlg(blocks, met);
    REQUIRE(met.boxes.boxes[0].mons[0].species == 16);
    REQUIRE(met.boxes.boxes[0].mons[0].metLocation == 2);

    emulocke::FrlgSaveBlocks names;
    std::array<uint8_t, emulocke::kCfruBoxMonSize> namedSealeo{};
    packCfru(namedSealeo, cfruMon(342, "SEALEO"));
    std::memcpy(names.storage.data() + 4, namedSealeo.data(), namedSealeo.size());
    for (int b = 0; b < emulocke::kCfruBoxCount; ++b) {
        const std::size_t off = b < 14 ? emulocke::kFrlgBoxNameOff + static_cast<std::size_t>(b) * 9
                                       : emulocke::kFrlgBoxNameOff - static_cast<std::size_t>(b - 13) * 9;
        char label[8];
        std::snprintf(label, sizeof label, "BOX %d", b + 1);
        emulocke::encodeGen3Text(label, {names.storage.data() + off, 9});
    }
    std::memset(names.flash30.data(), 0xFF, names.flash30.size());
    std::memset(names.flash31.data(), 0xFF, names.flash31.size());
    emulocke::encodeGen3Text("BOX 25", {names.block2.data() + emulocke::kCfruBox25Off, 9});
    emulocke::encodeGen3Text("BOX 20", {names.flash30.data() + emulocke::kCfruFlash30BoxOff, 9});
    names.fileSignature = emulocke::kUnboundSignature210;
    emulocke::GameSnapshot titled;
    emulocke::fillSnapshotFromFrlg(names, titled);
    REQUIRE(std::string(titled.boxes.boxes[0].name) == "BOX 1");
    REQUIRE(boxedCount(titled) == 1);
    REQUIRE(!namedBoxMon(titled));
    emulocke::DecryptedMon fromName;
    REQUIRE(!emulocke::decodeCfruBoxMon({names.storage.data() + emulocke::kFrlgBoxNameOff, emulocke::kCfruBoxMonSize},
                                        fromName));
}
