#include "adapter/gen45/Pk.hpp"

#include "adapter/gen3/Codec.hpp"

#include <cstdio>

namespace emulocke {
namespace {

char gen4Glyph(uint16_t c) {
    if (c >= 289 && c <= 298) {
        return static_cast<char>('0' + (c - 289));
    }
    if (c >= 299 && c <= 324) {
        return static_cast<char>('A' + (c - 299));
    }
    if (c >= 325 && c <= 350) {
        return static_cast<char>('a' + (c - 325));
    }
    if (c == 478) {
        return ' ';
    }
    if (c == 446) {
        return '-';
    }
    if (c == 433) {
        return '\'';
    }
    if (c == 439) {
        return '.';
    }
    return 0;
}

uint16_t gen4Code(char c) {
    if (c >= '0' && c <= '9') {
        return static_cast<uint16_t>(289 + (c - '0'));
    }
    if (c >= 'A' && c <= 'Z') {
        return static_cast<uint16_t>(299 + (c - 'A'));
    }
    if (c >= 'a' && c <= 'z') {
        return static_cast<uint16_t>(325 + (c - 'a'));
    }
    if (c == ' ') {
        return 478;
    }
    if (c == '-') {
        return 446;
    }
    if (c == '\'') {
        return 433;
    }
    if (c == '.') {
        return 439;
    }
    return 0;
}

}  // namespace

void decodeGen4Text(std::span<const uint8_t> src, char* dest, std::size_t destSize) {
    if (!dest || destSize == 0) {
        return;
    }
    std::size_t o = 0;
    for (std::size_t i = 0; i + 1 < src.size() && o + 1 < destSize; i += 2) {
        const uint16_t c = load16(src.data() + i);
        if (c == 0xFFFF) {
            break;
        }
        const char g = gen4Glyph(c);
        if (g) {
            dest[o++] = g;
        }
    }
    dest[o] = 0;
}

void encodeGen4Text(const char* src, std::span<uint8_t> dest) {
    std::size_t o = 0;
    for (; src && src[0] && o + 1 < dest.size(); ++src) {
        const uint16_t c = gen4Code(src[0]);
        if (!c) {
            continue;
        }
        store16(dest.data() + o, c);
        o += 2;
    }
    if (o + 1 < dest.size()) {
        store16(dest.data() + o, 0xFFFF);
    }
}

void decodeUtf16Text(std::span<const uint8_t> src, char* dest, std::size_t destSize) {
    if (!dest || destSize == 0) {
        return;
    }
    std::size_t o = 0;
    for (std::size_t i = 0; i + 1 < src.size() && o + 1 < destSize; i += 2) {
        const uint16_t c = load16(src.data() + i);
        if (c == 0 || c == 0xFFFF) {
            break;
        }
        dest[o++] = c < 128 ? static_cast<char>(c) : '?';
    }
    dest[o] = 0;
}

void encodeUtf16Text(const char* src, std::span<uint8_t> dest) {
    std::size_t o = 0;
    for (; src && src[0] && o + 1 < dest.size(); ++src) {
        store16(dest.data() + o, static_cast<uint8_t>(src[0]));
        o += 2;
    }
    if (o + 1 < dest.size()) {
        store16(dest.data() + o, 0xFFFF);
    }
}

bool utf16NamePresent(std::span<const uint8_t> src) {
    if (src.size() < 2) {
        return false;
    }
    const uint16_t first = load16(src.data());
    if (first == 0 || first == 0xFFFF) {
        return false;
    }
    for (std::size_t i = 0; i + 1 < src.size(); i += 2) {
        if (load16(src.data() + i) == 0xFFFF) {
            return true;
        }
    }
    return false;
}

}
