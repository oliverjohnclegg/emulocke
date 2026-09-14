#include "poke/Showdown.hpp"

#include "poke/Dex.hpp"

#include <cctype>
#include <cstdio>
#include <cstring>
#include <string>

namespace emulocke {
namespace {

bool sameName(const char* a, const char* b) {
    if (!a || !b) {
        return false;
    }
    while (*a && *b) {
        if (std::tolower(static_cast<unsigned char>(*a)) !=
            std::tolower(static_cast<unsigned char>(*b))) {
            return false;
        }
        ++a;
        ++b;
    }
    return *a == 0 && *b == 0;
}

void appendStatLine(std::string& out, const char* label, const uint8_t* values, uint8_t skip) {
    static constexpr const char* kStat[] = {"HP", "Atk", "Def", "SpA", "SpD", "Spe"};
    bool first = true;
    std::string line;
    for (int i = 0; i < 6; ++i) {
        if (values[i] == skip) {
            continue;
        }
        if (!first) {
            line += " / ";
        }
        first = false;
        char buf[24];
        std::snprintf(buf, sizeof buf, "%u %s", values[i], kStat[i]);
        line += buf;
    }
    if (!line.empty()) {
        out += label;
        out += line;
        out += '\n';
    }
}

const char* speciesTitle(const Mon& mon, SpeciesRef ref) {
    if (ref.name && ref.name[0]) {
        return ref.name;
    }
    return mon.speciesName[0] ? mon.speciesName : "Unknown";
}

}  // namespace

std::string exportSet(const Mon& mon, SpeciesRef ref, bool gen3) {
    const uint16_t national = ref.national ? ref.national : (gen3 ? uint16_t{0} : mon.species);
    const char* species = speciesTitle(mon, ref);
    std::string out;
    if (mon.nickname[0] && !sameName(mon.nickname, species) && !sameName(mon.nickname, mon.speciesName)) {
        out += mon.nickname;
        out += " (";
        out += species;
        out += ")";
    } else {
        out += species;
    }
    const MonGender gender = speciesGender(national, mon.personality);
    if (gender == MonGender::Male) {
        out += " (M)";
    } else if (gender == MonGender::Female) {
        out += " (F)";
    }
    const char* item = itemName(mon.heldItem, gen3);
    if (item && item[0]) {
        out += " @ ";
        out += item;
    }
    out += '\n';
    const char* ability = monAbility(mon, national, gen3);
    if (ability && ability[0]) {
        out += "Ability: ";
        out += ability;
        out += '\n';
    }
    const uint8_t level = monLevel(mon, national);
    if (level != 0 && level != 100) {
        char buf[32];
        std::snprintf(buf, sizeof buf, "Level: %u\n", level);
        out += buf;
    }
    if (mon.shiny) {
        out += "Shiny: Yes\n";
    }
    const uint8_t evs[] = {mon.evHp, mon.evAtk, mon.evDef, mon.evSpa, mon.evSpd, mon.evSpe};
    appendStatLine(out, "EVs: ", evs, 0);
    const char* nature = natureName(mon.nature);
    if (nature && nature[0]) {
        out += nature;
        out += " Nature\n";
    }
    const uint8_t ivs[] = {mon.ivHp, mon.ivAtk, mon.ivDef, mon.ivSpa, mon.ivSpd, mon.ivSpe};
    appendStatLine(out, "IVs: ", ivs, 31);
    for (int i = 0; i < 4; ++i) {
        const char* move = moveName(mon.moves[i]);
        if (move && move[0]) {
            out += "- ";
            out += move;
            out += '\n';
        }
    }
    return out;
}

}  // namespace emulocke
