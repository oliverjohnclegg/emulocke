#include "run/PatchApply.hpp"

extern "C" {
#include "xdelta3.h"
}

namespace emulocke {

std::optional<std::vector<uint8_t>> applyXdeltaPatch(
    std::span<const uint8_t> rom, std::span<const uint8_t> patch) {
    if (rom.empty() || patch.size() < 4 || patch[0] != 0xD6 || patch[1] != 0xC3 || patch[2] != 0xC4) {
        return std::nullopt;
    }
    usize_t avail = static_cast<usize_t>(rom.size());
    if (avail < (32u << 20)) {
        avail = 32u << 20;
    }
    for (int attempt = 0; attempt < 3; ++attempt) {
        std::vector<uint8_t> out(avail);
        usize_t wrote = 0;
        int rc = xd3_decode_memory(patch.data(), static_cast<usize_t>(patch.size()), rom.data(),
            static_cast<usize_t>(rom.size()), out.data(), &wrote, avail, 0);
        if (rc == XD3_INVALID_INPUT) {
            wrote = 0;
            rc = xd3_decode_memory(patch.data(), static_cast<usize_t>(patch.size()), rom.data(),
                static_cast<usize_t>(rom.size()), out.data(), &wrote, avail, XD3_ADLER32_NOVER);
        }
        if (rc == 0) {
            out.resize(wrote);
            return out;
        }
        if (rc != ENOSPC) {
            return std::nullopt;
        }
        avail *= 2;
    }
    return std::nullopt;
}

}
