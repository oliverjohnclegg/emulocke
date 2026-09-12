#pragma once

#include "adapter/gen3/BoxMon.hpp"

namespace emulocke {

void pullGrowth(const uint8_t* g, DecryptedMon& o);
void pushGrowth(uint8_t* g, const DecryptedMon& o);
void pullAttacks(const uint8_t* a, DecryptedMon& o);
void pushAttacks(uint8_t* a, const DecryptedMon& o);
void pullEvs(const uint8_t* e, DecryptedMon& o);
void pushEvs(uint8_t* e, const DecryptedMon& o);
void pullMisc(const uint8_t* m, DecryptedMon& o);
void pushMisc(uint8_t* m, const DecryptedMon& o);
void pullHeader(const uint8_t* raw, DecryptedMon& o);
void pushHeader(uint8_t* raw, const DecryptedMon& o);
void pullPartyTail(const uint8_t* tail, DecryptedMon& o);
void pushPartyTail(uint8_t* tail, const DecryptedMon& o);

}