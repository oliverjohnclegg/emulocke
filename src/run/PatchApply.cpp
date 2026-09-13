#include "run/PatchApply.hpp"

#include <mgba-util/patch.h>
#include <mgba-util/sha1.h>
#include <mgba-util/vfs.h>
#include <cstdio>

namespace emulocke {

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
    VFile* vf = VFileFromConstMemory(patch.data(), patch.size());
    if (vf) {
        Patch applied{};
        if (loadPatch(vf, &applied) && applied.outputSize && applied.applyPatch) {
            const size_t outSize = applied.outputSize(&applied, rom.size());
            if (outSize) {
                std::vector<uint8_t> out(outSize);
                const bool ok = applied.applyPatch(&applied, rom.data(), rom.size(), out.data(), outSize);
                vf->close(vf);
                if (ok) {
                    return out;
                }
                return applyXdeltaPatch(rom, patch);
            }
        }
        vf->close(vf);
    }
    return applyXdeltaPatch(rom, patch);
}

}