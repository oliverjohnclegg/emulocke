#include "application/Prefs.hpp"
#include "emu/FileBytes.hpp"
#include "run/Catalog.hpp"
#include "ui/Layout.hpp"
#include "run/NuzlockeRules.hpp"
#include "run/PatchApply.hpp"
#include "run/RomLibrary.hpp"
#include "run/RunLabel.hpp"
#include "run/RunMeta.hpp"
#include "run/RunStore.hpp"
#include "run/TitlePlay.hpp"

#include "test/PatchChecks.hpp"

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

int testLayout();

int main() {
    expect(static_cast<int>(emulocke::kRightPaneSpan) == 481, "right pane span");
    expect(emulocke::widthAfterRightPaneToggle(emulocke::kDefaultWindowW, false) == 554, "hide shrinks");
    expect(emulocke::widthAfterRightPaneToggle(554, true) == emulocke::kDefaultWindowW, "show grows");
    expect(emulocke::Prefs{}.rightPane, "right pane default");
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

    expect(emulocke::catalogTitles().size() == 30, "catalog size");
    expect(!emulocke::catalogBySlug("storm-silver"), "no storm silver");
    expect(!emulocke::catalogBySlug("blaze-black-2-redux"), "no bb2r");
    const char* hackSlugs[] = {"blaze-black-3.1", "volt-white-3.1", "volt-white-2-redux", "fire-red-omega",
        "sacred-gold", "platinum-kaizo", "renegade-platinum", "radical-red-4.1", "unbound-2.1.1.1",
        "run-and-bun-1.07", "inclement-emerald-1.13", "emerald-kaizo"};
    for (const char* slug : hackSlugs) {
        expect(emulocke::catalogBySlug(slug) != nullptr, slug);
    }
    expect(emulocke::catalogOptionId(*emulocke::catalogByUuid(emulocke::kBlazeBlackUuid), {}) == "full",
        "bb default");
    expect(emulocke::catalogOptionId(*emulocke::catalogByUuid(emulocke::kVoltWhiteUuid), {}) == "full",
        "vw default");
    expect(emulocke::catalogBySlug("volt-white-2-redux")->optionCount == 0, "vw2 no options");
    expect(std::strcmp(emulocke::catalogByUuid(emulocke::kBlazeBlackUuid)->prerequisiteUuid,
               emulocke::kBlackUsUuid) == 0,
        "bb prereq");
    expect(std::strcmp(emulocke::catalogByUuid(emulocke::kVoltWhiteUuid)->prerequisiteUuid,
               emulocke::kWhiteUsUuid) == 0,
        "vw prereq");
    expect(std::strcmp(emulocke::catalogBySlug("volt-white-2-redux")->prerequisiteUuid,
               emulocke::kWhite2UsUuid) == 0,
        "vw2 prereq");
    expect(std::strcmp(emulocke::catalogBySlug("sacred-gold")->prerequisiteUuid, emulocke::kHeartGoldUsUuid) ==
            0,
        "sg prereq");
    expect(std::strcmp(emulocke::catalogBySlug("platinum-kaizo")->prerequisiteUuid,
               emulocke::kPlatinumUs11Uuid) == 0,
        "pk prereq");
    expect(std::strcmp(emulocke::catalogBySlug("renegade-platinum")->prerequisiteUuid,
               emulocke::kPlatinumUs11Uuid) == 0,
        "rp prereq");
    expect(std::strcmp(emulocke::catalogBySlug("fire-red-omega")->prerequisiteUuid,
               emulocke::kFireRedUs10Uuid) == 0,
        "fro prereq");
    expect(std::strcmp(emulocke::catalogBySlug("run-and-bun-1.07")->prerequisiteUuid,
               emulocke::kEmeraldUsUuid) == 0,
        "rab prereq");
    expect(std::strcmp(emulocke::catalogBySlug("inclement-emerald-1.13")->prerequisiteUuid,
               emulocke::kEmeraldUsUuid) == 0,
        "ie prereq");
    expect(std::strcmp(emulocke::catalogBySlug("emerald-kaizo")->prerequisiteUuid, emulocke::kEmeraldUsUuid) ==
            0,
        "ek prereq");
    expect(std::string(emulocke::catalogByUuid(emulocke::kFireRedUs10Uuid)->artSlug) == "firered", "fr art");
    expect(std::string(emulocke::catalogByUuid(emulocke::kFireRedUs10Uuid)->version) == "1.0", "fr version");
    expect(std::string(emulocke::catalogByUuid(emulocke::kFireRedUs10Uuid)->details) == "US", "fr region");
    expect(emulocke::catalogListTitle(*emulocke::catalogByUuid(emulocke::kFireRedUs10Uuid)) ==
            "FIRE RED (1.0)",
        "fr list title");
    expect(std::string(emulocke::catalogByUuid(emulocke::kUnboundUuid)->artSlug) == "unbound", "unbound art");
    expect(std::string(emulocke::catalogByUuid(emulocke::kUnboundUuid)->details) == "US", "unbound region");
    expect(emulocke::catalogListTitle(*emulocke::catalogByUuid(emulocke::kUnboundUuid)) ==
            "UNBOUND (2.1.1.1)",
        "unbound list title");
    const emulocke::CatalogTitle* fr11 = emulocke::catalogBySlug("firered-us-1.1");
    expect(fr11 && emulocke::catalogListTitle(*fr11) == "FIRE RED (1.1)", "fr11 list title");
    expect(emulocke::catalogVersionCompare("1.1", "1.0") > 0, "1.1 > 1.0");
    expect(emulocke::catalogVersionCompare("2.1.1.1", "4.1") < 0, "2.1.1.1 < 4.1");
    const auto picker = emulocke::catalogPickerRows();
    const emulocke::CatalogTitle* firstFr = nullptr;
    const emulocke::CatalogTitle* secondFr = nullptr;
    for (const emulocke::CatalogTitle* title : picker) {
        if (std::string(title->artSlug) != "firered") {
            continue;
        }
        if (!firstFr) {
            firstFr = title;
        } else if (!secondFr) {
            secondFr = title;
        }
    }
    expect(firstFr && std::string(firstFr->version) == "1.1", "picker fr 1.1 first");
    expect(secondFr && std::string(secondFr->version) == "1.0", "picker fr 1.0 second");
    expect(emulocke::catalogListTitle(*emulocke::catalogBySlug("ruby-us")) == "RUBY (Rev 2)", "ruby list");
    expect(emulocke::catalogListTitle(*emulocke::catalogBySlug("emerald-us")) == "EMERALD", "emerald list");
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
    const emulocke::CatalogTitle* fr = emulocke::catalogByUuid(emulocke::kFireRedUs10Uuid);
    const emulocke::CatalogTitle* rr = emulocke::catalogByUuid(emulocke::kRadicalRedUuid);
    expect(!lib.ready(*fr), "fr not ready");
    expect(!lib.ready(*rr), "rr not ready");
    auto gated = lib.ensurePlayable(emulocke::kRadicalRedUuid);
    expect(!gated, "rr without prereq");
    expect(lib.lastError().find("Import") != std::string::npos, "prereq gate");

    expect(lib.writeBaseline(*fr, src), "store baseline");
    expect(lib.has(emulocke::kFireRedUs10Uuid), "has fr");
    expect(lib.ready(*fr), "fr ready");
    expect(lib.ready(*rr), "rr ready with prereq");
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

    const emulocke::CatalogTitle* black = emulocke::catalogByUuid(emulocke::kBlackUsUuid);
    expect(lib.writeBaseline(*black, src), "store black");
    std::vector<uint8_t> cleanDst{1, 9, 3, 4, 5};
    const char* fullAsset = emulocke::catalogPatchAsset(*emulocke::catalogByUuid(emulocke::kBlazeBlackUuid), "full");
    const char* cleanAsset = emulocke::catalogPatchAsset(*emulocke::catalogByUuid(emulocke::kBlazeBlackUuid), "clean");
    auto fullUps = makeUps(src, dst);
    auto cleanUps = makeUps(src, cleanDst);
    emulocke::writeWholeFile((assets / fullAsset).string(), fullUps.data(), static_cast<uint32_t>(fullUps.size()));
    emulocke::writeWholeFile(
        (assets / cleanAsset).string(), cleanUps.data(), static_cast<uint32_t>(cleanUps.size()));
    auto fullRom = lib.ensurePlayable(emulocke::kBlazeBlackUuid, "full");
    auto cleanRom = lib.ensurePlayable(emulocke::kBlazeBlackUuid, "clean");
    expect(fullRom && cleanRom && *fullRom != *cleanRom, "bb options split");
    expect(fullRom && fullRom->filename().string().find("-full") != std::string::npos, "bb full name");
    auto defRom = lib.ensurePlayable(emulocke::kBlazeBlackUuid, {});
    expect(defRom && fullRom && *defRom == *fullRom, "bb default full");
    auto fullAgain = lib.ensurePlayable(emulocke::kBlazeBlackUuid, "full");
    auto cleanAgain = lib.ensurePlayable(emulocke::kBlazeBlackUuid, "clean");
    expect(fullAgain && fullRom && *fullAgain == *fullRom, "bb full reuse");
    expect(cleanAgain && cleanRom && *cleanAgain == *cleanRom, "bb clean reuse");

    emulocke::RunStore optionStore(tmp / "option_runs");
    auto optRun = optionStore.create(emulocke::kBlazeBlackUuid, emulocke::regularRules(), "clean");
    expect(optRun && optRun->patchOption == "clean", "store option");
    {
        emulocke::RunStore reloadOpts(tmp / "option_runs");
        reloadOpts.load();
        expect(reloadOpts.find(optRun->id) && reloadOpts.find(optRun->id)->patchOption == "clean",
            "reload option");
    }

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
    expect(emulocke::formatPlayClock(0) == "00:00", "clock 0");
    expect(emulocke::formatPlayClock(59999) == "00:00", "clock under minute");
    expect(emulocke::formatPlayClock(60000) == "00:01", "clock 1 min");
    expect(emulocke::formatPlayClock(9ull * 60000ull) == "00:09", "clock 9 min");
    expect(emulocke::formatPlayClock(3599999) == "00:59", "clock 59 min");
    expect(emulocke::formatPlayClock(3600000) == "01:00", "clock 1 hour");
    expect(emulocke::formatPlayClock(3750000) == "01:02", "clock 1h2m");
    expect(emulocke::formatPlayClock(100ull * 3600000ull) == "100:00", "clock 100h");
    expect(store.addPlayMs(a->id, 1500), "add play");
    expect(store.find(a->id) && store.find(a->id)->playMs == 1500, "play ms");
    expect(emulocke::formatPlayClock(store.find(a->id)->playMs) == "00:00", "clock 1.5s");
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
    fails += testPatchFormats();
    fails += testLocalPatches();
    fails += testLayout();
    if (fails) {
        std::fprintf(stderr, "%d failed\n", fails);
        return 1;
    }
    std::printf("ok\n");
    return 0;
}