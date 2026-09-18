#include "adapter/HackSpecies.hpp"

#include "adapter/GameAdapter.hpp"
#include "adapter/frlg/FrlgNames.hpp"
#include "adapter/gen45/Names.hpp"

#include <cstring>

namespace emulocke {
namespace {

bool usable(const SpeciesRef& ref) {
    return ref.slug && ref.slug[0] && std::strcmp(ref.slug, "???") != 0;
}

}  // namespace

SpeciesRef hackAwareSpecies(std::string_view ext, uint16_t id, const GameAdapter* adapter) {
    if (ext == ".nds") {
        const SpeciesRef nat = nationalSpeciesRef(id);
        if (usable(nat)) {
            return nat;
        }
    }
    if (adapter) {
        const SpeciesRef ref = adapter->species(id);
        if (usable(ref)) {
            return ref;
        }
    }
    if (ext == ".gba") {
        return frlgSpeciesRef(id);
    }
    return nationalSpeciesRef(id);
}

}
