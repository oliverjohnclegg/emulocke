#include "calc/Pack.hpp"
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
    const emulocke::PackMon* geodude = emulocke::trainerMon(*pack, *brock, 0);
    const emulocke::PackMon* onix = emulocke::trainerMon(*pack, *brock, 1);
    REQUIRE(geodude && geodude->species == 74 && geodude->level == 12);
    REQUIRE(onix && onix->species == 95 && onix->level == 14);
    REQUIRE(emulocke::calcPack(emulocke::kFireRedUs11Uuid, {}) == pack);
    REQUIRE(emulocke::calcPack(emulocke::kLeafGreenUs10Uuid, {}) == pack);
    REQUIRE(emulocke::calcPack(emulocke::kLeafGreenUs11Uuid, {}) == pack);
    std::printf("calc pack check ok trainers=%d\n", pack->trainerCount);
    return 0;
}
