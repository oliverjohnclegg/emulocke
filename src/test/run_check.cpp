#include "emu/FileBytes.hpp"
#include "run/Catalog.hpp"
#include "run/NuzlockeRules.hpp"
#include "run/PatchApply.hpp"
#include "run/RomLibrary.hpp"
#include "run/RunLabel.hpp"
#include "run/RunMeta.hpp"
#include "run/RunStore.hpp"
#include "run/TitlePlay.hpp"

#include <mgba-util/crc32.h>
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

void writeVli(std::vector<uint8_t>& out, uint64_t value) {
    while (true) {
        uint8_t x = static_cast<uint8_t>(value & 0x7f);
        value >>= 7;
        if (value == 0) {
            out.push_back(static_cast<uint8_t>(x | 0x80));
            return;
        }
        out.push_back(x);
        value--;
    }
}

void writeLe32(std::vector<uint8_t>& out, uint32_t v) {
    out.push_back(static_cast<uint8_t>(v));
    out.push_back(static_cast<uint8_t>(v >> 8));
    out.push_back(static_cast<uint8_t>(v >> 16));
    out.push_back(static_cast<uint8_t>(v >> 24));
}

std::vector<uint8_t> makeUps(const std::vector<uint8_t>& src, const std::vector<uint8_t>& dst) {
    std::vector<uint8_t> patch{'U', 'P', 'S', '1'};
    writeVli(patch, src.size());
    writeVli(patch, dst.size());
    size_t i = 0;
    while (i < src.size() || i < dst.size()) {
        size_t start = i;
        while (i < src.size() && i < dst.size() && src[i] == dst[i]) {
            ++i;
        }
        writeVli(patch, i - start);
        while (i < dst.size() && (i >= src.size() || src[i] != dst[i])) {
            const uint8_t a = i < src.size() ? src[i] : 0;
            const uint8_t b = dst[i];
            const uint8_t x = static_cast<uint8_t>(a ^ b);
            if (x == 0) {
                break;
            }
            patch.push_back(x);
            ++i;
        }
        patch.push_back(0);
        ++i;
    }
    writeLe32(patch, doCrc32(src.data(), src.size()));
    writeLe32(patch, doCrc32(dst.data(), dst.size()));
    writeLe32(patch, doCrc32(patch.data(), patch.size()));
    return patch;
}

}  // namespace

