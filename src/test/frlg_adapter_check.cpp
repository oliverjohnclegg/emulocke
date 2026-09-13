#include "adapter/Cartridge.hpp"
#include "adapter/GameAdapter.hpp"
#include "adapter/LiveMemory.hpp"
#include "adapter/frlg/FrlgLayout.hpp"
#include "adapter/frlg/FrlgSave.hpp"
#include "adapter/gen3/BoxCrypt.hpp"
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

void storePlainParty(std::array<uint8_t, emulocke::kPartyMonSize>& raw) {
    uint8_t data[48];
    std::memcpy(data, raw.data() + 0x20, 48);
    const uint32_t pid = emulocke::load32(raw.data());
    const uint32_t ot = emulocke::load32(raw.data() + 4);
    emulocke::xorBoxData(data, pid, ot);
    uint8_t g[12], a[12], e[12], m[12];
    emulocke::unshuffleBoxData(data, pid, g, a, e, m);
    std::memcpy(raw.data() + 0x20, g, 12);
    std::memcpy(raw.data() + 0x2C, a, 12);
    std::memcpy(raw.data() + 0x38, e, 12);
    std::memcpy(raw.data() + 0x44, m, 12);
    emulocke::store16(raw.data() + 0x1C, 0);
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
    blocks.block1[emulocke::kFrlgBadgeByteOff] = 0x01;

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
    REQUIRE(snap.progress.starterSpecies == 1);
    REQUIRE(snap.gyms.slots == 8);
    REQUIRE(snap.gyms.earned == 1);

    const emulocke::SpeciesRef pika = fr->species(25);
    REQUIRE(pika.national == 25);
    REQUIRE(std::string(pika.slug) == "pikachu");
    REQUIRE(std::string(pika.name) == "Pikachu");
    const emulocke::SpeciesRef mime = fr->species(122);
    REQUIRE(std::string(mime.slug) == "mr-mime");
    REQUIRE(std::string(mime.name) == "Mr. Mime");

    const uint16_t badge1 = emulocke::kFrlgFlagBadge1;
    blocks.block1[emulocke::kFrlgFlagsOff + badge1 / 8] =
        static_cast<uint8_t>(1u << (badge1 % 8));
    const std::vector<uint8_t> savBadge = emulocke::writeFrlgSave(blocks);
    const emulocke::GameSnapshot badged = fromSave->readSave(savBadge);
    REQUIRE((badged.progress.badges & 1u) != 0);

    std::vector<uint8_t> ewram(0x40000, 0);
    ewram[emulocke::kFrlgPartyCount - 0x02000000] = 1;
    std::memcpy(ewram.data() + (emulocke::kFrlgParty - 0x02000000), party.data(), party.size());
    std::memcpy(ewram.data() + (emulocke::kFrlgSaveBlock2 - 0x02000000), blocks.block2.data(), blocks.block2.size());
    std::memcpy(ewram.data() + (emulocke::kFrlgSaveBlock1 - 0x02000000), blocks.block1.data(),
                blocks.block1.size());
    std::memcpy(ewram.data() + (emulocke::kFrlgStorage - 0x02000000), blocks.storage.data(),
                blocks.storage.size());
    emulocke::SpanMemory mem(0x02000000, ewram);
    const emulocke::GameSnapshot live = fr->readLive(mem);
    REQUIRE(live.ok);
    REQUIRE(live.party.mons[0].species == 1);
    REQUIRE(std::string(live.trainer.name) == "RED");
    REQUIRE(std::string(live.overworld.mapName) == "PALLET TOWN");
    REQUIRE(live.boxes.boxes[0].mons[0].species == 4);
    REQUIRE(live.progress.starterSpecies == 1);
    REQUIRE(live.gyms.slots == 8);
    REQUIRE(live.gyms.earned == 1);

    std::array<uint8_t, emulocke::kPartyMonSize> plainParty = party;
    storePlainParty(plainParty);
    emulocke::FrlgSaveBlocks hack = blocks;
    std::memcpy(hack.block1.data() + emulocke::kFrlgPartyOff, plainParty.data(), plainParty.size());
    const uint32_t sigs[] = {0x08012025u, 0x01121999u};
    for (uint32_t sig : sigs) {
        std::vector<uint8_t> hackSav = emulocke::writeFrlgSave(hack);
        for (int i = 0; i < 14; ++i) {
            uint8_t* sec = hackSav.data() + static_cast<std::size_t>(i) * 0x1000;
            emulocke::store16(sec + 0xFF6, static_cast<uint16_t>(emulocke::load16(sec + 0xFF6) + 1));
            emulocke::store32(sec + 0xFF8, sig);
        }
        const emulocke::GameAdapter* hackAdapter = emulocke::adapterForSave(hackSav);
        REQUIRE(hackAdapter != nullptr);
        const emulocke::GameSnapshot hackSnap = hackAdapter->readSave(hackSav);
        REQUIRE(hackSnap.ok);
        REQUIRE(hackSnap.party.count == 1);
        REQUIRE(hackSnap.party.mons[0].species == 1);
        REQUIRE(hackSnap.party.mons[0].level == 5);
    }
}