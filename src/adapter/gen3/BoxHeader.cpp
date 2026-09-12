#include "adapter/gen3/BoxFields.hpp"

#include "adapter/gen3/Codec.hpp"

namespace emulocke {

void pullHeader(const uint8_t* raw, DecryptedMon& o) {
    o.personality = load32(raw);
    o.otId = load32(raw + 4);
    decodeGen3Text({raw + 8, 10}, o.nickname, sizeof(o.nickname));
    o.language = raw[0x12];
    decodeGen3Text({raw + 0x14, 7}, o.otName, sizeof(o.otName));
}

void pushHeader(uint8_t* raw, const DecryptedMon& o) {
    store32(raw, o.personality);
    store32(raw + 4, o.otId);
    encodeGen3Text(o.nickname, {raw + 8, 10});
    raw[0x12] = o.language ? o.language : 2;
    raw[0x13] = o.species ? 0x02 : 0;
    encodeGen3Text(o.otName, {raw + 0x14, 7});
    raw[0x1B] = 0;
}

void pullPartyTail(const uint8_t* tail, DecryptedMon& o) {
    o.status = load32(tail);
    o.level = tail[4];
    o.hp = load16(tail + 6);
    o.maxHp = load16(tail + 8);
    o.attack = load16(tail + 10);
    o.defense = load16(tail + 12);
    o.speed = load16(tail + 14);
    o.spAttack = load16(tail + 16);
    o.spDefense = load16(tail + 18);
}

void pushPartyTail(uint8_t* tail, const DecryptedMon& o) {
    store32(tail, o.status);
    tail[4] = o.level;
    tail[5] = 0;
    store16(tail + 6, o.hp);
    store16(tail + 8, o.maxHp);
    store16(tail + 10, o.attack);
    store16(tail + 12, o.defense);
    store16(tail + 14, o.speed);
    store16(tail + 16, o.spAttack);
    store16(tail + 18, o.spDefense);
}

}