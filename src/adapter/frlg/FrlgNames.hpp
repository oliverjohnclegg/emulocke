#pragma once

#include <cstddef>
#include <cstdint>

namespace emulocke {

const char* frlgSpeciesName(uint16_t species);
const char* frlgMapName(uint8_t group, uint8_t num, char* scratch, std::size_t scratchSize);

}