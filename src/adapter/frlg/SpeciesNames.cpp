#include "adapter/frlg/FrlgNames.hpp"

namespace emulocke {
namespace {

constexpr const char* kSpecies[] = {
#include "adapter/frlg/SpeciesNames.inc"
};

}  // namespace

const char* frlgSpeciesName(uint16_t species) {
    if (species < sizeof(kSpecies) / sizeof(kSpecies[0])) {
        return kSpecies[species];
    }
    return "???";
}

}
