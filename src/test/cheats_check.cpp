#include "cheats/Book.hpp"
#include "cheats/Limits.hpp"
#include "cheats/Lines.hpp"
#include "cheats/Uuid.hpp"

#include "run/Catalog.hpp"

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iterator>
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

void testIdsAndParse() {
    expect(!emulocke::catalogUuidOk("../prefs.ini"), "slash uuid rejected");
    expect(!emulocke::catalogUuidOk("e8e92ba8-429b-55a0-b78d-2c269b6d2b56/../x"), "long uuid rejected");
    expect(!emulocke::catalogUuidOk("E8E92BA8-429B-55A0-B78D-2C269B6D2B56"), "upper uuid rejected");
    expect(emulocke::catalogUuidOk(emulocke::kFireRedUs10Uuid), "catalog uuid ok");
    expect(emulocke::cheatGamePath("../prefs.ini").empty(), "path traversal empty");

    std::vector<uint32_t> words;
    expect(emulocke::parseArWords("02000000 00000042\n# skip\n12000004 0000ABCD", words), "ar parse");
    expect(words.size() == 4 && words[0] == 0x02000000u && words[1] == 0x42u, "ar words");
    expect(!emulocke::parseArWords("not a code", words), "junk ar rejected");
    expect(!emulocke::parseArWords("", words), "empty ar rejected");
}

void testRoundtrip(const std::filesystem::path& tmp) {
    const auto fr = tmp / "fr.ini";
    const auto em = tmp / "em.ini";
    const auto run = tmp / "run.ini";

    emulocke::CheatBook book;
    expect(book.add("Walk Through Walls", "74000130 03BF\n82023D6C 1000"), "add wtw");
    expect(book.add("Rare Candy", "82024A7A 0044"), "add candy");
    expect(book.items().size() == 2, "two cheats");
    expect(book.items()[0].id == "c1" && book.items()[1].id == "c2", "stable ids");
    expect(!book.items()[0].enabled && !book.items()[1].enabled, "add starts off");
    expect(book.saveGame(fr), "save game");

    std::ifstream saved(fr);
    std::string blob((std::istreambuf_iterator<char>(saved)), std::istreambuf_iterator<char>());
    expect(blob.find("enabled") == std::string::npos, "no enabled in game file");
    expect(blob.find("Walk Through Walls") != std::string::npos, "name persisted");

    emulocke::CheatBook again;
    expect(again.loadGame(fr), "reload game");
    expect(again.items().size() == 2, "reload count");
    expect(!again.items()[0].enabled && !again.items()[1].enabled, "reload disabled");
    expect(again.setEnabled("c1", true), "enable c1");
    expect(again.saveEnabled(run), "save enabled");

    emulocke::CheatBook seated;
    expect(seated.loadGame(fr), "seat game");
    expect(seated.loadEnabled(run), "seat enabled");
    expect(seated.items()[0].enabled && !seated.items()[1].enabled, "c1 on c2 off");
    expect(seated.enabledSpecs().size() == 1, "one live spec");

    emulocke::CheatBook other;
    expect(other.add("Emerald only", "02000000 00000001"), "other game add");
    expect(other.saveGame(em), "save other");
    emulocke::CheatBook frAgain;
    frAgain.loadGame(fr);
    expect(frAgain.items().size() == 2, "games do not share");
    emulocke::CheatBook emAgain;
    emAgain.loadGame(em);
    expect(emAgain.items().size() == 1 && emAgain.items()[0].name == "Emerald only", "other game own list");

    emulocke::CheatBook freshRun;
    freshRun.loadGame(fr);
    freshRun.loadEnabled(tmp / "missing.ini");
    expect(freshRun.items().size() == 2 && !freshRun.items()[0].enabled, "missing enabled all off");

    {
        std::ofstream empty(tmp / "empty.ini", std::ios::trunc);
    }
    emulocke::CheatBook emptyOn;
    emptyOn.loadGame(fr);
    emptyOn.loadEnabled(tmp / "empty.ini");
    expect(emptyOn.items().size() == 2 && !emptyOn.items()[0].enabled, "empty enabled all off");

    {
        std::ofstream stale(run, std::ios::trunc);
        stale << "on=c1\non=c99\n";
    }
    emulocke::CheatBook ignore;
    ignore.loadGame(fr);
    ignore.loadEnabled(run);
    expect(ignore.items()[0].enabled && ignore.enabledSpecs().size() == 1, "unknown id ignored");
}

void testAdversary(const std::filesystem::path& tmp) {
    const auto huge = tmp / "huge.ini";
    {
        std::ofstream out(huge);
        out << std::string(emulocke::kMaxCheatFile + 1, 'A');
    }
    emulocke::CheatBook capped;
    expect(!capped.loadGame(huge) && capped.items().empty(), "huge file fail closed");

    const auto nameless = tmp / "nameless.ini";
    {
        std::ofstream out(nameless);
        out << "[c1]\ncode=02000000 00000001\n";
    }
    emulocke::CheatBook skip;
    expect(skip.loadGame(nameless) && skip.items().empty(), "missing name skipped");

    const auto longLine = tmp / "longline.ini";
    {
        std::ofstream out(longLine);
        out << "[c1]\nname=Big\ncode=" << std::string(emulocke::kMaxCheatLine + 1, 'A') << "\n";
    }
    emulocke::CheatBook over;
    expect(over.loadGame(longLine) && over.items().empty(), "oversize line skipped");

    const auto trunc = tmp / "trunc.ini";
    {
        std::ofstream out(trunc);
        out << "[c1]\nname=Tail\ncode=02000000 00000001";
    }
    emulocke::CheatBook tail;
    expect(tail.loadGame(trunc) && tail.items().size() == 1, "truncated last line kept");
    expect(tail.items()[0].name == "Tail", "truncated name");
}

}  // namespace

int testCheats() {
    testIdsAndParse();
    const auto tmp = std::filesystem::temp_directory_path() / "emulocke-cheats-check";
    std::filesystem::remove_all(tmp);
    std::filesystem::create_directories(tmp);
    testRoundtrip(tmp);
    testAdversary(tmp);
    std::filesystem::remove_all(tmp);
    return fails;
}
