#include "test/snapshot_fixtures.hpp"

#include "adapter/frlg/FrlgLayout.hpp"
#include "adapter/frlg/FrlgSave.hpp"
#include "adapter/gen3/BoxMon.hpp"
#include "adapter/gen3/Codec.hpp"
#include "adapter/gen4/Layout.hpp"
#include "adapter/gen45/Pk.hpp"
#include "adapter/gen5/Save.hpp"
#include "adapter/rse/RseLayout.hpp"
#include "adapter/rse/RseSave.hpp"

#include <array>
#include <cstring>
#include <vector>

namespace {

emulocke::DecryptedMon gen3Mon() {
    emulocke::DecryptedMon mon;
    mon.personality = 0x11111111;
    mon.otId = 0x22223333;
    mon.species = 1;
    mon.level = 5;
    mon.hp = 18;
    mon.maxHp = 20;
    mon.language = 2;
    std::strcpy(mon.nickname, "BULBASAUR");
    std::strcpy(mon.otName, "RED");
    return mon;
}

std::array<uint8_t, emulocke::kPk4PartySize> pk4() {
    std::array<uint8_t, emulocke::kPk4PartySize> plain{};
    emulocke::store32(plain.data(), 0x12345678);
    emulocke::store16(plain.data() + 8, 25);
    emulocke::store32(plain.data() + 0x0C, 12345);
    emulocke::encodeGen4Text("PIKACHU", {plain.data() + 0x48, 22});
    emulocke::encodeGen4Text("RED", {plain.data() + 0x68, 16});
    plain[0x8C] = 5;
    emulocke::store16(plain.data() + 0x8E, 20);
    emulocke::store16(plain.data() + 0x90, 20);
    std::array<uint8_t, emulocke::kPk4PartySize> out{};
    emulocke::encryptPk45(plain, out);
    return out;
}

std::array<uint8_t, emulocke::kPk5PartySize> pk5() {
    std::array<uint8_t, emulocke::kPk5PartySize> plain{};
    emulocke::store32(plain.data(), 0x12345678);
    emulocke::store16(plain.data() + 8, 25);
    emulocke::encodeUtf16Text("PIKACHU", {plain.data() + 0x48, 22});
    emulocke::encodeUtf16Text("RED", {plain.data() + 0x68, 16});
    plain[0x8C] = 5;
    emulocke::store16(plain.data() + 0x8E, 20);
    emulocke::store16(plain.data() + 0x90, 20);
    std::array<uint8_t, emulocke::kPk5PartySize> out{};
    emulocke::encryptPk45(plain, out);
    return out;
}

std::vector<uint8_t> gen4Sav(const emulocke::Gen4Layout& layout) {
    std::vector<uint8_t> sav(0x80000, 0);
    emulocke::encodeGen4Text("RED", {sav.data() + layout.trainerOff, 16});
    emulocke::store32(sav.data() + layout.trainerOff + 0x10, 12345);
    sav[layout.partyOff - 4] = 1;
    const auto pk = pk4();
    std::memcpy(sav.data() + layout.partyOff, pk.data(), pk.size());
    const std::size_t box0 = layout.storageStart + (layout.paddedBoxes ? 0 : 4);
    std::memcpy(sav.data() + box0, pk.data(), emulocke::kPkStoredSize);
    if (layout.mapOff != 0) {
        emulocke::store16(sav.data() + layout.mapOff, 201);
    }
    if (layout.eventFlagOff != 0) {
        sav[layout.eventFlagOff] = 1;
    }
    sav[layout.trainerOff + 0x1A] = 1;
    const std::size_t fo = layout.generalSize - layout.footerSize;
    if (layout.footerSize == 0x10) {
        emulocke::store32(sav.data() + fo, 1);
        emulocke::store32(sav.data() + fo + 8, emulocke::kGen4Magic);
    } else {
        emulocke::store32(sav.data() + fo + 4, 1);
        emulocke::store32(sav.data() + fo + 8, static_cast<uint32_t>(layout.generalSize));
        emulocke::store32(sav.data() + fo + 12, emulocke::kGen4Magic);
    }
    return sav;
}

}  // namespace

