#include "calc/Build.hpp"
#include "calc/Calculate.hpp"
#include "calc/Dex.hpp"
#include "calc/Pack.hpp"
#include "calc/Stats.hpp"
#include "calc/Type.hpp"
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
    std::printf("calc check ok\n");
    return 0;
}
