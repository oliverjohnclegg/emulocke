#include "emu/FileBytes.hpp"
#include "run/Catalog.hpp"
#include "run/PatchApply.hpp"
#include "test/PatchChecks.hpp"
#include "test/PatchFixtures.hpp"

#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <new>
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
    auto relaxed = emulocke::applyRomPatch(wrongSrc, bigPatch);
    expect(relaxed && relaxed->size() == bigDst.size(),
        "rom patch still applies when the window checksum fails");
    const std::vector<uint8_t> hugeApp{0xd6, 0xc3, 0xc4, 0x00, 0x04, 0xf2, 0xfb, 0xc0, 0xc9, 0xd6,
        0xdf, 0x24, 0x2d, 0x2a, 0x33, 0x38, 0x01, 0xc4, 0x00, 0x00, 0x05, 0xa0, 0x00, 0x00, 0x5c,
        0xa0, 0x40, 0x00, 0x41, 0x5c, 0xa0, 0x0d, 0x40, 0x04};
    expect(!emulocke::applyXdeltaPatch(src, hugeApp), "xdelta rejects a huge VCDIFF app header");

    const emulocke::CatalogTitle* blaze = emulocke::catalogByUuid(emulocke::kBlazeBlackUuid);
    const char* asset = blaze ? emulocke::catalogPatchAsset(*blaze, "full") : nullptr;
    std::filesystem::path patchPath;
    if (asset) {
        for (const char* root : {"assets", "../assets"}) {
            const auto cand = std::filesystem::path(root) / asset;
            if (std::filesystem::exists(cand)) {
                patchPath = cand;
                break;
            }
        }
    }
    if (!patchPath.empty()) {
        const auto patch = emulocke::readWholeFile(patchPath, emulocke::kMaxPatchFile);
        expect(!patch.empty(), "blaze black xdelta readable");
        constexpr std::size_t kNdsDump = std::size_t{256} << 20;
        std::vector<uint8_t> dummy;
        try {
            dummy.resize(kNdsDump);
        } catch (const std::bad_alloc&) {
            std::fprintf(stderr, "skip blaze black dummy: no memory\n");
            return fails;
        }
        expect(!emulocke::applyXdeltaPatch(dummy, patch), "blaze black dummy fails Adler32");
        const auto out = emulocke::applyRomPatch(dummy, patch);
        expect(out && out->size() == kNdsDump, "blaze black dummy still patches");
        if (out && out->size() == kNdsDump) {
            std::fprintf(stderr, "patched blaze-black dummy -> %zu bytes\n", out->size());
        }
    }
    return fails;
}
