#include "adapter/gen4/Layout.hpp"
#include "adapter/gen45/Pk.hpp"
#include "adapter/gen5/Save.hpp"
#include "emu/FileBytes.hpp"
#include "fuzz/FuzzRom.hpp"
#include "test/PatchFixtures.hpp"
#include "test/snapshot_fixtures.hpp"

#include <cstdio>
#include <filesystem>
#include <span>
#include <vector>

namespace {

bool writeSeed(const std::filesystem::path& root, const char* target, const char* name,
               std::span<const uint8_t> bytes) {
    const auto dir = root / target;
    std::filesystem::create_directories(dir);
    const auto path = dir / name;
    if (bytes.empty() || !emulocke::writeWholeFile(path.string(), bytes.data(), bytes.size())) {
        std::fprintf(stderr, "could not write %s\n", path.string().c_str());
        return false;
    }
    return true;
}

std::vector<uint8_t> patchedRom() {
    auto rom = emulocke::fuzz::baseRom();
    for (std::size_t i = 0x100; i < 0x140; ++i) {
        rom[i] ^= 0xA5;
    }
    rom.resize(rom.size() + 64, 0xEE);
    return rom;
}

}  // namespace

int main(int argc, char** argv) {
    const std::filesystem::path root = argc > 1 ? argv[1] : "src/fuzz/corpus";
    const auto& rom = emulocke::fuzz::baseRom();
    const auto target = patchedRom();
    const auto dp = makeSuiteSav(SuiteSav::Dp);
    const auto bw = makeSuiteSav(SuiteSav::Gen5);
    const std::span<const uint8_t> pk4 = std::span(dp).subspan(emulocke::dpLayout().partyOff, emulocke::kPk4PartySize);
    const std::span<const uint8_t> pk5 = std::span(bw).subspan(emulocke::kGen5Party + 8, emulocke::kPk5PartySize);
    bool ok = true;
    ok &= writeSeed(root, "fuzz_bps", "grow", emulocke::test::makeBps(rom, target));
    ok &= writeSeed(root, "fuzz_xdelta", "grow", emulocke::test::makeXdelta(rom, target));
    ok &= writeSeed(root, "fuzz_ips", "ips", emulocke::test::makeIps(rom, target));
    ok &= writeSeed(root, "fuzz_ips", "bps", emulocke::test::makeBps(rom, target));
    ok &= writeSeed(root, "fuzz_gen3_save", "frlg", makeSuiteSav(SuiteSav::Frlg));
    ok &= writeSeed(root, "fuzz_gen3_save", "rse", makeSuiteSav(SuiteSav::Rse));
    ok &= writeSeed(root, "fuzz_gen4_save", "dp", dp);
    ok &= writeSeed(root, "fuzz_gen4_save", "pt", makeSuiteSav(SuiteSav::Pt));
    ok &= writeSeed(root, "fuzz_gen4_save", "hgss", makeSuiteSav(SuiteSav::Hgss));
    ok &= writeSeed(root, "fuzz_gen5_save", "bw", bw);
    ok &= writeSeed(root, "fuzz_pk45", "pk4", pk4);
    ok &= writeSeed(root, "fuzz_pk45", "pk5", pk5);
    return ok ? 0 : 1;
}
