#include "adapter/frlg/FrlgNames.hpp"

#include "adapter/gen45/Names.hpp"

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

constexpr uint16_t kSpeciesCap = 1600;
Slot kSlots[kSpeciesCap];
Slot kUnboundSlots[kSpeciesCap];

uint16_t nationalIdForSlug(const char* slug) {
    if (!slug || !slug[0]) {
        return 0;
    }
    for (uint16_t n = 1; n < 1026; ++n) {
        const SpeciesRef nat = nationalSpeciesRef(n);
        if (nat.slug && std::strcmp(nat.slug, slug) == 0) {
            return n;
        }
    }
    return 0;
}

void fillSlot(const char* raw, Slot& slot) {
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
    slot.national = nationalIdForSlug(slot.slug);
    if (std::strcmp(raw, "???") == 0) {
        slot.name[0] = 0;
        slot.slug[0] = 0;
        slot.national = 0;
    }
}

SpeciesRef cachedRef(uint16_t species, Slot* slots, const char* raw) {
    if (species == 0 || species >= kSpeciesCap) {
        return {};
    }
    Slot& slot = slots[species];
    if (!slot.ready) {
        fillSlot(raw, slot);
        slot.ready = true;
    }
    if (slot.national == 0 && slot.name[0] == 0) {
        return {};
    }
    return {slot.national, slot.slug, slot.name};
}

}  // namespace

SpeciesRef frlgSpeciesRef(uint16_t species) {
    return cachedRef(species, kSlots, frlgSpeciesName(species));
}

SpeciesRef unboundSpeciesRef(uint16_t species) {
    return cachedRef(species, kUnboundSlots, unboundSpeciesName(species));
}

}