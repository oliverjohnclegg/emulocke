#pragma once

#include <cstdint>
#include <optional>
#include <span>
#include <string>
#include <vector>

namespace emulocke {

inline constexpr std::size_t kMaxPatchedRom = std::size_t{512} << 20;

std::string sha1Hex(std::span<const uint8_t> bytes);
std::optional<std::vector<uint8_t>> applyBpsPatch(
    std::span<const uint8_t> rom, std::span<const uint8_t> patch);
std::optional<std::vector<uint8_t>> applyXdeltaPatch(
    std::span<const uint8_t> rom, std::span<const uint8_t> patch);
std::optional<std::vector<uint8_t>> applyRomPatch(
    std::span<const uint8_t> rom, std::span<const uint8_t> patch);

}