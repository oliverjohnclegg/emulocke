#include "adapter/gen5/Pokeparam.hpp"

#include "adapter/gen3/Codec.hpp"

namespace emulocke {
namespace {

void tryRanks(std::span<const uint8_t> raw, std::size_t at, BattleBattler& out) {
    if (raw.size() < 7 || at > raw.size() - 7) {
        return;
    }
    int six = 0;
    for (int j = 0; j < 7; ++j) {
        if (raw[at + static_cast<std::size_t>(j)] > 12) {
            return;
        }
        six += raw[at + static_cast<std::size_t>(j)] == 6 ? 1 : 0;
    }
    if (six < 5) {
        return;
    }
    out.stages[1] = static_cast<int8_t>(raw[at] - 6);
    out.stages[2] = static_cast<int8_t>(raw[at + 1] - 6);
    out.stages[4] = static_cast<int8_t>(raw[at + 2] - 6);
    out.stages[5] = static_cast<int8_t>(raw[at + 3] - 6);
    out.stages[3] = static_cast<int8_t>(raw[at + 4] - 6);
    out.stages[6] = static_cast<int8_t>(raw[at + 5] - 6);
    out.stages[7] = static_cast<int8_t>(raw[at + 6] - 6);
}

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
    tryRanks(raw, 8, out);
    return true;
}

}
