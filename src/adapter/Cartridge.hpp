#pragma once

#include <cstdint>
#include <cstring>
#include <span>

namespace emulocke {

struct Cartridge {
    char code[5]{};
    uint8_t revision{};
};

inline Cartridge cartridgeFromRom(std::span<const uint8_t> rom) {
    Cartridge cart;
    if (rom.size() < 0xBD) {
        return cart;
    }
    std::memcpy(cart.code, rom.data() + 0xAC, 4);
    cart.revision = rom[0xBC];
    return cart;
}

inline bool cartridgeCodeIs(const Cartridge& cart, const char* code) {
    return std::memcmp(cart.code, code, 4) == 0;
}

}