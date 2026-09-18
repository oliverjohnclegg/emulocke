#include "calc/Build.hpp"
#include "calc/Calculate.hpp"
#include "calc/Dex.hpp"
#include "calc/HpBar.hpp"
#include "calc/Move.hpp"
#include "calc/Pack.hpp"
#include "calc/Type.hpp"
#include "run/Catalog.hpp"
#include "test/Check.hpp"

#include <cstdio>
#include <cstring>

int main() {
    const emulocke::SpeciesRow* snivy = emulocke::nationalDexRow(495);
    REQUIRE(snivy && std::strcmp(snivy->slug, "snivy") == 0);
    const emulocke::MoveRow* vine = emulocke::moveById(22);
    REQUIRE(vine);
    const emulocke::Move vw = emulocke::moveFromRow(*vine);
    REQUIRE(vw.category(3) == emulocke::MoveCat::Special);
    REQUIRE(vw.category(5) == emulocke::MoveCat::Physical);

    const emulocke::CalcPack* blaze = emulocke::calcPack(emulocke::kBlazeBlackUuid, {});
    REQUIRE(blaze);
    const emulocke::PackTrainer* acc = emulocke::packTrainer(*blaze, 64);
    REQUIRE(acc && std::strcmp(acc->name, "N") == 0);
    const emulocke::PackMon* nincada = emulocke::trainerMon(*blaze, *acc, 0);
    REQUIRE(nincada && nincada->species == 290);
    REQUIRE(nincada->moves[0] == 10 && nincada->moves[1] == 106 && nincada->moves[2] == 450 &&
        nincada->moves[3] == 141);
    emulocke::Pokemon ninc = emulocke::pokemonFromPack(*nincada, blaze);
    REQUIRE(ninc.maxHp == 20 && ninc.def == 16);
    emulocke::Pokemon rattata{};
    rattata.t1 = emulocke::Type::Normal;
    rattata.level = 10;
    rattata.atk = 16;
    const emulocke::MoveRow* wheelRow = emulocke::moveById(172);
    REQUIRE(wheelRow && wheelRow->bp == 60);
    const emulocke::Move vanillaWheel = emulocke::moveFromRow(*wheelRow);
    const emulocke::DamageResult vanilla = emulocke::calculate(5, 5, rattata, ninc, vanillaWheel, {});
    REQUIRE(vanilla.min == 15 && vanilla.max == 18);
    REQUIRE(vanilla.min * 100 / ninc.maxHp == 75);
    REQUIRE(vanilla.max * 100 / ninc.maxHp == 90);
    const emulocke::Move blazeWheel = emulocke::packedMove(blaze, 172);
    REQUIRE(blazeWheel.bp == 75);
    const emulocke::DamageResult packed = emulocke::calculate(5, 5, rattata, ninc, blazeWheel, {});
    REQUIRE(packed.min == 18 && packed.max == 22);
    REQUIRE(!packed.ohko(ninc.maxHp) && packed.max >= ninc.maxHp);
    const emulocke::Move cut = emulocke::packedMove(blaze, 15);
    REQUIRE(cut.bp == 60 && cut.type == emulocke::Type::Grass);
    const emulocke::CalcPack* volt = emulocke::calcPack(emulocke::kVoltWhiteUuid, {});
    REQUIRE(volt && emulocke::packedMove(volt, 172).bp == 75);

    emulocke::PackMon snivyMon{495, 7, 0, 0, {22, 33, 0, 0}};
    emulocke::Pokemon atk = emulocke::pokemonFromPack(snivyMon, blaze);
    emulocke::Pokemon def = emulocke::pokemonFromPack(*nincada, blaze);
    const emulocke::DamageResult grass = emulocke::calculate(5, 5, atk, def, vw, emulocke::Field{});
    REQUIRE(!grass.immune);
    REQUIRE(def.maxHp > 0);
    REQUIRE(grass.max * 100 / def.maxHp < 25);

    const emulocke::MoveRow* gustRow = emulocke::moveById(16);
    REQUIRE(gustRow);
    const emulocke::Move gust = emulocke::moveFromRow(*gustRow);
    REQUIRE(gust.category(5) == emulocke::MoveCat::Special);
    const emulocke::PackMon* purrloin = emulocke::trainerMon(*blaze, *acc, 1);
    REQUIRE(purrloin && purrloin->species == 509);
    emulocke::Pokemon pidgey{};
    pidgey.t1 = emulocke::Type::Normal;
    pidgey.t2 = emulocke::Type::Flying;
    pidgey.level = 6;
    pidgey.spa = 10;
    emulocke::Pokemon purr = emulocke::pokemonFromPack(*purrloin, blaze);
    REQUIRE(purr.maxHp == 21);
    REQUIRE(purr.spd == 9);
    const emulocke::DamageResult liveGust = emulocke::calculate(5, 5, pidgey, purr, gust, {});
    REQUIRE(liveGust.min == 5 && liveGust.max == 7);
    REQUIRE(liveGust.min * 100 / purr.maxHp == 23);
    REQUIRE(liveGust.max * 100 / purr.maxHp == 33);
    pidgey.spa = 8;
    const emulocke::DamageResult pkGust = emulocke::calculate(5, 5, pidgey, purr, gust, {});
    REQUIRE(pkGust.min == 5 && pkGust.max == 6);
    REQUIRE(pkGust.max * 100 / purr.maxHp == 28);
    int lo = 0;
    int hi = 0;
    emulocke::hpBarPctRange(emulocke::hpBarPixels(14, 21), lo, hi);
    REQUIRE(lo == 66 && hi == 68);
    emulocke::Mon raw{};
    raw.species = 16;
    raw.level = 4;
    raw.maxHp = 17;
    raw.hp = 11;
    raw.spAttack = 8;
    emulocke::Pokemon fromPk = emulocke::pokemonFromSnap(raw, blaze);
    REQUIRE(fromPk.level == 4);
    REQUIRE(fromPk.spa == 8);
    emulocke::BattleBattler live{};
    live.maxHp = 21;
    live.hp = 11;
    live.level = 6;
    emulocke::applyBattler(fromPk, live);
    REQUIRE(fromPk.level == 6);
    REQUIRE(fromPk.maxHp == 21);

    const emulocke::PackTrainer* castle = emulocke::packTrainer(*blaze, 587);
    REQUIRE(castle && castle->count == 6);
    const uint16_t want[6] = {571, 467, 80, 142, 474, 644};
    for (int i = 0; i < 6; ++i) {
        const emulocke::PackMon* mon = emulocke::trainerMon(*blaze, *castle, i);
        REQUIRE(mon && mon->species == want[i]);
        REQUIRE(mon->moves[0] && mon->moves[1] && mon->moves[2] && mon->moves[3]);
    }
    return 0;
}
