#include "adapter/Cartridge.hpp"
#include "adapter/GameAdapter.hpp"
#include "run/Catalog.hpp"
#include "test/Check.hpp"
#include "tracker/Atlas.hpp"
#include "tracker/Log.hpp"
#include "tracker/frlg/Keys.hpp"

#include <cstring>
#include <filesystem>
#include <fstream>
#include <span>
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
    REQUIRE(log.caught("route-1").status == emulocke::EncounterStatus::Captured);

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
    REQUIRE(loaded.caught("route-1").status == emulocke::EncounterStatus::Captured);
    REQUIRE(loaded.defeated("brock"));
    starterLog.setStatus("route-1", emulocke::EncounterStatus::Dead);
    REQUIRE(starterLog.save(path));
    emulocke::TrackerLog deadLoaded;
    REQUIRE(deadLoaded.load(path));
    REQUIRE(deadLoaded.caught("route-1").status == emulocke::EncounterStatus::Dead);
    REQUIRE(deadLoaded.caught("route-1").species == 16);
    {
        std::ofstream out(path, std::ios::trunc);
        out << "[caught]\nroute-2=25:9\n";
    }
    emulocke::TrackerLog legacy;
    REQUIRE(legacy.load(path));
    REQUIRE(legacy.caught("route-2").species == 25);
    REQUIRE(legacy.caught("route-2").personality == 9);
    REQUIRE(legacy.caught("route-2").status == emulocke::EncounterStatus::Captured);
    emulocke::TrackerLog missed;
    missed.setStatus("route-1", emulocke::EncounterStatus::Missed);
    emulocke::GameSnapshot later;
    later.ok = true;
    later.party.count = 1;
    later.party.mons[0].species = 16;
    later.party.mons[0].personality = 8;
    later.party.mons[0].metLocation = emulocke::kMapRoute1;
    emulocke::applyTrackerFill(missed, *atlas, later);
    REQUIRE(missed.caught("route-1").species == 0);
    REQUIRE(missed.caught("route-1").status == emulocke::EncounterStatus::Missed);
    std::filesystem::remove(path);

    emulocke::Cartridge fr;
    std::memcpy(fr.code, "BPRE", 4);
    fr.revision = 1;
    const emulocke::GameAdapter* adapter = emulocke::adapterFor(fr);
    REQUIRE(adapter != nullptr);
    REQUIRE(emulocke::matchSpeciesName(*adapter, "Pikachu") == 25);
    REQUIRE(emulocke::matchSpeciesName(*adapter, "Mr. Mime") == 122);

    const emulocke::TrackerAtlas* em = emulocke::trackerAtlas(emulocke::kEmeraldUsUuid, "");
    REQUIRE(em != nullptr);
    emulocke::TrackerLog treecko;
    emulocke::GameSnapshot hoenn;
    hoenn.ok = true;
    hoenn.party.count = 1;
    hoenn.party.mons[0].species = 252;
    hoenn.party.mons[0].personality = 3;
    emulocke::applyTrackerFill(treecko, *em, hoenn);
    REQUIRE(treecko.caught("starter").species == 252);

    emulocke::TrackerLog internal;
    hoenn.party.mons[0].species = 277;
    emulocke::applyTrackerFill(internal, *em, hoenn);
    REQUIRE(internal.caught("starter").species == 252);

    hoenn.gyms.earned = 1;
    emulocke::applyTrackerFill(internal, *em, hoenn);
    REQUIRE(internal.defeated("gym-1"));

    uint16_t wideMet[] = {400};
    emulocke::TrackerStop far{"far", emulocke::TrackerStopKind::Encounter, "Far", "", emulocke::BossKind::None,
                               emulocke::CatchKind::Met, wideMet, 1, nullptr, 0, 0, 0, 0};
    const std::span<const emulocke::TrackerStop> farStops{&far, 1};
    emulocke::TrackerAtlas wide{"t", farStops, {}};
    emulocke::TrackerLog farLog;
    emulocke::GameSnapshot distant;
    distant.ok = true;
    distant.party.count = 1;
    distant.party.mons[0].species = 16;
    distant.party.mons[0].personality = 4;
    distant.party.mons[0].metLocation = 400;
    emulocke::applyTrackerFill(farLog, wide, distant);
    REQUIRE(farLog.caught("far").species == 16);

    emulocke::Cartridge ruby;
    std::memcpy(ruby.code, "AXVE", 4);
    ruby.revision = 2;
    const emulocke::GameAdapter* rse = emulocke::adapterFor(ruby);
    REQUIRE(rse != nullptr);
    REQUIRE(emulocke::matchSpeciesName(*rse, "Treecko") == 252);
}
