#pragma once

#include <cstdint>
#include <optional>
#include <span>
#include <string>
#include <vector>

namespace emulocke {

std::string sha1Hex(std::span<const uint8_t> bytes);
std::optional<std::vector<uint8_t>> applyRomPatch(
    std::span<const uint8_t> rom, std::span<const uint8_t> patch);

}