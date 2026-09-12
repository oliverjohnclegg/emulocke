#include "run/GameId.hpp"
#include "run/NuzlockeRules.hpp"
#include "run/Roms.hpp"
#include "run/RunLabel.hpp"
#include "run/RunMeta.hpp"
#include "run/RunStore.hpp"

#include <chrono>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace {

int fails = 0;

void expect(bool cond, const char* msg) {
    if (!cond) {
        std::fprintf(stderr, "FAIL %s\n", msg);
        ++fails;
    }
}

void writeBytes(const std::filesystem::path& path, const std::vector<uint8_t>& bytes) {
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    out.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
}

std::vector<uint8_t> gbaWithCode(const char* code) {
    std::vector<uint8_t> bytes(0xC0, 0);
    std::memcpy(bytes.data() + 0xAC, code, 4);
    return bytes;
}

std::vector<uint8_t> ndsWithCode(const char* code) {
    std::vector<uint8_t> bytes(0x20, 0);
    std::memcpy(bytes.data() + 0x0C, code, 4);
    return bytes;
}

}  // namespace

int main() {
    expect(emulocke::gameIdFromCode("BPRE") == emulocke::GameId::FireRed, "BPRE");
    expect(emulocke::gameIdFromCode("BPEE") == emulocke::GameId::Emerald, "BPEE");
    expect(emulocke::gameIdFromCode("IRAO") == emulocke::GameId::Black, "IRAO");
    expect(emulocke::gameIdFromCode("IREO") == emulocke::GameId::Black2, "IREO");
    expect(!emulocke::gameIdFromCode("XXXX"), "unknown code");
    auto gba = gbaWithCode("BPRE");
    expect(emulocke::detectGameId(gba.data(), gba.size(), ".gba") == emulocke::GameId::FireRed, "gba detect");
    auto nds = ndsWithCode("IPKE");
    expect(emulocke::detectGameId(nds.data(), nds.size(), ".nds") == emulocke::GameId::HeartGold, "nds detect");
    expect(std::string(emulocke::rulesLabel(emulocke::regularRules())) == "REGULAR", "regular");
    expect(std::string(emulocke::rulesLabel(emulocke::hardcoreRules())) == "HARDCORE", "hardcore");
    emulocke::NuzlockeRules custom = emulocke::regularRules();
    custom.shinyClause = false;
    expect(std::string(emulocke::rulesLabel(custom)) == "CUSTOM", "custom");

    const auto tmp = std::filesystem::temp_directory_path() / "emulocke_run_test";
    std::filesystem::remove_all(tmp);
    const auto roms = tmp / "roms";
    const auto runs = tmp / "runs";
    std::filesystem::create_directories(roms);
    writeBytes(roms / "firered.gba", gbaWithCode("BPRE"));
    writeBytes(roms / "emerald.gba", gbaWithCode("BPEE"));
    writeBytes(roms / "homebrew.gba", gbaWithCode("HOME"));
    auto detected = emulocke::scanRomsDirs({roms});
    expect(detected.size() == 2, "scan size");
    expect(detected[0].gameId == emulocke::GameId::Emerald, "scan order emerald");
    expect(detected[1].gameId == emulocke::GameId::FireRed, "scan order firered");

    const auto older = roms / "firered_old.gba";
    writeBytes(older, gbaWithCode("BPRE"));
    std::filesystem::last_write_time(roms / "firered.gba", std::filesystem::last_write_time(older) + std::chrono::seconds(2));
    detected = emulocke::scanRomsDirs({roms});
    expect(std::filesystem::path(detected[1].romPath).filename() == "firered.gba", "newest dump wins");

    emulocke::RunStore store(runs);
    auto a = store.create(emulocke::GameId::FireRed, detected[1].romPath, emulocke::regularRules());
    auto b = store.create(emulocke::GameId::FireRed, detected[1].romPath, emulocke::hardcoreRules());
    auto c = store.create(emulocke::GameId::Emerald, detected[0].romPath, emulocke::hardcoreRules());
    expect(a && b && c, "create runs");
    expect(a->attempt == 1 && a->lineageId == a->id, "first attempt");
    expect(!std::filesystem::exists(store.batteryPath(a->id)), "no battery on create");
    expect(store.byGame(emulocke::GameId::FireRed).size() == 2, "group firered");
    expect(store.byGame(emulocke::GameId::Emerald).size() == 1, "group emerald");
    expect(emulocke::runHeadline(*a) == "Pokemon Fire Red: Regular Nuzlocke  |  Attempt #1", "headline");

    auto a2 = store.createAttempt(*a);
    expect(a2, "create attempt");
    expect(a2->id != a->id, "attempt has fresh id");
    expect(a2->lineageId == a->id, "same lineage");
    expect(a2->attempt == 2, "attempt ticks up");
    expect(a2->rules == a->rules && a2->romPath == a->romPath, "same settings");
    expect(!std::filesystem::exists(store.batteryPath(a2->id)), "fresh save");
    expect(!store.find(a->id), "source replaced");
    expect(!std::filesystem::exists(runs / a->id), "source dir gone");
    expect(store.runs().size() == 3, "replace not add");
    expect(store.byGame(emulocke::GameId::FireRed).size() == 2, "firered still two lineages");
    expect(emulocke::runHeadline(*a2) == "Pokemon Fire Red: Regular Nuzlocke  |  Attempt #2", "headline 2");

    auto a3 = store.createAttempt(*a2);
    expect(a3 && a3->attempt == 3, "attempt 3");
    expect(a3->lineageId == a->id, "lineage holds");
    expect(!store.find(a2->id), "prior attempt replaced");
    expect(store.runs().size() == 3, "still three lineages");
    expect(emulocke::runHeadline(*a3) == "Pokemon Fire Red: Regular Nuzlocke  |  Attempt #3", "headline 3");

    std::filesystem::create_directory(runs / a->id);
    emulocke::writeRunMeta(runs / a->id, *a);
    emulocke::RunStore stacked(runs);
    stacked.load();
    expect(stacked.runs().size() == 4, "leftover on disk");
    expect(stacked.byGame(emulocke::GameId::FireRed).size() == 2, "latest per lineage");
    bool sawLatest = false;
    for (const emulocke::Run* run : stacked.byGame(emulocke::GameId::FireRed)) {
        if (run->lineageKey() == a->id) {
            expect(run->attempt == 3, "listed latest attempt");
            sawLatest = true;
        }
    }
    expect(sawLatest, "listed regular firered");

    emulocke::RunStore loaded(runs);
    loaded.load();
    expect(loaded.runs().size() == 4, "reload count");
    expect(!loaded.find(a2->id), "reload dropped prior");
    const emulocke::Run* again = loaded.find(a3->id);
    expect(again && again->gameId == emulocke::GameId::FireRed, "reload game");
    expect(again && again->rules == emulocke::regularRules(), "reload rules");
    expect(again && again->attempt == 3, "reload attempt");
    expect(emulocke::resolveRomPath(*again, detected) == detected[1].romPath, "resolve existing");
    std::filesystem::remove_all(tmp);
    if (fails) {
        std::fprintf(stderr, "%d failed\n", fails);
        return 1;
    }
    std::printf("ok\n");
    return 0;
}