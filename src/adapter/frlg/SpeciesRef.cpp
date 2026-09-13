#include "adapter/frlg/FrlgNames.hpp"

#include <cctype>
#include <cstring>

namespace emulocke {
namespace {

struct Slot {
    char name[20];
    char slug[20];
    uint16_t national{};
    bool ready{};
};

Slot kSlots[440];

void fillSlot(uint16_t species, Slot& slot) {
    const char* raw = frlgSpeciesName(species);
    std::size_t ni = 0;
    std::size_t si = 0;
    bool upper = true;
    for (const char* p = raw; *p && ni + 1 < sizeof(slot.name); ++p) {
        const unsigned char c = static_cast<unsigned char>(*p);
        if (c == '\'') {
            slot.name[ni++] = '\'';
            upper = false;
            continue;
        }
        if (std::isalpha(c)) {
            const char low = static_cast<char>(std::tolower(c));
            slot.name[ni++] = upper ? static_cast<char>(std::toupper(c)) : low;
            if (si + 1 < sizeof(slot.slug)) {
                slot.slug[si++] = low;
            }
            upper = false;
            continue;
        }
        slot.name[ni++] = static_cast<char>(c);
        if ((c == '-' || c == '.') && si + 1 < sizeof(slot.slug)) {
            if (si == 0 || slot.slug[si - 1] != '-') {
                slot.slug[si++] = '-';
            }
        }
        upper = c != '\'';
    }
    slot.name[ni] = 0;
    slot.slug[si] = 0;
    if (species >= 1 && species <= 251) {
        slot.national = species;
    } else if (species >= 277) {
        slot.national = static_cast<uint16_t>(species - 25);
    }
    if (std::strcmp(raw, "???") == 0) {
        slot.name[0] = 0;
        slot.slug[0] = 0;
        slot.national = 0;
    }
}

}  // namespace

SpeciesRef frlgSpeciesRef(uint16_t species) {
    if (species == 0 || species >= 440) {
        return {};
    }
    Slot& slot = kSlots[species];
    if (!slot.ready) {
        fillSlot(species, slot);
        slot.ready = true;
    }
    if (slot.national == 0 && slot.name[0] == 0) {
        return {};
    }
    return {slot.national, slot.slug, slot.name};
}

}