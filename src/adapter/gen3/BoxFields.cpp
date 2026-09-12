#include "adapter/gen3/BoxFields.hpp"

#include "adapter/gen3/Codec.hpp"

#include <cstring>

namespace emulocke {

void pullGrowth(const uint8_t* g, DecryptedMon& o) {
    o.species = load16(g);
    o.heldItem = load16(g + 2);
    o.experience = load32(g + 4);
}

void pushGrowth(uint8_t* g, const DecryptedMon& o) {
    std::memset(g, 0, 12);
    store16(g, o.species);
    store16(g + 2, o.heldItem);
    store32(g + 4, o.experience);
}

void pullAttacks(const uint8_t* a, DecryptedMon& o) {
    for (int i = 0; i < 4; ++i) {
        o.moves[i] = load16(a + i * 2);
        o.pp[i] = a[8 + i];
    }
}

void pushAttacks(uint8_t* a, const DecryptedMon& o) {
    std::memset(a, 0, 12);
    for (int i = 0; i < 4; ++i) {
        store16(a + i * 2, o.moves[i]);
        a[8 + i] = o.pp[i];
    }
}

void pullEvs(const uint8_t* e, DecryptedMon& o) {
    o.evHp = e[0];
    o.evAtk = e[1];
    o.evDef = e[2];
    o.evSpe = e[3];
    o.evSpa = e[4];
    o.evSpd = e[5];
}

void pushEvs(uint8_t* e, const DecryptedMon& o) {
    std::memset(e, 0, 12);
    e[0] = o.evHp;
    e[1] = o.evAtk;
    e[2] = o.evDef;
    e[3] = o.evSpe;
    e[4] = o.evSpa;
    e[5] = o.evSpd;
}

void pullMisc(const uint8_t* m, DecryptedMon& o) {
    o.pokerus = m[0];
    o.metLocation = m[1];
    const uint16_t packed = load16(m + 2);
    o.metLevel = packed & 0x7F;
    o.metGame = static_cast<uint8_t>((packed >> 7) & 0x0F);
    o.ball = static_cast<uint8_t>((packed >> 11) & 0x0F);
    o.otGender = static_cast<uint8_t>((packed >> 15) & 1);
    const uint32_t iv = load32(m + 4);
    o.ivHp = iv & 0x1F;
    o.ivAtk = (iv >> 5) & 0x1F;
    o.ivDef = (iv >> 10) & 0x1F;
    o.ivSpe = (iv >> 15) & 0x1F;
    o.ivSpa = (iv >> 20) & 0x1F;
    o.ivSpd = (iv >> 25) & 0x1F;
    o.egg = ((iv >> 30) & 1) != 0;
    o.abilityNum = static_cast<uint8_t>((iv >> 31) & 1);
}

void pushMisc(uint8_t* m, const DecryptedMon& o) {
    std::memset(m, 0, 12);
    m[0] = o.pokerus;
    m[1] = o.metLocation;
    store16(m + 2, static_cast<uint16_t>((o.metLevel & 0x7F) | ((o.metGame & 0x0F) << 7) |
                                        ((o.ball & 0x0F) << 11) | ((o.otGender & 1) << 15)));
    uint32_t iv = o.ivHp & 0x1F;
    iv |= static_cast<uint32_t>(o.ivAtk & 0x1F) << 5;
    iv |= static_cast<uint32_t>(o.ivDef & 0x1F) << 10;
    iv |= static_cast<uint32_t>(o.ivSpe & 0x1F) << 15;
    iv |= static_cast<uint32_t>(o.ivSpa & 0x1F) << 20;
    iv |= static_cast<uint32_t>(o.ivSpd & 0x1F) << 25;
    iv |= static_cast<uint32_t>(o.egg ? 1u : 0u) << 30;
    iv |= static_cast<uint32_t>(o.abilityNum & 1u) << 31;
    store32(m + 4, iv);
}

}