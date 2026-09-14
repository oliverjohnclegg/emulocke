#include "emu/FileBytes.hpp"
#include "run/Catalog.hpp"
#include "run/PatchApply.hpp"
#include "test/PatchChecks.hpp"

#include <cstdlib>
#include <cstdio>
#include <filesystem>
#include <string>

namespace {

std::filesystem::path patchesDir() {
    if (std::filesystem::exists("assets/patches")) {
        return "assets/patches";
    }
    if (std::filesystem::exists("../assets/patches")) {
        return "../assets/patches";
    }
    return {};
}

void applyIfPresent(const std::filesystem::path& romPath, const std::filesystem::path& patchPath, int& fails) {
    if (!std::filesystem::exists(romPath) || !std::filesystem::exists(patchPath)) {
        return;
    }
    const auto rom = emulocke::readWholeFile(romPath.string(), emulocke::kMaxRomFile);
    const auto patch = emulocke::readWholeFile(patchPath.string(), emulocke::kMaxPatchFile);
    auto out = emulocke::applyRomPatch(rom, patch);
    if (!out || out->empty()) {
        std::fprintf(stderr, "FAIL local patch %s\n", patchPath.filename().string().c_str());
        ++fails;
        return;
    }
    std::fprintf(stderr, "patched %s -> %zu bytes\n", patchPath.filename().string().c_str(), out->size());
}

}  // namespace

int testLocalPatches() {
    const char* home = std::getenv("HOME");
    const auto patches = patchesDir();
    if (!home || patches.empty()) {
        return 0;
    }
    const std::filesystem::path roms = std::filesystem::path(home) / "test_roms";
    int fails = 0;
    const struct {
        const char* rom;
        const char* uuid;
        const char* option;
    } cases[] = {
        {"fire_red-1_0_squirrels-U.gba", emulocke::kRadicalRedUuid, ""},
        {"fire_red-1_0_squirrels-U.gba", emulocke::kUnboundUuid, ""},
        {"fire_red-1_0_squirrels-U.gba", "8527a185-3f81-585d-8f7c-579ae609d3c5", ""},
        {"emerald-U.gba", "06639a36-2636-5be7-a9ea-8b297df14269", ""},
        {"emerald-U.gba", "18855d7c-7171-59e2-82fd-03836a5b2f1c", ""},
        {"emerald-U.gba", "7d2136c6-bcbb-5764-ac94-f43f2d87dc1d", ""},
        {"heartgold-U.nds", "3f9719ca-e87f-5424-aa02-af7865e10deb", ""},
        {"platinum-U.nds", "d8ae6094-3a98-5ce5-8be5-fe1c4ed9c252", ""},
        {"platinum-U.nds", "be106054-eaa8-54b2-9f58-0fd1e948031e", ""},
        {"black-U.nds", emulocke::kBlazeBlackUuid, "full"},
        {"black-U.nds", emulocke::kBlazeBlackUuid, "clean"},
    };
    for (const auto& c : cases) {
        const emulocke::CatalogTitle* title = emulocke::catalogByUuid(c.uuid);
        if (!title) {
            continue;
        }
        const char* asset = emulocke::catalogPatchAsset(*title, c.option);
        applyIfPresent(roms / c.rom, patches / std::filesystem::path(asset ? asset : "").filename(), fails);
    }
    const auto unboundSav = roms / "rom_hack_patches" / "Pokemon Unbound.sav";
    if (std::filesystem::exists(unboundSav)) {
        std::fprintf(stderr, "note: Unbound.sav present; CFRU parse is a later pass\n");
    }
    return fails;
}
