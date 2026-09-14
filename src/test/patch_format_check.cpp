#include "run/PatchApply.hpp"
#include "test/PatchChecks.hpp"
#include "test/PatchFixtures.hpp"

#include <algorithm>
#include <cstdio>
#include <vector>

namespace {

using namespace emulocke::test;

int fails = 0;

void expect(bool cond, const char* msg) {
    if (!cond) {
        std::fprintf(stderr, "FAIL %s\n", msg);
        ++fails;
    }
}

}  // namespace

int testPatchFormats() {
    std::vector<uint8_t> src{1, 2, 3, 4, 5};
    std::vector<uint8_t> dst{1, 2, 9, 4, 5};
    auto ips = emulocke::applyRomPatch(src, makeIps(src, dst));
    expect(ips && ips->size() >= dst.size() && std::equal(dst.begin(), dst.end(), ips->begin()), "ips apply");
    auto bps = emulocke::applyRomPatch(src, makeBps(src, dst));
    expect(bps && *bps == dst, "bps apply");
    auto xdelta = makeXdelta(src, dst);
    expect(!xdelta.empty(), "xdelta encode");
    auto xd = emulocke::applyRomPatch(src, xdelta);
    expect(xd && *xd == dst, "xdelta apply");

    std::vector<uint8_t> bigSrc(4096);
    for (size_t i = 0; i < bigSrc.size(); ++i) {
        bigSrc[i] = static_cast<uint8_t>((i * 2654435761u) >> 13);
    }
    auto bigDst = bigSrc;
    bigDst[100] ^= 0xff;
    auto bigPatch = makeXdelta(bigSrc, bigDst);
    auto bigOut = emulocke::applyXdeltaPatch(bigSrc, bigPatch);
    expect(bigOut && *bigOut == bigDst, "xdelta applies with source copies");
    auto wrongSrc = bigSrc;
    wrongSrc[2000] ^= 0xff;
    expect(!emulocke::applyXdeltaPatch(wrongSrc, bigPatch), "xdelta rejects a source whose target checksum fails");
    const std::vector<uint8_t> hugeApp{0xd6, 0xc3, 0xc4, 0x00, 0x04, 0xf2, 0xfb, 0xc0, 0xc9, 0xd6,
        0xdf, 0x24, 0x2d, 0x2a, 0x33, 0x38, 0x01, 0xc4, 0x00, 0x00, 0x05, 0xa0, 0x00, 0x00, 0x5c,
        0xa0, 0x40, 0x00, 0x41, 0x5c, 0xa0, 0x0d, 0x40, 0x04};
    expect(!emulocke::applyXdeltaPatch(src, hugeApp), "xdelta rejects a huge VCDIFF app header");
    return fails;
}
