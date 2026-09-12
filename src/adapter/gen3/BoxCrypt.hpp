#pragma once

#include <cstdint>

namespace emulocke {

void xorBoxData(uint8_t* data, uint32_t personality, uint32_t otId);
uint16_t boxDataChecksum(const uint8_t* data);
void unshuffleBoxData(const uint8_t* shuffled, uint32_t pid, uint8_t* g, uint8_t* a, uint8_t* e, uint8_t* m);
void shuffleBoxData(const uint8_t* g, const uint8_t* a, const uint8_t* e, const uint8_t* m, uint32_t pid, uint8_t* out);

}