#include "adapter/gen45/Pk.hpp"

#include "adapter/gen3/Codec.hpp"
#include "adapter/gen45/Names.hpp"

#include <array>
#include <cstdio>
#include <cstring>

namespace emulocke {

bool parsePk45(std::span<const uint8_t> raw, bool utf16Names, Mon& out) {
    if (raw.size() < kPkStoredSize) {
        return false;
    }
    std::array<uint8_t, kPk4PartySize> buf{};
    if (!decryptPk45(raw, {buf.data(), raw.size()})) {
        return false;
    }
    const uint16_t species = load16(buf.data() + 8);
    if (species == 0) {
        return false;
    }
    out = Mon{};
    out.personality = load32(buf.data());
    out.species = species;
    out.heldItem = load16(buf.data() + 0x0A);
    out.otId = load32(buf.data() + 0x0C);
    out.experience = static_cast<uint32_t>(buf[0x10] | (buf[0x11] << 8) | (buf[0x12] << 16));
    out.evHp = buf[0x18];
    out.evAtk = buf[0x19];
    out.evDef = buf[0x1A];
    out.evSpe = buf[0x1B];
    out.evSpa = buf[0x1C];
    out.evSpd = buf[0x1D];
    for (int i = 0; i < 4; ++i) {
        out.moves[i] = load16(buf.data() + 0x28 + i * 2);
        out.pp[i] = buf[0x30 + i];
    }
    const uint32_t iv = load32(buf.data() + 0x38);
    out.ivHp = iv & 0x1F;
    out.ivAtk = (iv >> 5) & 0x1F;
    out.ivDef = (iv >> 10) & 0x1F;
    out.ivSpe = (iv >> 15) & 0x1F;
    out.ivSpa = (iv >> 20) & 0x1F;
    out.ivSpd = (iv >> 25) & 0x1F;
    out.egg = ((iv >> 30) & 1) != 0;
    out.abilityNum = buf[0x15];
    out.metGame = buf[0x5F];
    out.metLocation = load16(buf.data() + 0x46);
    out.ball = buf[0x83];
    out.nature = static_cast<uint8_t>(out.personality % 25);
    const uint16_t tid = static_cast<uint16_t>(out.otId);
    const uint16_t sid = static_cast<uint16_t>(out.otId >> 16);
    const uint16_t hid = static_cast<uint16_t>(out.personality >> 16);
    const uint16_t lid = static_cast<uint16_t>(out.personality);
    out.shiny = ((tid ^ sid ^ hid ^ lid) & 0xFFF8) == 0;
    if (raw.size() > 0x8C) {
        out.level = buf[0x8C];
        out.hp = load16(buf.data() + 0x8E);
        out.maxHp = load16(buf.data() + 0x90);
        out.attack = load16(buf.data() + 0x92);
        out.defense = load16(buf.data() + 0x94);
        out.speed = load16(buf.data() + 0x96);
        out.spAttack = load16(buf.data() + 0x98);
        out.spDefense = load16(buf.data() + 0x9A);
        out.status = load32(buf.data() + 0x88);
    }
    if (utf16Names) {
        decodeUtf16Text({buf.data() + 0x48, 22}, out.nickname, sizeof(out.nickname));
        decodeUtf16Text({buf.data() + 0x68, 16}, out.otName, sizeof(out.otName));
    } else {
        decodeGen4Text({buf.data() + 0x48, 22}, out.nickname, sizeof(out.nickname));
        decodeGen4Text({buf.data() + 0x68, 16}, out.otName, sizeof(out.otName));
    }
    std::snprintf(out.speciesName, sizeof(out.speciesName), "%s", nationalSpeciesName(species));
    return true;
}

}
