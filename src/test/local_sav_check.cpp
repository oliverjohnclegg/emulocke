#include "adapter/GameAdapter.hpp"
#include "test/Check.hpp"

#include <cstdlib>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

namespace {

std::vector<uint8_t> readFile(const std::filesystem::path& path) {
    std::ifstream in(path, std::ios::binary);
    return {std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()};
}

void checkSav(const std::filesystem::path& path, const char* expectOt, int expectParty,
              const char* expectDifficulty = nullptr) {
    if (!std::filesystem::exists(path)) {
        return;
    }
    const auto sav = readFile(path);
    const emulocke::GameAdapter* adapter = emulocke::adapterForSave(sav);
    REQUIRE(adapter != nullptr);
    const emulocke::GameSnapshot snap = adapter->readSave(sav);
    REQUIRE(snap.ok);
    if (expectParty > 0) {
        REQUIRE(snap.party.count == expectParty);
    } else {
        REQUIRE(snap.party.count > 0);
    }
    REQUIRE(snap.party.mons[0].species != 0);
    int boxed = 0;
    for (int b = 0; b < emulocke::kMaxBoxes; ++b) {
        for (int s = 0; s < 30; ++s) {
            if (snap.boxes.boxes[static_cast<std::size_t>(b)].mons[static_cast<std::size_t>(s)].species) {
                ++boxed;
            }
        }
    }
    REQUIRE(boxed > 0);
    REQUIRE(snap.overworld.mapName[0] != 0);
    REQUIRE(snap.gyms.slots != 0);
    if (expectOt) {
        REQUIRE(std::string(snap.trainer.name) == expectOt);
    }
    if (expectDifficulty) {
        REQUIRE(std::string(snap.progress.difficulty) == expectDifficulty);
    }
    std::fprintf(stderr, "%s cart=%s ot=%s party=%u first=%s difficulty=%s\n", path.filename().c_str(),
                 snap.adapterId.data(), snap.trainer.name, snap.party.count, snap.party.mons[0].speciesName,
                 snap.progress.difficulty);
}

}  // namespace

void testLocalSaves() {
    const char* home = std::getenv("HOME");
    if (!home) {
        return;
    }
    const std::filesystem::path dir = std::filesystem::path(home) / "test_roms";
    checkSav(dir / "ruby-1_1-U.sav", "Eugene", 6);
    checkSav(dir / "emerald-U.sav", "Ash", 6);
    checkSav(dir / "diamond-1_13-U.sav", "Juli", 6);
    checkSav(dir / "platinum-U.sav", "Anthony", 6);
    checkSav(dir / "heartgold-U.sav", "Ethan", 6);
    checkSav(dir / "black-U.sav", "Raval", 6);
    checkSav(dir / "test_blaze_black.sav", "Gibbers", 4);
    checkSav(dir / "black2-U.sav", "Jason", 6);
    checkSav(dir / "rom_hack_patches" / "Pokemon Unbound.sav", nullptr, 6, "0");
    checkSav(std::filesystem::path(home) / ".local/share/emulocke/emulocke/runs/6af31828902eec1e/battery.sav",
        "A", 1);
}
