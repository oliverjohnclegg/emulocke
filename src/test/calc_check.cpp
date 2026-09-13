#include "calc/Build.hpp"
#include "calc/Calculate.hpp"
#include "calc/Dex.hpp"
#include "calc/HpBar.hpp"
#include "calc/Pack.hpp"
#include "calc/Stats.hpp"
#include "calc/SwitchIn.hpp"
#include "calc/Type.hpp"
#include "run/Catalog.hpp"
#include "test/Check.hpp"

#include <cstdio>

using emulocke::DamageResult;
using emulocke::Field;
using emulocke::Move;
using emulocke::MoveKind;
using emulocke::Pokemon;
using emulocke::Type;

namespace {

void testCometPunch() {
    const emulocke::SpeciesRow* snorlax = emulocke::speciesById(143);
    const emulocke::SpeciesRow* vulpix = emulocke::speciesById(37);
    REQUIRE(snorlax && vulpix);
    emulocke::PackMon s{143, 100, 255, 0, {4, 0, 0, 0}};
    emulocke::PackMon v{37, 100, 255, 0, {0, 0, 0, 0}};
    Pokemon a = emulocke::pokemonFromPack(s);
    Pokemon d = emulocke::pokemonFromPack(v);
    a.atk = emulocke::otherStat(snorlax->atk, 31, 0, 100, 10);
    a.level = 100;
    d.def = emulocke::otherStat(vulpix->def, 31, 0, 100, 10);
    d.hp = emulocke::hpStat(vulpix->hp, 31, 0, 100);
    d.maxHp = d.hp;
    d.t1 = Type::Fire;
    d.t2 = Type::None;
    a.t1 = Type::Normal;
    a.t2 = Type::None;
    const emulocke::MoveRow* row = emulocke::moveById(4);
    REQUIRE(row);
    Move mv = emulocke::moveFromRow(*row);
    const DamageResult r = emulocke::calculate(3, 3, a, d, mv, Field{});
    std::printf("comet %d-%d hits %d\n", r.min, r.max, r.hits);
    REQUIRE(r.min == 132 && r.max == 156);
}

void testFixedAndImmune() {
    Pokemon mew;
    mew.name = "Mew";
    mew.level = 50;
    mew.hp = 100;
    mew.maxHp = 217;
    Pokemon vulpix;
    vulpix.name = "Vulpix";
    vulpix.t1 = Type::Fire;
    vulpix.hp = 217;
    vulpix.maxHp = 217;
    Move toss;
    toss.name = "Seismic Toss";
    toss.kind = MoveKind::Level;
    toss.type = Type::Fighting;
    const DamageResult r = emulocke::calculate(3, 3, mew, vulpix, toss, Field{});
    REQUIRE(r.min == 50 && r.max == 50);
    Pokemon gengar;
    gengar.name = "Gengar";
    gengar.t1 = Type::Ghost;
    gengar.t2 = Type::Poison;
    Move beam;
    beam.name = "Hyper Beam";
    beam.type = Type::Normal;
    beam.bp = 150;
    const DamageResult immune = emulocke::calculate(3, 3, mew, gengar, beam, Field{});
    REQUIRE(immune.immune || immune.max == 0);
}

void testHpBar() {
    REQUIRE(emulocke::hpBarPixels(80, 80) == 48);
    REQUIRE(emulocke::hpBarPixels(40, 80) == 24);
    REQUIRE(emulocke::hpBarPixels(1, 80) == 1);
    REQUIRE(emulocke::hpBarPixels(0, 80) == 0);
    REQUIRE(emulocke::hpBarPixels(1, 300) == 1);
    int lo = 0;
    int hi = 0;
    emulocke::hpBarPctRange(48, lo, hi);
    REQUIRE(lo == 100 && hi == 100);
    emulocke::hpBarPctRange(24, lo, hi);
    REQUIRE(lo == 50 && hi == 52);
    emulocke::hpBarPctRange(1, lo, hi);
    REQUIRE(lo == 1 && hi == 4);
    emulocke::hpBarPctRange(0, lo, hi);
    REQUIRE(lo == 0 && hi == 0);
    emulocke::hpBarPctRange(9, lo, hi);
    REQUIRE(lo == 18 && hi == 20);
    REQUIRE(emulocke::hpExactPct(80, 80) == 100);
    REQUIRE(emulocke::hpExactPct(40, 80) == 50);
    REQUIRE(emulocke::hpExactPct(1, 80) == 1);
    REQUIRE(emulocke::hpExactPct(1, 300) == 1);
    for (int maxHp = 1; maxHp <= 200; ++maxHp) {
        int prevPx = -1;
        int prevLo = -1;
        int prevHi = -1;
        for (int hp = 0; hp <= maxHp; ++hp) {
            const int px = emulocke::hpBarPixels(hp, maxHp);
            emulocke::hpBarPctRange(px, lo, hi);
            if (px == 24) {
                REQUIRE(lo == 50 && hi == 52);
            }
            if (px == prevPx) {
                REQUIRE(lo == prevLo && hi == prevHi);
            }
            prevPx = px;
            prevLo = lo;
            prevHi = hi;
        }
    }
}

void testSwitchIn() {
    const emulocke::CalcPack* pack = emulocke::calcPack(emulocke::kFireRedUs10Uuid, {});
    REQUIRE(pack);
    const emulocke::PackTrainer* rival = emulocke::packTrainer(*pack, 332);
    REQUIRE(rival && rival->count == 4);
    REQUIRE(emulocke::trainerMon(*pack, *rival, 0)->species == 17);
    REQUIRE(emulocke::trainerMon(*pack, *rival, 1)->species == 63);
    REQUIRE(emulocke::trainerMon(*pack, *rival, 3)->species == 7);
    bool down[6]{};
    int order[6];
    Pokemon grass;
    grass.t1 = Type::Grass;
    grass.t2 = Type::Poison;
    grass.hp = 80;
    grass.maxHp = 80;
    emulocke::switchOrder(*pack, *rival, down, grass, 3, order);
    REQUIRE(order[0] == 0 && order[1] == 1);
    REQUIRE(order[2] >= 0 && order[3] >= 0 && order[4] < 0);
    Pokemon fire;
    fire.t1 = Type::Fire;
    fire.t2 = Type::Flying;
    fire.hp = 90;
    fire.maxHp = 90;
    emulocke::switchOrder(*pack, *rival, down, fire, 3, order);
    REQUIRE(order[0] == 0 && order[1] == 3);
    const emulocke::PackTrainer* brock = emulocke::packTrainer(*pack, 414);
    emulocke::switchOrder(*pack, *brock, down, grass, 3, order);
    REQUIRE(order[0] == 0 && order[1] == 1);
}

void testFairyCfru() {
    REQUIRE(emulocke::typeMul(6, Type::Fairy, Type::Dragon) == 20);
    REQUIRE(emulocke::typeMul(3, Type::Fairy, Type::Dragon) == 10);
    Pokemon fairy;
    fairy.name = "Clefable";
    fairy.t1 = Type::Fairy;
    fairy.level = 50;
    fairy.spa = 150;
    Pokemon dragon;
    dragon.name = "Dragonite";
    dragon.t1 = Type::Dragon;
    dragon.t2 = Type::Flying;
    dragon.spd = 100;
    dragon.hp = 150;
    Move moon;
    moon.name = "Moonblast";
    moon.type = Type::Fairy;
    moon.bp = 95;
    moon.split = 1;
    const DamageResult r = emulocke::calculate(7, 6, fairy, dragon, moon, Field{});
    REQUIRE(!r.immune && r.min > 0);
}

}  // namespace

int main() {
    testCometPunch();
    testFixedAndImmune();
    testFairyCfru();
    testHpBar();
    testSwitchIn();
    std::printf("calc check ok\n");
    return 0;
}
