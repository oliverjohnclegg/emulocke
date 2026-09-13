#include "application/PreviewMons.hpp"

#include "adapter/frlg/FrlgNames.hpp"

#include <cstdio>

namespace emulocke {
namespace {

void fillMon(Mon& mon, uint16_t species, uint32_t pid, uint8_t level, uint16_t hp, uint16_t maxHp) {
    mon = {};
    mon.species = species;
    mon.personality = pid;
    mon.otId = 413612;
    mon.level = level;
    mon.hp = hp;
    mon.maxHp = maxHp;
    mon.ivHp = 31;
    mon.ivAtk = 31;
    mon.ivDef = 31;
    mon.ivSpe = 31;
    mon.ivSpa = 31;
    mon.ivSpd = 31;
    mon.metLocation = 0xFE;
    std::snprintf(mon.speciesName, sizeof mon.speciesName, "%s", frlgSpeciesName(species));
    std::snprintf(mon.otName, sizeof mon.otName, "RED");
}

void setMoves(Mon& mon, uint16_t a, uint16_t b, uint16_t c, uint16_t d) {
    mon.moves[0] = a;
    mon.moves[1] = b;
    mon.moves[2] = c;
    mon.moves[3] = d;
}

void apply(Mon& mon, uint16_t species, uint32_t pid, uint8_t level, uint16_t hp, uint16_t maxHp,
    uint16_t item, uint8_t nature, uint16_t a, uint16_t b, uint16_t c, uint16_t d, const char* nick) {
    fillMon(mon, species, pid, level, hp, maxHp);
    mon.heldItem = item;
    mon.nature = nature;
    setMoves(mon, a, b, c, d);
    if (nick) {
        std::snprintf(mon.nickname, sizeof mon.nickname, "%s", nick);
    }
}

}  // namespace

void fillPreviewParty(Party& party) {
    party.count = 6;
    apply(party.mons[0], 1, 0x1001, 16, 45, 45, 205, 3, 22, 73, 33, 45, "SPROUT");
    apply(party.mons[1], 16, 0x1002, 12, 22, 38, 0, 13, 16, 98, 17, 28, nullptr);
    apply(party.mons[2], 25, 0x1003, 18, 6, 40, 202, 10, 85, 86, 98, 104, nullptr);
    party.mons[2].ivAtk = 0;
    apply(party.mons[3], 19, 0x1005, 10, 28, 28, 0, 3, 158, 98, 0, 0, nullptr);
    apply(party.mons[4], 41, 0x1006, 14, 31, 35, 0, 13, 17, 44, 48, 0, nullptr);
    apply(party.mons[5], 50, 0x1008, 20, 18, 32, 0, 3, 10, 222, 163, 0, nullptr);
}

void fillPreviewBoxes(Boxes& boxes) {
    PcBox& box = boxes.boxes[0];
    std::snprintf(box.name, sizeof box.name, "BOX 1");
    int n = 0;
    apply(box.mons[n++], 10, 0x1004, 7, 0, 22, 0, 0, 33, 81, 0, 0, nullptr);
    apply(box.mons[n++], 122, 0x1009, 26, 72, 72, 0, 15, 94, 95, 0, 0, nullptr);
    apply(box.mons[n++], 145, 0x100A, 50, 160, 180, 200, 10, 85, 87, 65, 97, nullptr);
    box.mons[n - 1].evSpa = 252;
    box.mons[n - 1].evSpe = 252;
    box.mons[n - 1].evHp = 6;
    constexpr uint16_t kExtra[] = {150, 144, 146, 151, 149, 143, 130, 65, 94, 59, 68, 76, 103, 121, 73, 80};
    for (uint16_t species : kExtra) {
        apply(box.mons[n++], species, 0x1100u + species, 40, 120, 120, 0, 0, 33, 0, 0, 0, nullptr);
    }
    constexpr uint16_t kGrave[] = {13, 17, 21, 23, 43, 74};
    for (uint16_t species : kGrave) {
        apply(box.mons[n++], species, 0x2000u + species, 12, 0, 28, 0, 0, 33, 0, 0, 0, nullptr);
    }
    for (Mon& mon : box.mons) {
        if (mon.species == 65) {
            mon.heldItem = 200;
            mon.nature = 10;
            mon.ivAtk = 0;
            setMoves(mon, 94, 85, 105, 8);
        } else if (mon.species == 94) {
            setMoves(mon, 247, 94, 95, 8);
        }
    }
}

}