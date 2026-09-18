#include "adapter/gen5/Pokeparam.hpp"

#include "adapter/gen3/Codec.hpp"

namespace emulocke {
namespace {

bool takeHp(uint16_t species, uint16_t hp, uint16_t maxHp, uint16_t expect, BattleBattler& out) {
    if (maxHp == 0 || maxHp > 999 || hp > maxHp) {
        return false;
    }
    if (expect != 0 && maxHp != expect) {
        return false;
    }
    out = {};
    out.species = species;
    out.hp = hp;
    out.maxHp = maxHp;
    return true;
}

}  // namespace

bool readBtlRanks(std::span<const uint8_t> raw, std::size_t at, int8_t stages[8]) {
    if (!stages || raw.size() < 7 || at > raw.size() - 7) {
        return false;
    }
    uint8_t v[7];
    bool any = false;
    for (int j = 0; j < 7; ++j) {
        v[j] = raw[at + static_cast<std::size_t>(j)];
        if (v[j] > 12) {
            return false;
        }
        any = any || v[j] != 0;
    }
    if (!any) {
        return false;
    }
    stages[1] = static_cast<int8_t>(v[0] - 6);
    stages[2] = static_cast<int8_t>(v[1] - 6);
    stages[4] = static_cast<int8_t>(v[2] - 6);
    stages[5] = static_cast<int8_t>(v[3] - 6);
    stages[3] = static_cast<int8_t>(v[4] - 6);
    stages[6] = static_cast<int8_t>(v[5] - 6);
    stages[7] = static_cast<int8_t>(v[6] - 6);
    return true;
}

bool readBtlPokeparam(std::span<const uint8_t> raw, uint16_t species, uint16_t maxHp,
    BattleBattler& out, uint16_t level) {
    if (raw.size() < 8 || load16(raw.data()) != species || load16(raw.data() + 2) > 31) {
        return false;
    }
    if (level != 0 && raw.size() >= 15) {
        const uint8_t got = raw[14];
        if (got >= 1 && got <= 100 && got != level) {
            return false;
        }
    }
    const uint16_t a = load16(raw.data() + 4);
    const uint16_t b = load16(raw.data() + 6);
    if (!takeHp(species, b, a, maxHp, out) && !takeHp(species, a, b, maxHp, out)) {
        return false;
    }
    readBtlRanks(raw, 8, out.stages);
    return true;
}

}
