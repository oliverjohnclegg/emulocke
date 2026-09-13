#pragma once

#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <span>

namespace emulocke {

struct Cartridge {
    char code[5]{};
    uint8_t revision{};
};

inline Cartridge cartridgeFromGbaRom(std::span<const uint8_t> rom) {
    Cartridge cart;
    if (rom.size() < 0xBD) {
        return cart;
    }
    std::memcpy(cart.code, rom.data() + 0xAC, 4);
    cart.revision = rom[0xBC];
    return cart;
}

inline Cartridge cartridgeFromNdsRom(std::span<const uint8_t> rom) {
    Cartridge cart;
    if (rom.size() < 0x1F) {
        return cart;
    }
    std::memcpy(cart.code, rom.data() + 0x0C, 4);
    cart.revision = rom[0x1E];
    return cart;
}

inline Cartridge cartridgeFromRom(std::span<const uint8_t> rom) {
    return cartridgeFromGbaRom(rom);
}

inline bool cartridgeCodeIs(const Cartridge& cart, const char* code) {
    return std::memcmp(cart.code, code, 4) == 0;
}

inline bool cartridgeMatches(const Cartridge& cart, const char* code, std::initializer_list<uint8_t> revs) {
    if (!cartridgeCodeIs(cart, code)) {
        return false;
    }
    for (uint8_t rev : revs) {
        if (cart.revision == rev) {
            return true;
        }
    }
    return false;
}

}
