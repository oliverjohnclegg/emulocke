#include "run/PatchApply.hpp"
#include "test/PatchChecks.hpp"
#include "test/PatchFixtures.hpp"

#include <cstdio>
#include <vector>

namespace {

using namespace emulocke::test;

int fails = 0;

void expectRejected(const std::vector<uint8_t>& src, const std::vector<uint8_t>& patch, const char* msg) {
    if (emulocke::applyBpsPatch(src, patch)) {
        std::fprintf(stderr, "FAIL accepted %s\n", msg);
        ++fails;
    }
}

std::vector<uint8_t> commands(const std::vector<uint8_t>& src, uint64_t targetSize,
                              const std::vector<uint64_t>& vlis) {
    auto patch = bpsHeader(src.size(), targetSize);
    for (const auto v : vlis) {
        writeVli(patch, v);
    }
    sealBps(patch, src, 0);
    return patch;
}

void checkHeaderBounds(const std::vector<uint8_t>& src) {
    std::vector<uint8_t> tenByteVli{'B', 'P', 'S', '1'};
    tenByteVli.insert(tenByteVli.end(), 12, 0x7f);
    sealBps(tenByteVli, src, 0);
    expectRejected(src, tenByteVli, "vli longer than ten bytes");

    expectRejected(src, commands(src, emulocke::kMaxPatchedRom + 1, {}), "target above cap");
    expectRejected(src, commands(src, uint64_t{1} << 62, {}), "target beyond addressable memory");
    expectRejected(src, commands(src, 0, {}), "empty target");

    auto hugeMeta = bpsHeader(src.size(), src.size(), ~uint64_t{0} - 8);
    sealBps(hugeMeta, src, 0);
    expectRejected(src, hugeMeta, "meta length wrapping past patch end");

    auto wrongSource = bpsHeader(src.size() + 1, src.size());
    sealBps(wrongSource, src, 0);
    expectRejected(src, wrongSource, "source size mismatch");
}

void checkCommandBounds(const std::vector<uint8_t>& src) {
    const uint64_t n = src.size();
    expectRejected(src, commands(src, n, {((n + 1 - 1) << 2) | 0}), "source read past target");
    expectRejected(src, commands(src, n + 4, {((n + 4 - 1) << 2) | 0}), "source read past source");
    expectRejected(src, commands(src, n, {((n - 1) << 2) | 1}), "target read past patch data");
    expectRejected(src, commands(src, n, {(0 << 2) | 2, (n << 1)}), "source copy offset past source");
    expectRejected(src, commands(src, n, {(0 << 2) | 2, (1 << 1) | 1}), "source copy negative offset underflow");
    expectRejected(src, commands(src, n, {((n - 1) << 2) | 2, ~uint64_t{0} & ~uint64_t{1}}),
                   "source copy offset near uint64 max");
    expectRejected(src, commands(src, n, {(0 << 2) | 3, 0}), "target copy before anything written");
    expectRejected(src, commands(src, n, {(0 << 2) | 0, (0 << 2) | 3, (1 << 1)}),
                   "target copy offset reaching the write head");
    expectRejected(src, commands(src, n, {((n - 2) << 2) | 0}), "short target");
    expectRejected(src, commands(src, n, {((n - 1) << 2) | 0}), "target crc mismatch");
}

}  // namespace

int testPatchBounds() {
    const std::vector<uint8_t> src{1, 2, 3, 4, 5, 6, 7, 8};
    checkHeaderBounds(src);
    checkCommandBounds(src);
    const std::vector<uint8_t> dst{1, 2, 9, 4, 5, 6, 7, 8};
    auto ok = emulocke::applyBpsPatch(src, makeBps(src, dst));
    if (!ok || *ok != dst) {
        std::fprintf(stderr, "FAIL valid bps still applies\n");
        ++fails;
    }
    return fails;
}
