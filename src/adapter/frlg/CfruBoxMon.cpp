#include "adapter/frlg/CfruBoxes.hpp"

#include "adapter/frlg/FrlgLayout.hpp"
#include "adapter/gen3/BoxFields.hpp"
#include "adapter/gen3/Codec.hpp"

namespace emulocke {
namespace {

bool packedSlot(const uint8_t* p) {
    const uint16_t species = load16(p + 28);
    if (species == 0 || species > 4095) {
        return false;
    }
    if (p[18] > 7) {
        return false;
    }
    return load32(p + 32) <= 1640000u;
}

}  // namespace

bool decodeCfruBoxMon(std::span<const uint8_t> raw, DecryptedMon& out) {
    if (raw.size() < kCfruBoxMonSize) {
        return false;
    }
    out = DecryptedMon{};
    pullHeader(raw.data(), out);
    out.species = load16(raw.data() + 28);
    if (out.species == 0) {
        return false;
    }
    out.heldItem = load16(raw.data() + 30);
    out.experience = load32(raw.data() + 32);
    out.ball = raw[38];
    const uint64_t moves = load32(raw.data() + 39) | (static_cast<uint64_t>(raw[43]) << 32);
    for (int i = 0; i < 4; ++i) {
        out.moves[i] = static_cast<uint16_t>((moves >> (10 * i)) & 0x3FFu);
    }
    out.evHp = raw[44];
    out.evAtk = raw[45];
    out.evDef = raw[46];
    out.evSpe = raw[47];
    out.evSpa = raw[48];
    out.evSpd = raw[49];
    pullMisc(raw.data() + 50, out);
    out.ball = raw[38];
    out.egg = out.egg || ((raw[19] & 4) != 0);
    out.checksumOk = true;
    return true;
}

bool cfruPackedMon(std::span<const uint8_t> raw) {
    if (raw.size() < kCfruBoxMonSize) {
        return false;
    }
    return packedSlot(raw.data());
}

bool cfruPackedStorage(std::span<const uint8_t> storage) {
    const std::size_t packedBytes = 4 + static_cast<std::size_t>(kCfruPackedBoxes) * kCfruBoxBytes;
    if (storage.size() < packedBytes || storage.size() < kFrlgStorageSize) {
        return false;
    }
    int vanilla = 0;
    int packed = 0;
    for (int i = 0; i < 14 * 30; ++i) {
        DecryptedMon dec;
        const uint8_t* raw = storage.data() + kFrlgBoxStart + static_cast<std::size_t>(i) * kBoxMonSize;
        if (decryptBoxMon({raw, kBoxMonSize}, dec)) {
            ++vanilla;
        }
    }
    for (int i = 0; i < kCfruPackedBoxes * 30; ++i) {
        if (packedSlot(storage.data() + 4 + static_cast<std::size_t>(i) * kCfruBoxMonSize)) {
            ++packed;
        }
    }
    if (packed > vanilla) {
        return true;
    }
    if (packed == 0 || packed != vanilla) {
        return false;
    }
    DecryptedMon asVanilla;
    DecryptedMon asPacked;
    const uint8_t* first = storage.data() + 4;
    return decryptBoxMon({first, kBoxMonSize}, asVanilla) && decodeCfruBoxMon({first, kCfruBoxMonSize}, asPacked) &&
           asVanilla.species != asPacked.species;
}

}
