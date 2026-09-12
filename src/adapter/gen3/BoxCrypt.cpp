#include "adapter/gen3/BoxCrypt.hpp"

#include "adapter/gen3/Codec.hpp"

#include <cstring>

namespace emulocke {
namespace {

constexpr uint8_t kTypeSlot[24][4] = {
    {0, 1, 2, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}, {0, 3, 1, 2}, {0, 2, 3, 1}, {0, 3, 2, 1},
    {1, 0, 2, 3}, {1, 0, 3, 2}, {2, 0, 1, 3}, {3, 0, 1, 2}, {2, 0, 3, 1}, {3, 0, 2, 1},
    {1, 2, 0, 3}, {1, 3, 0, 2}, {2, 1, 0, 3}, {3, 1, 0, 2}, {2, 3, 0, 1}, {3, 2, 0, 1},
    {1, 2, 3, 0}, {1, 3, 2, 0}, {2, 1, 3, 0}, {3, 1, 2, 0}, {2, 3, 1, 0}, {3, 2, 1, 0},
};

}  // namespace

void xorBoxData(uint8_t* data, uint32_t personality, uint32_t otId) {
    for (int i = 0; i < 12; ++i) {
        uint32_t w = load32(data + i * 4);
        w ^= personality;
        w ^= otId;
        store32(data + i * 4, w);
    }
}

uint16_t boxDataChecksum(const uint8_t* data) {
    uint16_t sum = 0;
    for (int i = 0; i < 24; ++i) {
        sum = static_cast<uint16_t>(sum + load16(data + i * 2));
    }
    return sum;
}

void unshuffleBoxData(const uint8_t* shuffled, uint32_t pid, uint8_t* g, uint8_t* a, uint8_t* e, uint8_t* m) {
    const uint8_t* slots = kTypeSlot[pid % 24];
    uint8_t* types[4] = {g, a, e, m};
    for (int t = 0; t < 4; ++t) {
        std::memcpy(types[t], shuffled + slots[t] * 12, 12);
    }
}

void shuffleBoxData(const uint8_t* g, const uint8_t* a, const uint8_t* e, const uint8_t* m, uint32_t pid, uint8_t* out) {
    const uint8_t* slots = kTypeSlot[pid % 24];
    const uint8_t* types[4] = {g, a, e, m};
    for (int t = 0; t < 4; ++t) {
        std::memcpy(out + slots[t] * 12, types[t], 12);
    }
}

}