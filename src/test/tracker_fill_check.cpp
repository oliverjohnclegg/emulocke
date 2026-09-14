#include "adapter/Cartridge.hpp"
#include "adapter/GameAdapter.hpp"
#include "adapter/gen45/Names.hpp"
#include "run/Catalog.hpp"
#include "test/Check.hpp"
#include "tracker/Atlas.hpp"
#include "tracker/Log.hpp"
#include "tracker/frlg/Keys.hpp"

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <span>
#include <string>
#include <vector>

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
    pallet.party.mons[0].species = 2;
    emulocke::applyTrackerFill(starterLog, *atlas, pallet);
    REQUIRE(starterLog.caught("starter").species == 1);

    const emulocke::TrackerAtlas* unbound = emulocke::trackerAtlas(emulocke::kUnboundUuid, "");
    REQUIRE(unbound != nullptr);
    emulocke::TrackerLog ubLog;
    emulocke::GameSnapshot ubSnap;
    ubSnap.ok = true;
    ubSnap.party.count = 1;
    ubSnap.party.mons[0].species = 398;
    ubSnap.party.mons[0].personality = 11;
    emulocke::applyTrackerFill(ubLog, *unbound, ubSnap);
    REQUIRE(ubLog.caught("starter").species == 398);

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
    REQUIRE(!deadLoaded.markedDead(0));
    deadLoaded.setCaught("route-1", 16, 99);
    REQUIRE(deadLoaded.markedDead(99));
    REQUIRE(!deadLoaded.markedDead(1));
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

    const emulocke::TrackerAtlas* rrAtlas = emulocke::trackerAtlas(emulocke::kRadicalRedUuid, "");
    REQUIRE(rrAtlas != nullptr);
    emulocke::TrackerLog rrLog;
    emulocke::GameSnapshot rrSnap;
    rrSnap.ok = true;
    rrSnap.party.count = 1;
    rrSnap.party.mons[0].species = 758;
    rrSnap.party.mons[0].personality = 5;
    emulocke::applyTrackerFill(rrLog, *rrAtlas, rrSnap);
    REQUIRE(rrLog.caught("starter").species == 758);
    REQUIRE(std::strcmp(emulocke::nationalSpeciesRef(650).slug, "chespin") == 0);

    const emulocke::TrackerAtlas* blaze = emulocke::trackerAtlas(emulocke::kBlazeBlackUuid, "");
    REQUIRE(blaze != nullptr);
    emulocke::TrackerLog blazeLog;
    emulocke::GameSnapshot blazeSnap;
    blazeSnap.ok = true;
    blazeSnap.party.count = 1;
    blazeSnap.party.mons[0].species = 495;
    blazeSnap.party.mons[0].personality = 9;
    emulocke::applyTrackerFill(blazeLog, *blaze, blazeSnap);
    REQUIRE(blazeLog.caught("starter").species == 495);
    REQUIRE(blazeLog.defeated("b1"));
    REQUIRE(blazeLog.defeated("c1"));
    REQUIRE(!blazeLog.defeated("n1"));

    emulocke::TrackerLog servineLog;
    emulocke::GameSnapshot servineSnap;
    servineSnap.ok = true;
    servineSnap.party.count = 1;
    servineSnap.party.mons[0].species = 496;
    servineSnap.party.mons[0].personality = 13;
    emulocke::applyTrackerFill(servineLog, *blaze, servineSnap);
    REQUIRE(servineLog.caught("starter").species == 496);
    REQUIRE(servineLog.defeated("b1"));
    REQUIRE(servineLog.defeated("c1"));
    REQUIRE(!servineLog.defeated("n1"));

    const char* home = std::getenv("HOME");
    if (home) {
        const auto savPath = std::filesystem::path(home) / "test_roms" / "test_blaze_black.sav";
        if (std::filesystem::exists(savPath)) {
            std::ifstream in(savPath, std::ios::binary);
            std::vector<uint8_t> sav(std::istreambuf_iterator<char>(in), {});
            const emulocke::GameAdapter* bb = emulocke::adapterForSave(sav);
            REQUIRE(bb != nullptr);
            const emulocke::GameSnapshot real = bb->readSave(sav);
            REQUIRE(real.ok);
            REQUIRE(std::string(real.trainer.name) == "Gibbers");
            REQUIRE(real.party.count == 4);
            REQUIRE(real.progress.starterSpecies == 496);
            REQUIRE((real.gyms.earned & 1) != 0);
            REQUIRE((real.gyms.earned & 2) == 0);
            emulocke::TrackerLog realLog;
            emulocke::applyTrackerFill(realLog, *blaze, real);
            REQUIRE(realLog.caught("starter").species == 496);
            REQUIRE(realLog.defeated("gym-1"));
            REQUIRE(!realLog.defeated("gym-2"));
            REQUIRE(realLog.defeated("b1"));
            REQUIRE(realLog.defeated("c1"));
            REQUIRE(!realLog.defeated("n1"));
            const auto stickyPath = std::filesystem::temp_directory_path() / "emulocke-bb-starter.ini";
            {
                std::ofstream out(stickyPath);
                out << "[caught]\nstarter=0:0:c\n[boss]\n";
            }
            emulocke::TrackerLog sticky;
            REQUIRE(sticky.load(stickyPath));
            emulocke::applyTrackerFill(sticky, *blaze, real);
            REQUIRE(sticky.caught("starter").species == 496);
            std::filesystem::remove(stickyPath);
        }
    }

    blazeLog.setDefeated("gym-1", true);
    blazeSnap.gyms.slots = 8;
    blazeSnap.gyms.earned = 0;
    emulocke::applyTrackerFill(blazeLog, *blaze, blazeSnap);
    REQUIRE(!blazeLog.defeated("gym-1"));
    blazeSnap.gyms.earned = 1;
    emulocke::applyTrackerFill(blazeLog, *blaze, blazeSnap);
    REQUIRE(blazeLog.defeated("gym-1"));
    REQUIRE(!blazeLog.defeated("gym-2"));

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
