#include "adapter/gen45/NdsBattle.hpp"

#include "adapter/gen3/Codec.hpp"

#include <array>

namespace emulocke {
namespace {

bool maxHpOk(const BattleBattler& b, uint16_t expect) {
    return expect == 0 || b.maxHp == expect;
}

}  // namespace

void overlayNdsBattleMons(const LiveMemory& mem, uint32_t from, uint32_t to, GameSnapshot& snap) {
    if (from < kNdsRam) {
        from = kNdsRam;
    }
    if (to > kNdsRam + kNdsRamBytes) {
        to = kNdsRam + kNdsRamBytes;
    }
    if (to < from || to - from < kNdsBattleMonSize * 2) {
        return;
    }
    const uint16_t playerSp = snap.battle.player.species;
    const uint16_t foeSp = snap.battle.foe.species;
    const uint16_t playerMax = snap.battle.player.maxHp;
    const uint16_t foeMax = snap.battle.foe.maxHp;
    BattleBattler bestP{};
    BattleBattler bestF{};
    BattleBattler loneP{};
    BattleBattler loneF{};
    int bestSum = 0x7fffffff;
    int lonePHp = 0x7fffffff;
    int loneFHp = 0x7fffffff;
    bool found = false;
    bool gotP = false;
    bool gotF = false;
    static constexpr uint32_t kStride[] = {0xC0, 0x14C};
    static constexpr uint32_t kChunk = 0x1000;
    static constexpr uint32_t kSpan = 0x14C + static_cast<uint32_t>(kNdsBattleMonSize);
    std::array<uint8_t, kChunk> chunk{};
    for (uint32_t addr = from; addr < to; addr += kChunk - kSpan) {
        const uint32_t n = addr + kChunk > to ? to - addr : kChunk;
        if (n < kNdsBattleMonSize || !mem.read(addr, {chunk.data(), n})) {
            continue;
        }
        for (uint32_t i = 0; i + kNdsBattleMonSize <= n; i += 4) {
            const uint16_t sp = load16(chunk.data() + i);
            if (sp != playerSp && sp != foeSp) {
                continue;
            }
            BattleBattler one;
            if (readNdsBattleMon({chunk.data() + i, kNdsBattleMonSize}, one)) {
                if (one.species == playerSp && maxHpOk(one, playerMax) &&
                    (!gotP || static_cast<int>(one.hp) < lonePHp)) {
                    loneP = one;
                    lonePHp = one.hp;
                    gotP = true;
                }
                if (one.species == foeSp && maxHpOk(one, foeMax) &&
                    (!gotF || static_cast<int>(one.hp) < loneFHp)) {
                    loneF = one;
                    loneFHp = one.hp;
                    gotF = true;
                }
            }
            if (sp != playerSp) {
                continue;
            }
            for (uint32_t stride : kStride) {
                if (i + stride + kNdsBattleMonSize > n) {
                    continue;
                }
                BattleBattler p;
                BattleBattler f;
                if (!readNdsBattleMon({chunk.data() + i, kNdsBattleMonSize}, p) ||
                    !readNdsBattleMon({chunk.data() + i + stride, kNdsBattleMonSize}, f)) {
                    continue;
                }
                if (p.species != playerSp || f.species != foeSp || !maxHpOk(p, playerMax) ||
                    !maxHpOk(f, foeMax)) {
                    continue;
                }
                const int sum = static_cast<int>(p.hp) + static_cast<int>(f.hp);
                if (!found || sum < bestSum) {
                    bestP = p;
                    bestF = f;
                    bestSum = sum;
                    found = true;
                }
            }
        }
    }
    if (!found && (gotP || gotF)) {
        bestP = loneP;
        bestF = loneF;
        found = true;
    }
    if (!found) {
        return;
    }
    const uint8_t pIdx = snap.battle.player.partyIndex;
    const uint8_t fIdx = snap.battle.foe.partyIndex;
    snap.battle.player = bestP;
    snap.battle.player.partyIndex = pIdx;
    snap.battle.foe = bestF;
    snap.battle.foe.partyIndex = fIdx;
    if (fIdx < 6) {
        snap.battle.foeHp[fIdx] = bestF.hp;
        snap.battle.foeMaxHp[fIdx] = bestF.maxHp;
    }
}

}
