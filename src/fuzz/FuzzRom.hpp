#pragma once

#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

namespace emulocke::fuzz {

inline constexpr std::size_t kBaseRomBytes = 4096;

inline const std::vector<uint8_t>& baseRom() {
    static const std::vector<uint8_t> rom = [] {
        std::vector<uint8_t> bytes(kBaseRomBytes);
        for (std::size_t i = 0; i < bytes.size(); ++i) {
            bytes[i] = static_cast<uint8_t>(i * 7 + 3);
        }
        return bytes;
    }();
    return rom;
}

inline std::span<const uint8_t> input(const uint8_t* data, std::size_t size) {
    return {data, size};
}

}
