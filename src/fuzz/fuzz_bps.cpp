#include "fuzz/FuzzRom.hpp"
#include "run/PatchApply.hpp"

#include <mgba-util/crc32.h>
#include <vector>

namespace {

constexpr std::size_t kBpsMinBytes = 16;

void storeLe32(std::vector<uint8_t>& bytes, std::size_t at, uint32_t value) {
    for (std::size_t i = 0; i < 4; ++i) {
        bytes[at + i] = static_cast<uint8_t>(value >> (8 * i));
    }
}

std::vector<uint8_t> withValidFooterCrcs(const uint8_t* data, size_t size, const std::vector<uint8_t>& rom) {
    std::vector<uint8_t> patch(data, data + size);
    if (patch.size() >= kBpsMinBytes) {
        storeLe32(patch, patch.size() - 12, doCrc32(rom.data(), rom.size()));
        storeLe32(patch, patch.size() - 4, doCrc32(patch.data(), patch.size() - 4));
    }
    return patch;
}

}  // namespace

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    const auto& rom = emulocke::fuzz::baseRom();
    emulocke::applyBpsPatch(rom, emulocke::fuzz::input(data, size));
    emulocke::applyBpsPatch(rom, withValidFooterCrcs(data, size, rom));
    return 0;
}
