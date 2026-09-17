#include "adapter/gen5/Pokeparam.hpp"

#include "adapter/gen3/Codec.hpp"

namespace emulocke {
namespace {

bool takeAdj(uint16_t v, uint16_t maxHp, uint16_t seedHp, uint16_t& hp, bool& got) {
    if (v > maxHp || (v == 0 && seedHp > 0)) {
        return false;
    }
    if (!got || (v < maxHp && hp == maxHp) || (v < hp && v > 0)) {
        hp = v;
        got = true;
    }
    return true;
}

bool isStat(uint16_t v, uint16_t atk, uint16_t def) {
    return (atk != 0 && v == atk) || (def != 0 && v == def);
}

void takeNext(std::span<const uint8_t> raw, std::size_t off, uint16_t maxHp, uint16_t seedHp,
    uint16_t atk, uint16_t def, uint16_t& hp, bool& got, bool allowZero) {
    const bool hasNext = raw.size() - off >= 4;
    const bool hasPrev = off >= 2;
    if (hasNext) {
        const uint16_t nxt = load16(raw.data() + off + 2);
        if (isStat(nxt, atk, def) && off != 4) {
            if (hasPrev) {
                const uint16_t prev = load16(raw.data() + off - 2);
                if (prev == 0 && allowZero) {
                    hp = 0;
                    got = true;
                } else {
                    takeAdj(prev, maxHp, seedHp, hp, got);
                }
            }
            return;
        }
        if (nxt == 0) {
            if (allowZero) {
                hp = 0;
                got = true;
            }
            return;
        }
        takeAdj(nxt, maxHp, seedHp, hp, got);
    }
    if (!got && hasPrev) {
        takeAdj(load16(raw.data() + off - 2), maxHp, seedHp, hp, got);
    }
}

bool takePin(std::span<const uint8_t> raw, std::size_t off, uint16_t maxHp, uint16_t seedHp,
    uint16_t atk, uint16_t def, uint16_t& hp, bool& got) {
    if (raw.size() - off >= 6 && off >= 2 && load16(raw.data() + off + 2) == atk &&
        load16(raw.data() + off + 4) == def) {
        const uint16_t cur = load16(raw.data() + off - 2);
        if (cur == 0) {
            hp = 0;
            got = true;
            return true;
        }
        takeAdj(cur, maxHp, seedHp, hp, got);
        return true;
    }
    if (raw.size() - off >= 8 && load16(raw.data() + off + 4) == atk &&
        load16(raw.data() + off + 6) == def) {
        const uint16_t cur = load16(raw.data() + off + 2);
        if (cur == 0) {
            hp = 0;
            got = true;
            return true;
        }
        takeAdj(cur, maxHp, seedHp, hp, got);
        return true;
    }
    return false;
}

}  // namespace

bool readBtlHp(std::span<const uint8_t> raw, uint16_t maxHp, uint16_t seedHp, uint16_t& hp,
    uint16_t atk, uint16_t def) {
    if (maxHp == 0 || raw.size() < 4) {
        return false;
    }
    bool got = false;
    const bool pin = atk != 0 && def != 0;
    bool first = true;
    for (std::size_t off = 0; off + 2 < raw.size(); off += 2) {
        if (load16(raw.data() + off) != maxHp) {
            continue;
        }
        if (pin && takePin(raw, off, maxHp, seedHp, atk, def, hp, got)) {
            if (hp == 0) {
                return true;
            }
            first = false;
            continue;
        }
        takeNext(raw, off, maxHp, seedHp, atk, def, hp, got, first && off <= 6);
        if (got && hp == 0) {
            return true;
        }
        first = false;
    }
    if (got) {
        return true;
    }
    for (std::size_t off = 0; off + 8 <= raw.size(); off += 4) {
        if (load32(raw.data() + off) != maxHp) {
            continue;
        }
        const uint32_t after = load32(raw.data() + off + 4);
        if (after <= 999) {
            takeAdj(static_cast<uint16_t>(after), maxHp, seedHp, hp, got);
        }
    }
    return got;
}

bool readBtlCoreHp(std::span<const uint8_t> raw, uint16_t species, uint16_t& hp, uint16_t atk,
    uint16_t def) {
    if (raw.size() < 8 || load16(raw.data()) != species) {
        return false;
    }
    const uint16_t a = load16(raw.data() + 2);
    const uint16_t b = load16(raw.data() + 4);
    const uint16_t c = load16(raw.data() + 6);
    uint16_t mx = 0;
    uint16_t cur = 0;
    const bool live = c == 0 && a >= 1 && a <= 999 && b <= a;
    if (live) {
        mx = a;
        cur = b;
    } else if (a <= 31) {
        mx = b;
        cur = c;
    } else {
        return false;
    }
    if (mx < 1 || mx > 999 || cur > mx) {
        return false;
    }
    if (!live && raw.size() >= 10 && atk != 0 && def != 0 && cur == atk &&
        load16(raw.data() + 8) == def) {
        return false;
    }
    hp = cur;
    return true;
}

bool readBtlLiveHp(std::span<const uint8_t> raw, uint16_t species, uint16_t maxHp, uint16_t seedHp,
    uint16_t& hp, uint16_t atk, uint16_t def) {
    uint16_t cur = 0;
    if (readBtlCoreHp(raw, species, cur, atk, def)) {
        if (cur > 0) {
            hp = cur;
            return true;
        }
        if (raw.size() >= 8 && load16(raw.data() + 6) == 0 && load16(raw.data() + 2) >= 1 &&
            load16(raw.data() + 4) == 0) {
            hp = 0;
            return true;
        }
        if (raw.size() < 15) {
            return false;
        }
        int six = 0;
        for (int j = 0; j < 7; ++j) {
            if (raw[static_cast<std::size_t>(8 + j)] > 12) {
                return false;
            }
            six += raw[static_cast<std::size_t>(8 + j)] == 6 ? 1 : 0;
        }
        if (six < 5) {
            return false;
        }
        hp = 0;
        return true;
    }
    if (raw.size() < 4 || load16(raw.data() + 2) > 31) {
        return false;
    }
    if (!readBtlHp(raw, maxHp, seedHp, cur, atk, def) || cur == 0) {
        return false;
    }
    hp = cur;
    return true;
}

bool considerBtl(BattleBattler& best, bool& got, uint16_t, uint16_t species, uint16_t hp,
    uint16_t maxHp) {
    auto assign = [&] {
        best = {};
        best.species = species;
        best.hp = hp;
        best.maxHp = maxHp;
        got = true;
    };
    if (!got) {
        assign();
        return true;
    }
    if (best.species == species) {
        if (hp == 0 || (best.hp != 0 && hp < best.hp && hp > 0)) {
            assign();
            return true;
        }
        return false;
    }
    if (best.hp == 0 && hp > 0) {
        assign();
        return true;
    }
    if (hp == 0 || hp >= best.hp) {
        return false;
    }
    assign();
    return true;
}

}
