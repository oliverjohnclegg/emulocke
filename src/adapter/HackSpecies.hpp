#pragma once

#include "adapter/Species.hpp"

#include <cstdint>
#include <string_view>

namespace emulocke {

class GameAdapter;

SpeciesRef hackAwareSpecies(std::string_view ext, uint16_t id, const GameAdapter* adapter,
                            bool unbound = false);

}
