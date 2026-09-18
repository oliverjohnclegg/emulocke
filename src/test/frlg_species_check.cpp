#include "adapter/Cartridge.hpp"
#include "adapter/GameAdapter.hpp"
#include "adapter/HackSpecies.hpp"
#include "adapter/frlg/FrlgNames.hpp"
#include "adapter/gen45/Names.hpp"
#include "test/Check.hpp"

#include <cstring>
#include <string>

void testFrlgSpecies() {
    const emulocke::SpeciesRef sealeo = emulocke::frlgSpeciesRef(342);
    REQUIRE(std::string(sealeo.slug) == "sealeo");
    REQUIRE(std::string(sealeo.name) == "Sealeo");
    REQUIRE(sealeo.national == 364);

    const emulocke::SpeciesRef servine = emulocke::frlgSpeciesRef(549);
    REQUIRE(std::string(servine.slug) == "servine");
    REQUIRE(std::string(servine.name) == "Servine");
    REQUIRE(servine.national == 496);

    const emulocke::SpeciesRef skorupi = emulocke::frlgSpeciesRef(504);
    REQUIRE(std::string(skorupi.slug) == "skorupi");
    REQUIRE(std::string(skorupi.name) == "Skorupi");
    REQUIRE(skorupi.national == 451);

    REQUIRE(std::string(emulocke::nationalSpeciesRef(342).slug) == "crawdaunt");
    REQUIRE(std::string(emulocke::nationalSpeciesRef(549).slug) == "lilligant");
    REQUIRE(std::string(emulocke::nationalSpeciesRef(504).slug) == "patrat");

    emulocke::Cartridge fr11;
    std::memcpy(fr11.code, "BPRE", 4);
    fr11.revision = 1;
    const emulocke::GameAdapter* fr = emulocke::adapterFor(fr11);
    REQUIRE(fr != nullptr);
    REQUIRE(std::string(emulocke::hackAwareSpecies(".gba", 342, fr).slug) == "sealeo");
    REQUIRE(std::string(emulocke::hackAwareSpecies(".nds", 342, fr).slug) == "crawdaunt");
    REQUIRE(std::string(emulocke::hackAwareSpecies(".gba", 549, fr).slug) == "servine");
    REQUIRE(std::string(emulocke::hackAwareSpecies(".nds", 549, fr).slug) == "lilligant");
    REQUIRE(std::string(emulocke::hackAwareSpecies(".gba", 504, fr).slug) == "skorupi");
    REQUIRE(std::string(emulocke::hackAwareSpecies(".nds", 504, fr).slug) == "patrat");
    REQUIRE(std::string(emulocke::hackAwareSpecies(".gba", 342, nullptr).slug) == "sealeo");

    REQUIRE(std::string(emulocke::frlgSpeciesRef(847).slug) == "oinkologne");
    const emulocke::SpeciesRef white = emulocke::unboundSpeciesRef(847);
    REQUIRE(std::string(white.slug) == "floette");
    REQUIRE(std::string(white.name) == "Floette");
    REQUIRE(white.national == 670);
    REQUIRE(std::string(emulocke::unboundSpeciesRef(848).slug) == "floette");
    REQUIRE(std::string(emulocke::unboundSpeciesRef(778).slug) == "floette");
    REQUIRE(std::string(emulocke::hackAwareSpecies(".gba", 847, fr, true).slug) == "floette");
    REQUIRE(std::string(emulocke::hackAwareSpecies(".gba", 847, fr, false).slug) == "oinkologne");
    REQUIRE(std::string(emulocke::hackAwareSpecies(".gba", 847, nullptr, true).slug) == "floette");
}
