#pragma once

#include "adapter/Snapshot.hpp"

#include <cstdint>
#include <string_view>

namespace emulocke {

bool gen3Adapter(std::string_view id);
uint16_t speciesBst(uint16_t national);
uint8_t speciesGrowth(uint16_t national);
MonGender speciesGender(uint16_t national, uint32_t personality);
uint8_t levelFromExp(uint16_t national, uint32_t exp);
uint8_t monLevel(const Mon& mon, uint16_t national);
const char* natureName(uint8_t nature);
const char* abilityName(uint16_t id);
const char* moveName(uint16_t id);
const char* itemName(uint16_t id, bool gen3);
const char* monAbility(const Mon& mon, uint16_t national, bool gen3);

}
