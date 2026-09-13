#include "adapter/gen3/BoxMon.hpp"

#include "adapter/frlg/FrlgNames.hpp"

#include <cstdio>
#include <cstring>

namespace emulocke {

Mon toSnapshotMon(const DecryptedMon& in) {
    Mon mon;
    mon.species = in.species;
    mon.heldItem = in.heldItem;
    mon.personality = in.personality;
    mon.otId = in.otId;
    mon.level = in.level;
    mon.hp = in.hp;
    mon.maxHp = in.maxHp;
    mon.attack = in.attack;
    mon.defense = in.defense;
    mon.speed = in.speed;
    mon.spAttack = in.spAttack;
    mon.spDefense = in.spDefense;
    mon.ivHp = in.ivHp;
    mon.ivAtk = in.ivAtk;
    mon.ivDef = in.ivDef;
    mon.ivSpe = in.ivSpe;
    mon.ivSpa = in.ivSpa;
    mon.ivSpd = in.ivSpd;
    mon.evHp = in.evHp;
    mon.evAtk = in.evAtk;
    mon.evDef = in.evDef;
    mon.evSpe = in.evSpe;
    mon.evSpa = in.evSpa;
    mon.evSpd = in.evSpd;
    mon.nature = natureOf(in.personality);
    mon.abilityNum = in.abilityNum;
    mon.shiny = isShiny(in.otId, in.personality);
    mon.egg = in.egg;
    mon.status = in.status;
    for (int i = 0; i < 4; ++i) {
        mon.moves[i] = in.moves[i];
        mon.pp[i] = in.pp[i];
    }
    mon.metLocation = in.metLocation;
    mon.metLevel = in.metLevel;
    mon.metGame = in.metGame;
    mon.ball = in.ball;
    std::snprintf(mon.speciesName, sizeof(mon.speciesName), "%s", frlgSpeciesName(in.species));
    std::snprintf(mon.nickname, sizeof(mon.nickname), "%s", in.nickname);
    std::snprintf(mon.otName, sizeof(mon.otName), "%s", in.otName);
    return mon;
}

}
