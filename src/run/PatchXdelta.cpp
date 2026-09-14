#include "run/PatchApply.hpp"

#include <algorithm>

extern "C" {
#include "xdelta3.h"
}

namespace emulocke {
namespace {

constexpr std::size_t kXdeltaFirstBuffer = std::size_t{32} << 20;

bool hasVcdiffMagic(std::span<const uint8_t> patch) {
    return patch.size() >= 4 && patch[0] == 0xD6 && patch[1] == 0xC3 && patch[2] == 0xC4;
}

}  // namespace

std::optional<std::vector<uint8_t>> applyXdeltaPatch(
    std::span<const uint8_t> rom, std::span<const uint8_t> patch) {
    if (rom.empty() || rom.size() > kMaxRomFile || !hasVcdiffMagic(patch)) {
        return std::nullopt;
    }
    std::size_t avail = std::max(rom.size(), kXdeltaFirstBuffer);
    while (true) {
        avail = std::min(avail, kMaxRomFile);
        std::vector<uint8_t> out(avail);
        usize_t wrote = 0;
        const int rc = xd3_decode_memory(patch.data(), static_cast<usize_t>(patch.size()), rom.data(),
            static_cast<usize_t>(rom.size()), out.data(), &wrote, static_cast<usize_t>(avail), 0);
        if (rc == 0) {
            out.resize(wrote);
            return out;
        }
        if (rc != ENOSPC || avail == kMaxRomFile) {
            return std::nullopt;
        }
        avail *= 2;
    }
}

}
