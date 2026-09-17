#include "adapter/GameAdapter.hpp"
#include "emu/FileBytes.hpp"
#include "run/BatteryWatch.hpp"
#include "test/Check.hpp"
#include "test/snapshot_fixtures.hpp"

#include <chrono>
#include <filesystem>

namespace {

std::filesystem::path scratchBattery() {
    const auto dir = std::filesystem::temp_directory_path() / "emulocke-battery-watch";
    std::filesystem::create_directories(dir);
    return dir / "run.sav";
}

void bumpWriteTime(const std::filesystem::path& path) {
    const auto stamp = std::filesystem::last_write_time(path);
    std::filesystem::last_write_time(path, stamp + std::chrono::seconds(2));
}

void checkRereadsOnlyWhenFileChanges() {
    const auto path = scratchBattery();
    const auto sav = makeSuiteSav(SuiteSav::Frlg);
    REQUIRE(emulocke::writeWholeFile(path.string(), sav.data(), sav.size()));
    const emulocke::GameAdapter* adapter = emulocke::adapterForSave(sav);
    REQUIRE(adapter != nullptr);

    emulocke::BatteryWatch watch;
    REQUIRE(watch.refresh(path, *adapter));
    REQUIRE(watch.snapshot().ok);
    REQUIRE(!watch.refresh(path, *adapter));
    REQUIRE(!watch.refresh(path, *adapter));

    bumpWriteTime(path);
    REQUIRE(watch.refresh(path, *adapter));
    REQUIRE(!watch.refresh(path, *adapter));

    const auto bumped = std::filesystem::last_write_time(path);
    std::vector<uint8_t> grown = sav;
    grown.push_back(0);
    REQUIRE(emulocke::writeWholeFile(path.string(), grown.data(), grown.size()));
    std::filesystem::last_write_time(path, bumped);
    REQUIRE(watch.refresh(path, *adapter));

    std::filesystem::remove(path);
    REQUIRE(!watch.refresh(path, *adapter));
    REQUIRE(!watch.snapshot().ok);
    std::filesystem::remove_all(path.parent_path());
}

void checkMergePrefersLiveParty() {
    const auto path = scratchBattery();
    const auto sav = makeSuiteSav(SuiteSav::Frlg);
    REQUIRE(emulocke::writeWholeFile(path.string(), sav.data(), sav.size()));
    emulocke::BatteryWatch watch;
    REQUIRE(watch.refresh(path, *emulocke::adapterForSave(sav)));
    const emulocke::GameSnapshot fromSave = watch.snapshot();
    REQUIRE(fromSave.party.count > 0);

    emulocke::GameSnapshot empty;
    watch.mergeInto(empty);
    REQUIRE(empty.ok && empty.party.count == fromSave.party.count);

    emulocke::GameSnapshot live = fromSave;
    live.party.count = 1;
    live.gyms.slots = 0;
    live.boxes = {};
    live.overworld = {};
    watch.mergeInto(live);
    REQUIRE(live.party.count == 1);
    REQUIRE(live.gyms.slots == fromSave.gyms.slots);
    if (fromSave.boxes.boxes[0].mons[0].species != 0) {
        REQUIRE(live.boxes.boxes[0].mons[0].species == fromSave.boxes.boxes[0].mons[0].species);
    }
    if (fromSave.overworld.mapName[0] != 0) {
        REQUIRE(std::string(live.overworld.mapName) == fromSave.overworld.mapName);
    }
    std::filesystem::remove_all(path.parent_path());
}

}  // namespace

void testBatteryWatch() {
    checkRereadsOnlyWhenFileChanges();
    checkMergePrefersLiveParty();
}
