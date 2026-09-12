#include "adapter/gen3/Codec.hpp"

#include <cctype>

namespace emulocke {
namespace {

char glyph(uint8_t code) {
    if (code == 0x00) {
        return ' ';
    }
    if (code >= 0xA1 && code <= 0xAA) {
        return static_cast<char>('0' + (code - 0xA1));
    }
    if (code >= 0xBB && code <= 0xD4) {
        return static_cast<char>('A' + (code - 0xBB));
    }
    if (code >= 0xD5 && code <= 0xEE) {
        return static_cast<char>('a' + (code - 0xD5));
    }
    if (code == 0xAB) {
        return '!';
    }
    if (code == 0xAC) {
        return '?';
    }
    if (code == 0xAD) {
        return '.';
    }
    if (code == 0xAE) {
        return '-';
    }
    if (code == 0xB8) {
        return ',';
    }
    if (code == 0xBA) {
        return '/';
    }
    if (code == 0xF0) {
        return ':';
    }
    return '?';
}

uint8_t codeFor(char ch) {
    if (ch == ' ') {
        return 0x00;
    }
    if (ch >= '0' && ch <= '9') {
        return static_cast<uint8_t>(0xA1 + (ch - '0'));
    }
    if (ch >= 'A' && ch <= 'Z') {
        return static_cast<uint8_t>(0xBB + (ch - 'A'));
    }
    if (ch >= 'a' && ch <= 'z') {
        return static_cast<uint8_t>(0xD5 + (ch - 'a'));
    }
    if (ch == '!') {
        return 0xAB;
    }
    if (ch == '?') {
        return 0xAC;
    }
    if (ch == '.') {
        return 0xAD;
    }
    if (ch == '-') {
        return 0xAE;
    }
    if (ch == ',') {
        return 0xB8;
    }
    if (ch == '/') {
        return 0xBA;
    }
    if (ch == ':') {
        return 0xF0;
    }
    if (ch == '\'') {
        return 0xB4;
    }
    return 0x00;
}

}  // namespace

void decodeGen3Text(std::span<const uint8_t> src, char* dest, std::size_t destSize) {
    if (!dest || destSize == 0) {
        return;
    }
    std::size_t n = 0;
    for (uint8_t code : src) {
        if (code == 0xFF || n + 1 >= destSize) {
            break;
        }
        dest[n++] = glyph(code);
    }
    dest[n] = 0;
}

void encodeGen3Text(const char* src, std::span<uint8_t> dest) {
    std::size_t i = 0;
    if (src) {
        for (; src[i] && i + 1 < dest.size(); ++i) {
            dest[i] = codeFor(src[i]);
        }
    }
    if (i < dest.size()) {
        dest[i++] = 0xFF;
    }
    for (; i < dest.size(); ++i) {
        dest[i] = 0xFF;
    }
}

}