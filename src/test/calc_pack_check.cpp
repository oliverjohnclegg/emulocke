#include "calc/Ai.hpp"
#include "calc/Build.hpp"
#include "calc/Pack.hpp"
#include "calc/Session.hpp"
#include "calc/Type.hpp"
#include "run/Catalog.hpp"
#include "test/Check.hpp"

#include <cstdio>
#include <cstring>

int main() {
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

    const emulocke::CalcPack* em = emulocke::calcPack(emulocke::kEmeraldUsUuid, {});
    REQUIRE(em && em->dmgGen == 3 && em->trainerCount > 400);
    const emulocke::PackTrainer* roxanne = emulocke::packTrainer(*em, 265);
    REQUIRE(roxanne && std::strcmp(roxanne->name, "ROXANNE") == 0);
    REQUIRE(emulocke::calcPack(emulocke::kRubyUsUuid, {})->trainerCount > 300);

    const emulocke::CalcPack* pt = emulocke::calcPack(emulocke::kPlatinumUsUuid, {});
    REQUIRE(pt && pt->dmgGen == 4 && pt->trainerCount > 500);
    const emulocke::PackTrainer* roark = emulocke::packTrainer(*pt, 246);
    REQUIRE(roark);
    REQUIRE(std::strcmp(roark->name, "Leader Roark") == 0);
    REQUIRE(std::strcmp(roark->cls, "Leader") == 0);
    REQUIRE(std::strcmp(roark->location, "Oreburgh Gym") == 0);
    REQUIRE(emulocke::pokemonFromPack(*emulocke::trainerMon(*pt, *roark, 0), pt).species != 0);
    REQUIRE(emulocke::calcPack(emulocke::kDiamondUsUuid, {})->dmgGen == 4);
    REQUIRE(emulocke::calcPack(emulocke::kHeartGoldUsUuid, {})->dmgGen == 4);
    REQUIRE(emulocke::calcPack(emulocke::kBlackUsUuid, {})->dmgGen == 5);
    REQUIRE(emulocke::calcPack(emulocke::kWhite2UsUuid, {})->dmgGen == 5);
    const emulocke::CalcPack* blaze = emulocke::calcPack(emulocke::kBlazeBlackUuid, {});
    REQUIRE(blaze && blaze->dmgGen == 5 && blaze->trainerCount > 400);
    emulocke::CalcSession session;
    session.setPack(blaze);
    session.search("N");
    REQUIRE(!session.trainerHits().empty());
    REQUIRE(std::strcmp(session.trainerHits().front()->name, "N") == 0);
    REQUIRE(std::strcmp(session.trainerHits().front()->cls, "PKMN Trainer") == 0);
    REQUIRE(std::strcmp(session.trainerHits().front()->location, "Accumula Town") == 0);
    session.search("Accumula");
    REQUIRE(!session.trainerHits().empty());
    bool nAtAccumula = false;
    for (const emulocke::PackTrainer* t : session.trainerHits()) {
        nAtAccumula |= std::strcmp(t->name, "N") == 0;
    }
    REQUIRE(nAtAccumula);
    session.search("Bianca");
    REQUIRE(!session.trainerHits().empty());
    REQUIRE(std::strcmp(session.trainerHits().front()->name, "Bianca") == 0);
    session.search("Youngster");
    REQUIRE(!session.trainerHits().empty());
    REQUIRE(std::strcmp(session.trainerHits().front()->cls, "Youngster") == 0);
    REQUIRE(emulocke::calcPack(emulocke::kSacredGoldUuid, {})->dmgGen == 4);
    REQUIRE(emulocke::calcPack(emulocke::kEmeraldKaizoUuid, {})->trainerCount > 400);
    REQUIRE(emulocke::calcPack(emulocke::kFireRedOmegaUuid, {})->trainerCount > 400);
    const emulocke::CalcPack* rr = emulocke::calcPack(emulocke::kRadicalRedUuid, {});
    REQUIRE(rr && rr->dmgGen == 8 && rr->trainerCount > 400);
    const emulocke::PackTrainer* rrBrock = emulocke::packTrainer(*rr, 414);
    REQUIRE(rrBrock && std::strcmp(rrBrock->name, "Brock") == 0);
    REQUIRE(emulocke::calcPack(emulocke::kRadicalRedUuid, "hardcore") == rr);
    const emulocke::CalcPack* unbound = emulocke::calcPack(emulocke::kUnboundUuid, {});
    REQUIRE(unbound && unbound->dmgGen == 8 && unbound->trainerCount > 400);
    REQUIRE(emulocke::calcPack(emulocke::kUnboundUuid, "expert") == unbound);
    return 0;
}