std::vector<uint8_t> makeSuiteSav(SuiteSav kind) {
    if (kind == SuiteSav::Frlg) {
        emulocke::FrlgSaveBlocks blocks;
        emulocke::encodeGen3Text("RED", {blocks.block2.data(), 8});
        emulocke::store32(blocks.block2.data() + 0x0A, 0x12345678);
        blocks.block1[emulocke::kFrlgPartyCountOff] = 1;
        std::array<uint8_t, emulocke::kPartyMonSize> party{};
        emulocke::encryptPartyMon(gen3Mon(), party);
        std::memcpy(blocks.block1.data() + emulocke::kFrlgPartyOff, party.data(), party.size());
        blocks.block1[emulocke::kFrlgMapGroupOff] = 3;
        blocks.block1[emulocke::kFrlgMapNumOff] = 0;
        emulocke::DecryptedMon boxed = gen3Mon();
        boxed.species = 4;
        std::array<uint8_t, emulocke::kBoxMonSize> box{};
        emulocke::encryptBoxMon(boxed, box);
        std::memcpy(blocks.storage.data() + emulocke::kFrlgBoxStart, box.data(), box.size());
        emulocke::encodeGen3Text("BOX 1", {blocks.storage.data() + emulocke::kFrlgBoxNameOff, 9});
        blocks.block1[emulocke::kFrlgFlagsOff] = 1;
        return emulocke::writeFrlgSave(blocks);
    }
    if (kind == SuiteSav::Rse) {
        emulocke::RseSaveBlocks blocks;
        emulocke::encodeGen3Text("RED", {blocks.block2.data(), 8});
        emulocke::store32(blocks.block2.data() + 0x0A, 0x12345678);
        blocks.block1[emulocke::kRsePartyCountOff] = 1;
        std::array<uint8_t, emulocke::kPartyMonSize> party{};
        emulocke::encryptPartyMon(gen3Mon(), party);
        std::memcpy(blocks.block1.data() + emulocke::kRsePartyOff, party.data(), party.size());
        blocks.block1[emulocke::kRseMapGroupOff] = 0;
        blocks.block1[emulocke::kRseMapNumOff] = 9;
        emulocke::DecryptedMon boxed = gen3Mon();
        boxed.species = 4;
        std::array<uint8_t, emulocke::kBoxMonSize> box{};
        emulocke::encryptBoxMon(boxed, box);
        std::memcpy(blocks.storage.data() + emulocke::kRseBoxStart, box.data(), box.size());
        emulocke::encodeGen3Text("BOX 1", {blocks.storage.data() + emulocke::kRseBoxNameOff, 9});
        blocks.block1[emulocke::kRseFlagsOffRs] = 1;
        blocks.block1[emulocke::kRseFlagsOffEm] = 1;
        return emulocke::writeRseSave(blocks);
    }
    if (kind == SuiteSav::Dp) {
        return gen4Sav(emulocke::dpLayout());
    }
    if (kind == SuiteSav::Pt) {
        return gen4Sav(emulocke::ptLayout());
    }
    if (kind == SuiteSav::Hgss) {
        return gen4Sav(emulocke::hgssLayout());
    }
    std::vector<uint8_t> sav(0x80000, 0);
    sav[emulocke::kGen5Party + 4] = 1;
    const auto pk = pk5();
    std::memcpy(sav.data() + emulocke::kGen5Party + 8, pk.data(), pk.size());
    std::memcpy(sav.data() + emulocke::kGen5Box, pk.data(), emulocke::kPkStoredSize);
    emulocke::encodeUtf16Text("RED", {sav.data() + emulocke::kGen5Trainer + 4, 16});
    emulocke::store32(sav.data() + emulocke::kGen5Trainer + 0x14, 12345);
    sav[emulocke::kGen5Trainer + 0x1F] = emulocke::kVersionBlack;
    emulocke::store16(sav.data() + emulocke::kGen5Position, 14);
    sav[emulocke::kBwEventWork + emulocke::kBwFlagStart] = 1;
    sav[emulocke::kBw2EventWork + emulocke::kBw2FlagStart] = 1;
    sav[emulocke::kBwBadgeOff] = 1;
    sav[emulocke::kBw2BadgeOff] = 1;
    return sav;
}
