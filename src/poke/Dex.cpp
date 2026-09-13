#include "poke/Dex.hpp"

#include <array>
#include <cstddef>

namespace emulocke {
namespace {

struct SpeciesRow {
    uint8_t hp{};
    uint8_t atk{};
    uint8_t def{};
    uint8_t spa{};
    uint8_t spd{};
    uint8_t spe{};
    uint8_t gender{};
    uint8_t growth{};
    uint8_t ab0{};
    uint8_t ab1{};
};

constexpr SpeciesRow kSpecies[] = {
#include "poke/SpeciesDex.inc"
};

constexpr const char* kNatures[] = {
    "Hardy",   "Lonely", "Brave",  "Adamant", "Naughty", "Bold",    "Docile", "Relaxed",
    "Impish",  "Lax",    "Timid",  "Hasty",   "Serious", "Jolly",   "Naive",  "Modest",
    "Mild",    "Quiet",  "Bashful","Rash",    "Calm",    "Gentle",  "Sassy",  "Careful",
    "Quirky",
};

constexpr const char* kMoves[] = {
#include "poke/Moves.inc"
};

constexpr const char* kAbilities[] = {
#include "poke/Abilities.inc"
};

constexpr const char* kGen3Items[] = {
#include "poke/Gen3Items.inc"
};

constexpr const char* kGen45Items[] = {
#include "poke/Gen45Items.inc"
};

const char* at(const char* const* table, std::size_t n, uint16_t id) {
    if (id >= n) {
        return "";
    }
    const char* s = table[id];
    return s ? s : "";
}

const SpeciesRow* row(uint16_t national) {
    if (national >= std::size(kSpecies)) {
        return nullptr;
    }
    return &kSpecies[national];
}

}  // namespace

bool gen3Adapter(std::string_view id) {
    return id.starts_with("firered") || id.starts_with("leafgreen") || id.starts_with("ruby") ||
           id.starts_with("sapphire") || id.starts_with("emerald");
}

uint16_t speciesBst(uint16_t national) {
    const SpeciesRow* s = row(national);
    if (!s) {
        return 0;
    }
    return static_cast<uint16_t>(s->hp + s->atk + s->def + s->spa + s->spd + s->spe);
}

MonGender speciesGender(uint16_t national, uint32_t personality) {
    const SpeciesRow* s = row(national);
    if (!s) {
        return MonGender::Unknown;
    }
    if (s->gender == 255) {
        return MonGender::Unknown;
    }
    if (s->gender == 254) {
        return MonGender::Female;
    }
    if (s->gender == 0) {
        return MonGender::Male;
    }
    return (personality & 0xFFu) < s->gender ? MonGender::Female : MonGender::Male;
}

const char* natureName(uint8_t nature) {
    return at(kNatures, std::size(kNatures), nature);
}

const char* abilityName(uint16_t id) {
    return at(kAbilities, std::size(kAbilities), id);
}

const char* moveName(uint16_t id) {
    return at(kMoves, std::size(kMoves), id);
}

const char* itemName(uint16_t id, bool gen3) {
    return gen3 ? at(kGen3Items, std::size(kGen3Items), id) : at(kGen45Items, std::size(kGen45Items), id);
}

const char* monAbility(const Mon& mon, uint16_t national, bool gen3) {
    if (!gen3) {
        return abilityName(mon.abilityNum);
    }
    const SpeciesRow* s = row(national);
    if (!s) {
        return "";
    }
    return abilityName(mon.abilityNum ? s->ab1 : s->ab0);
}

uint8_t speciesGrowth(uint16_t national) {
    const SpeciesRow* s = row(national);
    return s ? s->growth : 0;
}

}  // namespace emulocke
