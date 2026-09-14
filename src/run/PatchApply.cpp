#include "run/PatchApply.hpp"

#include <mgba-util/patch.h>
#include <mgba-util/sha1.h>
#include <mgba-util/vfs.h>
#include <cstdio>
#include <memory>

namespace emulocke {
namespace {

struct VFileCloser {
    void operator()(VFile* vf) const { vf->close(vf); }
};
using VFilePtr = std::unique_ptr<VFile, VFileCloser>;

std::optional<std::vector<uint8_t>> applyMgbaPatch(
    std::span<const uint8_t> rom, std::span<const uint8_t> patch) {
    const VFilePtr vf(VFileFromConstMemory(patch.data(), patch.size()));
    if (!vf) {
        return std::nullopt;
    }
    Patch applied{};
    if (!loadPatch(vf.get(), &applied) || !applied.outputSize || !applied.applyPatch) {
        return std::nullopt;
    }
    const size_t outSize = applied.outputSize(&applied, rom.size());
    if (outSize == 0 || outSize > kMaxPatchedRom) {
        return std::nullopt;
    }
    std::vector<uint8_t> out(outSize);
    if (!applied.applyPatch(&applied, rom.data(), rom.size(), out.data(), outSize)) {
        return std::nullopt;
    }
    return out;
}

}  // namespace

std::string sha1Hex(std::span<const uint8_t> bytes) {
    uint8_t digest[20]{};
    sha1Buffer(bytes.data(), bytes.size(), digest);
    char hex[41]{};
    for (int i = 0; i < 20; ++i) {
        std::snprintf(hex + i * 2, 3, "%02x", digest[i]);
    }
    return hex;
}

std::optional<std::vector<uint8_t>> applyRomPatch(
    std::span<const uint8_t> rom, std::span<const uint8_t> patch) {
    if (rom.empty() || patch.empty()) {
        return std::nullopt;
    }
    if (patch.size() >= 4 && patch[0] == 'B' && patch[1] == 'P' && patch[2] == 'S' && patch[3] == '1') {
        return applyBpsPatch(rom, patch);
    }
    if (auto out = applyMgbaPatch(rom, patch)) {
        return out;
    }
    return applyXdeltaPatch(rom, patch);
}

}