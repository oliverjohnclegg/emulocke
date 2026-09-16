#include "adapter/Snapshot.hpp"
#include "adapter/Species.hpp"
#include "poke/Dex.hpp"
#include "poke/Showdown.hpp"
#include "test/Check.hpp"

#include <cstdio>
#include <string>

int main() {
    REQUIRE(emulocke::speciesBst(25) == 300);
    REQUIRE(emulocke::speciesBst(65) == 490);
    REQUIRE(emulocke::speciesBst(3) > emulocke::speciesBst(1));
    REQUIRE(std::string(emulocke::moveName(33)) == "Tackle");
    REQUIRE(std::string(emulocke::moveName(94)) == "Psychic");
    REQUIRE(std::string(emulocke::itemName(200, true)) == "Leftovers");
    REQUIRE(std::string(emulocke::itemName(234, false)) == "Leftovers");
    REQUIRE(std::string(emulocke::abilityName(28)) == "Synchronize");
    REQUIRE(std::string(emulocke::natureName(10)) == "Timid");
    REQUIRE(emulocke::gen3Adapter("firered-us-1.0"));
    REQUIRE(!emulocke::gen3Adapter("diamond-us"));
    REQUIRE(emulocke::levelFromExp(1, 135) == 5);
    REQUIRE(emulocke::levelFromExp(1, 0) == 1);

    emulocke::Mon mon;
    mon.species = 65;
    mon.heldItem = 200;
    mon.personality = 10;
    mon.level = 36;
    mon.abilityNum = 0;
    mon.nature = 10;
    mon.evSpe = 252;
    mon.evSpa = 6;
    mon.ivHp = 31;
    mon.ivAtk = 0;
    mon.ivDef = 31;
    mon.ivSpa = 31;
    mon.ivSpd = 31;
    mon.ivSpe = 31;
    mon.moves[0] = 94;
    mon.moves[1] = 85;
    std::snprintf(mon.speciesName, sizeof mon.speciesName, "ALAKAZAM");
    std::snprintf(mon.nickname, sizeof mon.nickname, "KAZ");
    emulocke::SpeciesRef ref;
    ref.national = 65;
    ref.name = "Alakazam";
    ref.slug = "alakazam";
    const std::string set = emulocke::exportSet(mon, ref, true);
    REQUIRE(set.find("KAZ (Alakazam)") != std::string::npos);
    REQUIRE(set.find("@ Leftovers") != std::string::npos);
    REQUIRE(set.find("Ability: Synchronize") != std::string::npos);
    REQUIRE(set.find("Level: 36") != std::string::npos);
    REQUIRE(set.find("Timid Nature") != std::string::npos);
    REQUIRE(set.find("EVs: 6 SpA / 252 Spe") != std::string::npos);
    REQUIRE(set.find("IVs: 0 Atk") != std::string::npos);
    REQUIRE(set.find("- Psychic") != std::string::npos);
    REQUIRE(set.find("- Thunderbolt") != std::string::npos);
    REQUIRE(std::string(emulocke::monAbility(mon, 65, true)) == "Synchronize");

    std::string team;
    emulocke::appendSet(team, mon, ref, true);
    emulocke::Mon mewtwo = mon;
    mewtwo.species = 150;
    mewtwo.nickname[0] = 0;
    std::snprintf(mewtwo.speciesName, sizeof mewtwo.speciesName, "MEWTWO");
    emulocke::SpeciesRef mewtwoRef;
    mewtwoRef.national = 150;
    mewtwoRef.name = "Mewtwo";
    emulocke::appendSet(team, mewtwo, mewtwoRef, true);
    REQUIRE(team.find("KAZ (Alakazam)") != std::string::npos);
    REQUIRE(team.find("Mewtwo") != std::string::npos);
    REQUIRE(team.find("\n\n") != std::string::npos);

    emulocke::Mon boxed;
    boxed.species = 1;
    boxed.experience = 135;
    REQUIRE(emulocke::monLevel(boxed, 1) == 5);

    std::printf("poke check ok\n");
    return 0;
}
