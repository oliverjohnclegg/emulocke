#include "adapter/gen45/Pk.hpp"

#include "adapter/gen3/Codec.hpp"

#include <cstring>

namespace emulocke {
namespace {

constexpr uint8_t kBlockPos[] = {
    0, 1, 2, 3, 0, 1, 3, 2, 0, 2, 1, 3, 0, 3, 1, 2, 0, 2, 3, 1, 0, 3, 2, 1,
    1, 0, 2, 3, 1, 0, 3, 2, 2, 0, 1, 3, 3, 0, 1, 2, 2, 0, 3, 1, 3, 0, 2, 1,
    1, 2, 0, 3, 1, 3, 0, 2, 2, 1, 0, 3, 3, 1, 0, 2, 2, 3, 0, 1, 3, 2, 0, 1,
    1, 2, 3, 0, 1, 3, 2, 0, 2, 1, 3, 0, 3, 1, 2, 0, 2, 3, 1, 0, 3, 2, 1, 0,
};

void cryptRange(uint8_t* data, uint32_t seed, std::size_t start, std::size_t end) {
    for (std::size_t i = start; i + 1 < end; i += 2) {
        seed = 0x41C64E6D * seed + 0x6073;
        const uint16_t x = static_cast<uint16_t>(seed >> 16);
        data[i] ^= static_cast<uint8_t>(x);
        data[i + 1] ^= static_cast<uint8_t>(x >> 8);
    }
}

void unshuffle(uint8_t* data, uint32_t sv) {
    uint8_t tmp[kPkStoredSize];
    std::memcpy(tmp, data, kPkStoredSize);
    const uint32_t index = (sv % 24) * 4;
    for (int block = 0; block < 4; ++block) {
        const int src = 8 + kBlockPos[index + static_cast<uint32_t>(block)] * 32;
        std::memcpy(data + 8 + block * 32, tmp + src, 32);
    }
}

void shuffle(uint8_t* data, uint32_t sv) {
    uint8_t tmp[kPkStoredSize];
    std::memcpy(tmp, data, kPkStoredSize);
    const uint32_t index = (sv % 24) * 4;
    for (int block = 0; block < 4; ++block) {
        const int dest = 8 + kBlockPos[index + static_cast<uint32_t>(block)] * 32;
        std::memcpy(data + dest, tmp + 8 + block * 32, 32);
    }
}

}  // namespace

bool decryptPk45(std::span<const uint8_t> raw, std::span<uint8_t> out) {
    if (raw.size() < kPkStoredSize || out.size() < raw.size()) {
        return false;
    }
    std::memcpy(out.data(), raw.data(), raw.size());
    const uint32_t pid = load32(out.data());
    const uint16_t expect = load16(out.data() + 6);
    const uint32_t sv = (pid >> 13) & 31;
    cryptRange(out.data(), expect, 8, kPkStoredSize);
    unshuffle(out.data(), sv);
    uint16_t sum = 0;
    for (std::size_t i = 8; i < kPkStoredSize; i += 2) {
        sum += load16(out.data() + i);
    }
    if (sum != expect) {
        return false;
    }
    if (raw.size() > kPkStoredSize) {
        cryptRange(out.data(), pid, kPkStoredSize, raw.size());
    }
    return true;
}

bool encryptPk45(std::span<const uint8_t> plain, std::span<uint8_t> out) {
    if (plain.size() < kPkStoredSize || out.size() < plain.size()) {
        return false;
    }
    std::memcpy(out.data(), plain.data(), plain.size());
    uint16_t sum = 0;
    for (std::size_t i = 8; i < kPkStoredSize; i += 2) {
        sum += load16(out.data() + i);
    }
    store16(out.data() + 6, sum);
    const uint32_t pid = load32(out.data());
    shuffle(out.data(), (pid >> 13) & 31);
    cryptRange(out.data(), sum, 8, kPkStoredSize);
    if (plain.size() > kPkStoredSize) {
        cryptRange(out.data(), pid, kPkStoredSize, plain.size());
    }
    return true;
}

}
