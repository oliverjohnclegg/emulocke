#include "run/PatchApply.hpp"
#include "test/PatchChecks.hpp"

#include <mgba-util/crc32.h>
#include <algorithm>
#include <cstdio>
#include <vector>

extern "C" {
#include "xdelta3.h"
}

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

std::vector<uint8_t> makeIps(const std::vector<uint8_t>& src, const std::vector<uint8_t>& dst) {
    std::vector<uint8_t> patch{'P', 'A', 'T', 'C', 'H'};
    const size_t n = std::min(src.size(), dst.size());
    size_t i = 0;
    while (i < n) {
        if (src[i] == dst[i]) {
            ++i;
            continue;
        }
        const size_t start = i;
        while (i < n && src[i] != dst[i] && i - start < 0xffff) {
            ++i;
        }
        patch.push_back(static_cast<uint8_t>((start >> 16) & 0xff));
        patch.push_back(static_cast<uint8_t>((start >> 8) & 0xff));
        patch.push_back(static_cast<uint8_t>(start & 0xff));
        const uint16_t len = static_cast<uint16_t>(i - start);
        patch.push_back(static_cast<uint8_t>(len >> 8));
        patch.push_back(static_cast<uint8_t>(len));
        patch.insert(patch.end(), dst.begin() + static_cast<std::ptrdiff_t>(start),
            dst.begin() + static_cast<std::ptrdiff_t>(i));
    }
    patch.insert(patch.end(), {'E', 'O', 'F'});
    return patch;
}

std::vector<uint8_t> makeBps(const std::vector<uint8_t>& src, const std::vector<uint8_t>& dst) {
    std::vector<uint8_t> patch{'B', 'P', 'S', '1'};
    writeVli(patch, src.size());
    writeVli(patch, dst.size());
    writeVli(patch, 0);
    writeVli(patch, ((dst.size() - 1) << 2) | 1);
    patch.insert(patch.end(), dst.begin(), dst.end());
    writeLe32(patch, doCrc32(src.data(), src.size()));
    writeLe32(patch, doCrc32(dst.data(), dst.size()));
    writeLe32(patch, doCrc32(patch.data(), patch.size()));
    return patch;
}

std::vector<uint8_t> makeXdelta(const std::vector<uint8_t>& src, const std::vector<uint8_t>& dst) {
    std::vector<uint8_t> patch(1024);
    usize_t wrote = 0;
    const int rc = xd3_encode_memory(dst.data(), static_cast<usize_t>(dst.size()), src.data(),
        static_cast<usize_t>(src.size()), patch.data(), &wrote, static_cast<usize_t>(patch.size()), 0);
    if (rc != 0) {
        return {};
    }
    patch.resize(wrote);
    return patch;
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
    return fails;
}
