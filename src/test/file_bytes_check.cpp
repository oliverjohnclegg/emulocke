#include "emu/FileBytes.hpp"

#include <cstdio>
#include <filesystem>
#include <vector>

namespace {

int fails = 0;

void expect(bool cond, const char* msg) {
    if (!cond) {
        std::fprintf(stderr, "FAIL %s\n", msg);
        ++fails;
    }
}

}  // namespace

int testFileBytes() {
    const auto dir = std::filesystem::temp_directory_path() / "emulocke-file-bytes-check";
    std::filesystem::create_directories(dir);
    const auto path = (dir / "ten.bin").string();
    const std::vector<uint8_t> ten{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    expect(emulocke::writeWholeFile(path, ten.data(), ten.size()), "write ten bytes");
    expect(emulocke::readWholeFile(path, 10) == ten, "read at the cap");
    expect(emulocke::readWholeFile(path, emulocke::kMaxSaveFile) == ten, "read under the cap");
    expect(emulocke::readWholeFile(path, 9).empty(), "read above the cap returns nothing");
    expect(emulocke::readWholeFile((dir / "missing.bin").string(), 10).empty(), "missing file returns nothing");
    expect(emulocke::readWholeFile(dir.string(), 10).empty(), "directory returns nothing");
    expect(emulocke::writeWholeFile(dir / "via-path.bin", ten.data(), ten.size()), "write path overload");
    expect(emulocke::readWholeFile(dir / "via-path.bin", 10) == ten, "read path overload");
    std::filesystem::remove_all(dir);
    return fails;
}
