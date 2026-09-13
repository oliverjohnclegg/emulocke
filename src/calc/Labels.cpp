#include "calc/Labels.hpp"

#include "calc/Ability.hpp"

namespace emulocke {

const char* abilityName(uint8_t id) {
    static const char* k[] = {"", "Stench", "Drizzle", "Speed Boost", "Battle Armor", "Sturdy",
        "Damp", "Limber", "Sand Veil", "Static", "Volt Absorb", "Water Absorb", "Oblivious",
        "Cloud Nine", "Compoundeyes", "Insomnia", "Color Change", "Immunity", "Flash Fire",
        "Shield Dust", "Own Tempo", "Suction Cups", "Intimidate", "Shadow Tag", "Rough Skin",
        "Wonder Guard", "Levitate", "Effect Spore", "Synchronize", "Clear Body", "Natural Cure",
        "Lightningrod", "Serene Grace", "Swift Swim", "Chlorophyll", "Illuminate", "Trace",
        "Huge Power", "Poison Point", "Inner Focus", "Magma Armor", "Water Veil", "Magnet Pull",
        "Soundproof", "Rain Dish", "Sand Stream", "Pressure", "Thick Fat", "Early Bird", "Flame Body",
        "Run Away", "Keen Eye", "Hyper Cutter", "Pickup", "Truant", "Hustle", "Cute Charm", "Plus",
        "Minus", "Forecast", "Sticky Hold", "Shed Skin", "Guts", "Marvel Scale", "Liquid Ooze",
        "Overgrow", "Blaze", "Torrent", "Swarm", "Rock Head", "Drought", "Arena Trap", "Vital Spirit",
        "White Smoke", "Pure Power", "Shell Armor", "Cacophony", "Air Lock"};
    if (id == 0 || id >= sizeof(k) / sizeof(k[0])) {
        return nullptr;
    }
    return k[id];
}

const char* statusAbbrev(uint32_t status) {
    if (status & 7) {
        return "SLP";
    }
    if (status & kStFrz) {
        return "FRZ";
    }
    if (status & kStPar) {
        return "PAR";
    }
    if (status & kStBurn) {
        return "BRN";
    }
    if (status & kStToxic) {
        return "TOX";
    }
    if (status & kStPsn) {
        return "PSN";
    }
    return nullptr;
}

}