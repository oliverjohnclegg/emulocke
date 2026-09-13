#include "adapter/gen45/Names.hpp"

#include <cctype>
#include <cstddef>
#include <cstring>

namespace emulocke {
namespace {

struct Slot {
    char name[20];
    char slug[24];
    bool ready{};
};

Slot kSlots[650];

void fillSlot(uint16_t species, Slot& slot) {
    const char* raw = nationalSpeciesName(species);
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
        if (c == ' ' && si + 1 < sizeof(slot.slug)) {
            if (si == 0 || slot.slug[si - 1] != '-') {
                slot.slug[si++] = '-';
            }
        }
        upper = c != '\'';
    }
    slot.name[ni] = 0;
    slot.slug[si] = 0;
    if (std::strcmp(raw, "???") == 0 || raw[0] == '-') {
        slot.name[0] = 0;
        slot.slug[0] = 0;
    }
}

}  // namespace

SpeciesRef nationalSpeciesRef(uint16_t species) {
    if (species == 0 || species >= 650) {
        return {};
    }
    Slot& slot = kSlots[species];
    if (!slot.ready) {
        fillSlot(species, slot);
        slot.ready = true;
    }
    if (slot.slug[0] == 0) {
        return {};
    }
    return {species, slot.slug, slot.name};
}

}