#include "adapter/Cartridge.hpp"
#include "adapter/GameAdapter.hpp"
#include "run/Catalog.hpp"
#include "test/Check.hpp"
#include "tracker/Atlas.hpp"
#include "tracker/Log.hpp"
#include "tracker/frlg/Keys.hpp"

#include <cstring>
#include <filesystem>
#include <string>

void testTrackerFill() {
    const emulocke::TrackerAtlas* atlas = emulocke::trackerAtlas(emulocke::kFireRedUs10Uuid, "");
    REQUIRE(atlas != nullptr);

    emulocke::TrackerLog log;
    emulocke::GameSnapshot snap;
    snap.ok = true;
    snap.party.count = 1;
    snap.party.mons[0].species = 16;
    snap.party.mons[0].personality = 413912340;
    snap.party.mons[0].metLocation = emulocke::kMapRoute1;
    emulocke::applyTrackerFill(log, *atlas, snap);
    REQUIRE(log.caught("route-1").species == 16);
    REQUIRE(log.caught("route-1").personality == 413912340);

    snap.party.count = 2;
    snap.party.mons[1].species = 19;
    snap.party.mons[1].personality = 99;
    snap.party.mons[1].metLocation = emulocke::kMapRoute1;
    emulocke::applyTrackerFill(log, *atlas, snap);
    REQUIRE(log.caught("route-1").species == 16);

    snap.party.mons[0].species = 17;
    emulocke::applyTrackerFill(log, *atlas, snap);
    REQUIRE(log.caught("route-1").species == 17);

    emulocke::TrackerLog starterLog;
    emulocke::GameSnapshot pallet;
    pallet.ok = true;
    pallet.party.count = 1;
    pallet.party.mons[0].species = 1;
    pallet.party.mons[0].personality = 7;
    pallet.party.mons[0].metLocation = emulocke::kMapPallet;
    emulocke::applyTrackerFill(starterLog, *atlas, pallet);
    REQUIRE(starterLog.caught("starter").species == 1);
    REQUIRE(starterLog.caught("pallet-town").species == 0);

    const uint16_t brockFlag = emulocke::kFlagDefeatedBrock;
    pallet.progress.flags[brockFlag / 8] =
        static_cast<uint8_t>(pallet.progress.flags[brockFlag / 8] | (1u << (brockFlag % 8)));
    emulocke::applyTrackerFill(starterLog, *atlas, pallet);
    REQUIRE(starterLog.defeated("brock"));
    starterLog.setDefeated("brock", true);
    pallet.progress.flags[brockFlag / 8] = 0;
    emulocke::applyTrackerFill(starterLog, *atlas, pallet);
    REQUIRE(starterLog.defeated("brock"));

    const auto path = std::filesystem::temp_directory_path() / "emulocke-tracker-check.ini";
    starterLog.setCaught("route-1", 16, 0);
    REQUIRE(starterLog.save(path));
    emulocke::TrackerLog loaded;
    REQUIRE(loaded.load(path));
    REQUIRE(loaded.caught("starter").species == 1);
    REQUIRE(loaded.caught("route-1").species == 16);
    REQUIRE(loaded.caught("route-1").personality == 0);
    REQUIRE(loaded.defeated("brock"));
    std::filesystem::remove(path);

    emulocke::Cartridge fr;
    std::memcpy(fr.code, "BPRE", 4);
    fr.revision = 1;
    const emulocke::GameAdapter* adapter = emulocke::adapterFor(fr);
    REQUIRE(adapter != nullptr);
    REQUIRE(emulocke::matchSpeciesName(*adapter, "Pikachu") == 25);
    REQUIRE(emulocke::matchSpeciesName(*adapter, "Mr. Mime") == 122);
}
