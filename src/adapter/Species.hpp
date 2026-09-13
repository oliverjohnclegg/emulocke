#pragma once

#include <cstdint>

namespace emulocke {

struct SpeciesRef {
    uint16_t national{};
    const char* slug = "";
    const char* name = "";
};

}