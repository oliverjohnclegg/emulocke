#pragma once

#include "adapter/Species.hpp"

#include <cstdint>

namespace emulocke {

const char* nationalSpeciesName(uint16_t species);
bool nationalSpeciesKnown(uint16_t species);
SpeciesRef nationalSpeciesRef(uint16_t species);

}
