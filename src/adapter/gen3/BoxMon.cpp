#include "adapter/gen3/BoxMon.hpp"

#include "adapter/gen3/BoxCrypt.hpp"
#include "adapter/gen3/BoxFields.hpp"
#include "adapter/gen3/Codec.hpp"

#include <cstring>

namespace emulocke {

bool decryptBoxMon(std::span<const uint8_t> raw, DecryptedMon& out) {
    if (raw.size() < kBoxMonSize) {
        return false;
    }
    out = DecryptedMon{};
    pullHeader(raw.data(), out);
    uint8_t data[48];
    std::memcpy(data, raw.data() + 0x20, 48);
    xorBoxData(data, out.personality, out.otId);
    out.checksumOk = load16(raw.data() + 0x1C) == boxDataChecksum(data);
    uint8_t g[12], a[12], e[12], m[12];
    unshuffleBoxData(data, out.personality, g, a, e, m);
    pullGrowth(g, out);
    pullAttacks(a, out);
    pullEvs(e, out);
    pullMisc(m, out);
    return out.species != 0 && out.checksumOk;
}

bool encryptBoxMon(const DecryptedMon& in, std::span<uint8_t> raw) {
    if (raw.size() < kBoxMonSize) {
        return false;
    }
    std::memset(raw.data(), 0, kBoxMonSize);
    pushHeader(raw.data(), in);
    uint8_t g[12], a[12], e[12], m[12], data[48];
    pushGrowth(g, in);
    pushAttacks(a, in);
    pushEvs(e, in);
    pushMisc(m, in);
    shuffleBoxData(g, a, e, m, in.personality, data);
    store16(raw.data() + 0x1C, boxDataChecksum(data));
    xorBoxData(data, in.personality, in.otId);
    std::memcpy(raw.data() + 0x20, data, 48);
    return true;
}

bool decryptPartyMon(std::span<const uint8_t> raw, DecryptedMon& out) {
    if (raw.size() < kPartyMonSize) {
        return false;
    }
    decryptBoxMon(raw.first(kBoxMonSize), out);
    pullPartyTail(raw.data() + kBoxMonSize, out);
    return out.species != 0 && out.checksumOk;
}

bool encryptPartyMon(const DecryptedMon& in, std::span<uint8_t> raw) {
    if (raw.size() < kPartyMonSize || !encryptBoxMon(in, raw.first(kBoxMonSize))) {
        return false;
    }
    pushPartyTail(raw.data() + kBoxMonSize, in);
    return true;
}

bool isShiny(uint32_t otId, uint32_t personality) {
    const uint16_t tid = static_cast<uint16_t>(otId);
    const uint16_t sid = static_cast<uint16_t>(otId >> 16);
    const uint16_t hid = static_cast<uint16_t>(personality >> 16);
    const uint16_t lid = static_cast<uint16_t>(personality);
    return (tid ^ sid ^ hid ^ lid) < 8;
}

uint8_t natureOf(uint32_t personality) {
    return static_cast<uint8_t>(personality % 25);
}

}