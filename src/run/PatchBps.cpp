#include "run/BpsCommands.hpp"
#include "run/PatchApply.hpp"

#include <mgba-util/crc32.h>
#include <cstring>

namespace emulocke {
namespace {

constexpr std::size_t kBpsHeader = 4;
constexpr std::size_t kBpsFooter = 12;

uint32_t le32(std::span<const uint8_t> p, std::size_t at) {
    return static_cast<uint32_t>(p[at]) | (static_cast<uint32_t>(p[at + 1]) << 8) |
           (static_cast<uint32_t>(p[at + 2]) << 16) | (static_cast<uint32_t>(p[at + 3]) << 24);
}

bool footerMatches(std::span<const uint8_t> rom, std::span<const uint8_t> patch) {
    return doCrc32(patch.data(), patch.size() - 4) == le32(patch, patch.size() - 4) &&
           doCrc32(rom.data(), rom.size()) == le32(patch, patch.size() - 12);
}

}  // namespace

std::optional<std::vector<uint8_t>> applyBpsPatch(
    std::span<const uint8_t> rom, std::span<const uint8_t> patch) {
    if (patch.size() < kBpsHeader + kBpsFooter || std::memcmp(patch.data(), "BPS1", kBpsHeader) != 0 ||
        !footerMatches(rom, patch)) {
        return std::nullopt;
    }
    BpsReader reader(patch, kBpsHeader, patch.size() - kBpsFooter);
    uint64_t sourceSize = 0;
    uint64_t targetSize = 0;
    uint64_t meta = 0;
    if (!reader.readVli(sourceSize) || sourceSize != rom.size() || !reader.readVli(targetSize) ||
        targetSize == 0 || targetSize > kMaxPatchedRom || !reader.readVli(meta) || !reader.skip(meta)) {
        return std::nullopt;
    }
    BpsState state{rom, std::vector<uint8_t>(static_cast<std::size_t>(targetSize))};
    while (!reader.done()) {
        if (!runBpsCommand(reader, state)) {
            return std::nullopt;
        }
    }
    if (state.write != state.out.size() ||
        doCrc32(state.out.data(), state.out.size()) != le32(patch, patch.size() - 8)) {
        return std::nullopt;
    }
    return std::move(state.out);
}

}