int main() {
    expect(emulocke::catalogBySha1("41cb23d8dccc8ebd7c649cd8fbb58eeace6e2fdc") ==
            emulocke::catalogBySlug("firered-us-1.0"),
        "fr 1.0 sha");
    expect(emulocke::catalogByUuid(emulocke::kUnboundUuid)->kind == emulocke::TitleKind::Hack, "unbound hack");
    expect(std::strcmp(emulocke::catalogByUuid(emulocke::kUnboundUuid)->prerequisiteUuid,
               emulocke::kFireRedUs10Uuid) == 0,
        "unbound prereq");
    const std::string abc = "abc";
    expect(emulocke::sha1Hex({reinterpret_cast<const uint8_t*>(abc.data()), abc.size()}) ==
            "a9993e364706816aba3e25717850c26c9cd0d89d",
        "sha1 abc");

    std::vector<uint8_t> src{1, 2, 3, 4, 5};
    std::vector<uint8_t> dst{1, 2, 9, 4, 5};
    auto patched = emulocke::applyRomPatch(src, makeUps(src, dst));
    expect(patched && *patched == dst, "ups apply");

    expect(std::string(emulocke::rulesLabel(emulocke::regularRules())) == "REGULAR", "regular");
    expect(std::string(emulocke::rulesLabel(emulocke::hardcoreRules())) == "HARDCORE", "hardcore");

    expect(emulocke::catalogTitles().size() == 20, "catalog size");
    expect(std::string(emulocke::catalogBySha1("66d2fbfb0dbc1f86a3d726971196989b950092bc")->slug) ==
            "diamond-us",
        "diamond 1.13 alias");
    expect(std::string(emulocke::catalogBySha1("5da09a39424f1a76c52a3eebad9b5e8dcacb71ba")->slug) ==
            "black2-us",
        "black2 alias");
    expect(std::string(emulocke::catalogBySha1("610b96a9c9a7d03d2bafb655e7560ccff1a6d894")->slug) ==
            "ruby-us-1.1",
        "ruby 1.1");
    expect(std::string(emulocke::catalogBySha1("0862ec35b24de5c7e2dcb88c9eea0873110d755c")->slug) ==
            "platinum-us-1.1",
        "platinum 1.1");
    expect(std::string(emulocke::catalogBySlug("black-us")->code) == "IRBO", "black code");
    expect(std::string(emulocke::catalogBySlug("white-us")->code) == "IRAO", "white code");
    expect(emulocke::catalogBySlug("diamond-us")->revision == 5, "diamond rev");

    const auto tmp = std::filesystem::temp_directory_path() / "emulocke_rom_library_test";
    std::filesystem::remove_all(tmp);
    const auto roms = tmp / "roms";
    const auto assets = tmp / "assets";
    const auto runs = tmp / "runs";
    std::filesystem::create_directories(assets / "patches");
    emulocke::RomLibrary lib(roms, assets);
    const auto junk = tmp / "junk.gba";
    emulocke::writeWholeFile(junk.string(), src.data(), static_cast<uint32_t>(src.size()));
    auto imported = lib.importFile(junk);
    expect(!imported.ok, "reject unknown");

    bool sawFr = false;
    bool sawRr = false;
    bool sawUnbound = false;
    for (const emulocke::CatalogTitle* title : lib.playableTitles()) {
        sawFr = sawFr || title->uuid == std::string(emulocke::kFireRedUs10Uuid);
        sawRr = sawRr || title->uuid == std::string(emulocke::kRadicalRedUuid);
        sawUnbound = sawUnbound || title->uuid == std::string(emulocke::kUnboundUuid);
    }
    expect(!sawFr && sawRr && sawUnbound, "hacks listed without import");
    expect(!lib.has(emulocke::kFireRedUs10Uuid), "no fr yet");
    auto gated = lib.ensurePlayable(emulocke::kRadicalRedUuid);
    expect(!gated, "rr without prereq");
    expect(lib.lastError().find("prerequisite") != std::string::npos, "prereq gate");

    const emulocke::CatalogTitle* fr = emulocke::catalogByUuid(emulocke::kFireRedUs10Uuid);
    expect(lib.writeBaseline(*fr, src), "store baseline");
    expect(lib.has(emulocke::kFireRedUs10Uuid), "has fr");
    expect(std::filesystem::path(lib.storedPath(*fr)).filename() ==
            (std::string(emulocke::kFireRedUs10Uuid) + ".gba"),
        "uuid filename");

    auto missingHack = lib.ensurePlayable(emulocke::kUnboundUuid);
    expect(!missingHack, "hack without patch");
    expect(lib.lastError().find("Patch") != std::string::npos, "missing patch copy");

    const auto patchPath = assets / "patches" / (std::string(emulocke::kUnboundUuid) + ".ups");
    auto ups = makeUps(src, dst);
    emulocke::writeWholeFile(patchPath.string(), ups.data(), static_cast<uint32_t>(ups.size()));
    auto derived = lib.ensurePlayable(emulocke::kUnboundUuid);
    expect(derived.has_value(), "ensure unbound");
    auto again = lib.ensurePlayable(emulocke::kUnboundUuid);
    expect(again && *again == *derived, "reuse derived");
    auto bytes = emulocke::readWholeFile(derived->string());
    expect(bytes == dst, "derived bytes");

    const auto playable = lib.playableTitles();
    sawFr = false;
    sawUnbound = false;
    for (const emulocke::CatalogTitle* title : playable) {
        sawFr = sawFr || title->uuid == std::string(emulocke::kFireRedUs10Uuid);
        sawUnbound = sawUnbound || title->uuid == std::string(emulocke::kUnboundUuid);
    }
    expect(sawFr && sawUnbound, "playable list");

    emulocke::RunStore store(runs);
    auto a = store.create(emulocke::kFireRedUs10Uuid, emulocke::regularRules());
    auto b = store.create(emulocke::kFireRedUs10Uuid, emulocke::hardcoreRules());
    expect(a && b, "create runs");
    expect(a && a->playMs == 0, "new play 0");
    expect(emulocke::runHeadline(*a) == "Pokemon Fire Red: Regular Nuzlocke  |  Attempt #1", "headline");
    expect(store.addPlayMs(a->id, 1500), "add play");
    expect(store.find(a->id) && store.find(a->id)->playMs == 1500, "play ms");
    {
        emulocke::RunStore check(runs);
        check.load();
        expect(check.find(a->id) && check.find(a->id)->playMs == 1500, "reload play");
    }

    const auto playFile = tmp / "playtime.ini";
    emulocke::TitlePlay titlePlay(playFile);
    expect(titlePlay.get(emulocke::kFireRedUs10Uuid) == 0, "title 0");
    expect(titlePlay.add(emulocke::kFireRedUs10Uuid, 4000), "title add");
    expect(titlePlay.get(emulocke::kFireRedUs10Uuid) == 4000, "title 4s");
    emulocke::TitlePlay reloadedPlay(playFile);
    expect(reloadedPlay.get(emulocke::kFireRedUs10Uuid) == 4000, "title reload");

    auto a2 = store.createAttempt(*store.find(a->id));
    expect(a2 && a2->attempt == 2 && !store.find(a->id), "replace attempt");
    expect(a2 && a2->playMs == 0, "attempt play 0");
    emulocke::TitlePlay afterAttempt(playFile);
    expect(afterAttempt.get(emulocke::kFireRedUs10Uuid) == 4000, "title after attempt");
    expect(store.addPlayMs(b->id, 250), "other add play");
    expect(store.byCatalogUuid(emulocke::kFireRedUs10Uuid).size() == 2, "two lineages");

    emulocke::RunStore loaded(runs);
    loaded.load();
    const emulocke::Run* againRun = loaded.find(a2->id);
    expect(againRun && againRun->catalogUuid == emulocke::kFireRedUs10Uuid, "reload uuid");
    expect(againRun && againRun->attempt == 2, "reload attempt");
    expect(againRun && againRun->playMs == 0, "reload play 0");
    expect(loaded.find(b->id) && loaded.find(b->id)->playMs == 250, "other run play");

    const auto legacyDir = runs / "0123456789abcdef";
    std::filesystem::create_directory(legacyDir);
    {
        std::ofstream out(legacyDir / "meta.ini");
        out << "game=" << emulocke::kFireRedUs10Uuid << "\n";
        out << "lineageId=0123456789abcdef\n";
        out << "attempt=1\n";
        out << "firstEncounter=1\n";
        out << "nicknames=1\n";
        out << "faintIsDeath=1\n";
        out << "setMode=0\n";
        out << "noItemsInBattle=0\n";
        out << "levelCap=0\n";
        out << "dupesClause=1\n";
        out << "shinyClause=1\n";
        out << "createdAt=2026-01-01T00:00:00Z\n";
        out << "lastPlayedAt=2026-01-01T00:00:00Z\n";
    }
    loaded.load();
    const emulocke::Run* legacyRun = loaded.find("0123456789abcdef");
    expect(legacyRun && legacyRun->playMs == 0, "legacy play 0");

    std::filesystem::remove_all(tmp);
    if (fails) {
        std::fprintf(stderr, "%d failed\n", fails);
        return 1;
    }
    std::printf("ok\n");
    return 0;
}