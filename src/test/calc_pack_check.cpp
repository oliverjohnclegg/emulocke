#include "calc/Ai.hpp"
#include "calc/Build.hpp"
#include "calc/Pack.hpp"
#include "calc/Type.hpp"
#include "run/Catalog.hpp"
#include "test/Check.hpp"

#include <cstdio>
#include <cstring>

int main() {
    REQUIRE(emulocke::calcPack(emulocke::kRadicalRedUuid, {}) == nullptr);
    REQUIRE(emulocke::calcPack(emulocke::kUnboundUuid, {}) == nullptr);
    const emulocke::CalcPack* pack = emulocke::calcPack(emulocke::kFireRedUs10Uuid, {});
    REQUIRE(pack);
    REQUIRE(pack->dmgGen == 3 && pack->typeChart == 3 && pack->switchIn == 3);
    REQUIRE(pack->trainerCount > 400);
    const emulocke::PackTrainer* brock = emulocke::packTrainer(*pack, 414);
    REQUIRE(brock);
    REQUIRE(std::strcmp(brock->name, "BROCK") == 0);
    REQUIRE(brock->count == 2);
    REQUIRE(brock->aiFlags ==
        (emulocke::kAiCheckBadMove | emulocke::kAiCheckViability | emulocke::kAiTryToFaint));
    const emulocke::PackMon* geodude = emulocke::trainerMon(*pack, *brock, 0);
    const emulocke::PackMon* onix = emulocke::trainerMon(*pack, *brock, 1);
    REQUIRE(geodude && geodude->species == 74 && geodude->level == 12);
    REQUIRE(onix && onix->species == 95 && onix->level == 14);
    emulocke::Pokemon geo = emulocke::pokemonFromPack(*geodude);
    emulocke::Pokemon grass;
    grass.t1 = emulocke::Type::Grass;
    grass.t2 = emulocke::Type::Poison;
    grass.hp = 80;
    grass.maxHp = 80;
    grass.spe = 50;
    grass.def = 80;
    int pct[4]{};
    emulocke::moveUsePct(pack->dmgGen, pack->typeChart, brock->aiFlags, geo, grass, geodude->moves,
        emulocke::Field{}, pct);
    REQUIRE(pct[0] == 100 && pct[1] == 0);
    emulocke::Pokemon ghost;
    ghost.t1 = emulocke::Type::Ghost;
    ghost.t2 = emulocke::Type::Poison;
    ghost.hp = 120;
    ghost.maxHp = 120;
    emulocke::moveUsePct(pack->dmgGen, pack->typeChart, brock->aiFlags, geo, ghost, geodude->moves,
        emulocke::Field{}, pct);
    REQUIRE(pct[0] == 0 && pct[1] == 100);
    const emulocke::PackTrainer* calvin = emulocke::packTrainer(*pack, 90);
    REQUIRE(calvin && calvin->aiFlags == emulocke::kAiCheckBadMove);
    REQUIRE(emulocke::calcPack(emulocke::kFireRedUs11Uuid, {}) == pack);
    REQUIRE(emulocke::calcPack(emulocke::kLeafGreenUs10Uuid, {}) == pack);
    REQUIRE(emulocke::calcPack(emulocke::kLeafGreenUs11Uuid, {}) == pack);
    std::printf("calc pack check ok trainers=%d\n", pack->trainerCount);
    return 0;
}