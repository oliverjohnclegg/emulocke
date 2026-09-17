#include "run/NdsMac.hpp"

#include <atomic>
#include <cctype>
#include <charconv>
#include <chrono>
#include <cstdio>
#include <random>

namespace emulocke {
namespace {

constexpr NdsMac kOui{0x00, 0x09, 0xBF, 0, 0, 0};
constexpr NdsMac kMelonDefault{0x00, 0x09, 0xBF, 0x11, 0x22, 0x33};

}  // namespace

bool ndsMacAssigned(const NdsMac& mac) {
    return mac[0] == kOui[0] && mac[1] == kOui[1] && mac[2] == kOui[2] && (mac[3] | mac[4] | mac[5]) != 0;
}

NdsMac randomNdsMac() {
    static std::atomic<uint32_t> seq{1};
    uint32_t mix = seq++ * 0x9e3779b9u;
    mix ^= static_cast<uint32_t>(std::chrono::steady_clock::now().time_since_epoch().count());
    mix ^= std::random_device{}();
    NdsMac mac = kOui;
    mac[3] = static_cast<uint8_t>(mix);
    mac[4] = static_cast<uint8_t>(mix >> 8);
    mac[5] = static_cast<uint8_t>(mix >> 16);
    if (!ndsMacAssigned(mac) || mac == kMelonDefault) {
        mac[5] ^= 1;
    }
    return mac;
}

std::optional<NdsMac> parseNdsMac(std::string_view text) {
    char hex[12];
    std::size_t n = 0;
    for (char c : text) {
        if (c == ':' || c == '-') {
            continue;
        }
        if (!std::isxdigit(static_cast<unsigned char>(c)) || n >= 12) {
            return std::nullopt;
        }
        hex[n++] = c;
    }
    if (n != 12) {
        return std::nullopt;
    }
    NdsMac mac{};
    for (int i = 0; i < 6; ++i) {
        unsigned v = 0;
        const auto [end, ec] = std::from_chars(hex + i * 2, hex + i * 2 + 2, v, 16);
        if (ec != std::errc{} || end != hex + i * 2 + 2) {
            return std::nullopt;
        }
        mac[static_cast<std::size_t>(i)] = static_cast<uint8_t>(v);
    }
    if (!ndsMacAssigned(mac)) {
        return std::nullopt;
    }
    return mac;
}

std::string formatNdsMac(const NdsMac& mac) {
    char buf[13];
    std::snprintf(buf, sizeof buf, "%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return buf;
}

}