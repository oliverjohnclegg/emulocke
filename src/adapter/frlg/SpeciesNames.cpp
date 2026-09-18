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

const char* unboundSpeciesName(uint16_t species) {
    if (species == 777 || (species >= 840 && species <= 843)) {
        return "FLABEBE";
    }
    if (species >= 844 && species <= 848) {
        return "FLOETTE";
    }
    if (species >= 849 && species <= 852) {
        return "FLORGES";
    }
    return frlgSpeciesName(species);
}

}
