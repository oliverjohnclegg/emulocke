#include "emu/FileBytes.hpp"
#include "run/Catalog.hpp"
#include "run/NuzlockeRules.hpp"
#include "run/PatchApply.hpp"
#include "run/RomLibrary.hpp"
#include "run/RunLabel.hpp"
#include "run/RunMeta.hpp"
#include "run/RunStore.hpp"

#include <mgba-util/crc32.h>
#include <cstdio>
#include <cstring>
#include <filesystem>
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

    expect(emulocke::catalogTitles().size() == 18, "catalog size");

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
    expect(emulocke::runHeadline(*a) == "Pokemon Fire Red: Regular Nuzlocke  |  Attempt #1", "headline");
    auto a2 = store.createAttempt(*a);
    expect(a2 && a2->attempt == 2 && !store.find(a->id), "replace attempt");
    expect(store.byCatalogUuid(emulocke::kFireRedUs10Uuid).size() == 2, "two lineages");

    const char* kLeafGreen = "9f374685-6339-5285-a9e9-7953afa9802b";
    auto lg = store.create(kLeafGreen, emulocke::regularRules());
    expect(lg.has_value(), "create leaf green");
    emulocke::Run* older = store.find(lg->id);
    emulocke::Run* newer = store.find(a2->id);
    emulocke::Run* mid = store.find(b->id);
    expect(older && newer && mid, "find lineages");
    older->lastPlayedAt = "2020-01-01T00:00:00Z";
    mid->lastPlayedAt = "2024-06-01T00:00:00Z";
    newer->lastPlayedAt = "2026-12-31T00:00:00Z";
    expect(emulocke::writeRunMeta(runs / older->id, *older), "stamp lg");
    expect(emulocke::writeRunMeta(runs / mid->id, *mid), "stamp hardcore");
    expect(emulocke::writeRunMeta(runs / newer->id, *newer), "stamp fr");
    const auto recent = store.recentLineages();
    expect(recent.size() == 3, "three lineages");
    expect(recent[0]->id == newer->id, "last played first");
    expect(recent[0]->catalogUuid == emulocke::kFireRedUs10Uuid, "fr not catalog-grouped");
    expect(recent.back()->id == older->id, "oldest last");

    emulocke::RunStore loaded(runs);
    loaded.load();
    const emulocke::Run* againRun = loaded.find(a2->id);
    expect(againRun && againRun->catalogUuid == emulocke::kFireRedUs10Uuid, "reload uuid");
    expect(againRun && againRun->attempt == 2, "reload attempt");

    std::filesystem::remove_all(tmp);
    if (fails) {
        std::fprintf(stderr, "%d failed\n", fails);
        return 1;
    }
    std::printf("ok\n");
    return 0;
}