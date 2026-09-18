#include "calc/Build.hpp"

#include "calc/Dex.hpp"
#include "calc/Nature.hpp"
#include "calc/Stats.hpp"

namespace emulocke {
namespace {

const SpeciesRow* rowFor(uint16_t species, const char* name, const CalcPack* pack) {
    if (pack && pack->dex && species < static_cast<uint16_t>(pack->dexCount) && pack->dex[species].slug) {
        return &pack->dex[species];
    }
    if (pack && (pack->dmgGen == 4 || pack->dmgGen == 5)) {
        if (const SpeciesRow* nat = nationalDexRow(species)) {
            return nat;
        }
    }
    if (const SpeciesRow* named = speciesByName(name)) {
        return named;
    }
    return speciesById(species);
}

Pokemon fromRow(const SpeciesRow& row, uint16_t species, uint8_t level, uint8_t iv, uint8_t nature,
    uint8_t abilityNum, const uint8_t ev[6]) {
    Pokemon out;
    out.name = row.slug;
    out.species = species;
    out.t1 = static_cast<Type>(row.t1);
    out.t2 = row.t2 == row.t1 ? Type::None : static_cast<Type>(row.t2);
    out.level = level;
    out.ability = abilityNum ? row.a2 : row.a1;
    out.maxHp = hpStat(row.hp, iv, ev[0], level);
    out.hp = out.maxHp;
    out.atk = otherStat(row.atk, iv, ev[1], level, natureMul(nature, 1));
    out.def = otherStat(row.def, iv, ev[2], level, natureMul(nature, 2));
    out.spe = otherStat(row.spe, iv, ev[3], level, natureMul(nature, 3));
    out.spa = otherStat(row.spa, iv, ev[4], level, natureMul(nature, 4));
    out.spd = otherStat(row.spd, iv, ev[5], level, natureMul(nature, 5));
    return out;
}

}  // namespace

Pokemon pokemonFromPack(const PackMon& mon, const CalcPack* pack) {
    const uint8_t iv = static_cast<uint8_t>(mon.iv * 31 / 255);
    const uint8_t ev[6] = {mon.evHp, mon.evAtk, mon.evDef, mon.evSpe, mon.evSpa, mon.evSpd};
    const SpeciesRow* row = rowFor(mon.species, nullptr, pack);
    if (!row) {
        return {};
    }
    Pokemon out = fromRow(*row, mon.species, mon.level, iv, mon.nature, mon.ability, ev);
    out.item = mon.item;
    if (mon.ability > 1) {
        out.ability = mon.ability;
    }
    return out;
}

Pokemon pokemonFromPack(const PackMon& mon) {
    return pokemonFromPack(mon, nullptr);
}

Pokemon pokemonFromSnap(const Mon& mon, const CalcPack* pack) {
    const uint8_t ev[6] = {mon.evHp, mon.evAtk, mon.evDef, mon.evSpe, mon.evSpa, mon.evSpd};
    const SpeciesRow* row = rowFor(mon.species, mon.speciesName, pack);
    if (!row) {
        return {};
    }
    Pokemon out = fromRow(*row, mon.species, mon.level, mon.ivAtk, mon.nature, mon.abilityNum, ev);
    if (mon.maxHp) {
        out.maxHp = mon.maxHp;
        out.hp = mon.hp;
        out.atk = mon.attack;
        out.def = mon.defense;
        out.spa = mon.spAttack;
        out.spd = mon.spDefense;
        out.spe = mon.speed;
    }
    out.item = mon.heldItem;
    out.status = mon.status;
    return out;
}

Field fieldFromSnap(const GameSnapshot* snap) {
    Field f;
    if (!snap || !snap->battle.inBattle) {
        return f;
    }
    if (snap->battle.weather == 1) {
        f.weather = Weather::Rain;
    } else if (snap->battle.weather == 2) {
        f.weather = Weather::Sand;
    } else if (snap->battle.weather == 3) {
        f.weather = Weather::Sun;
    } else if (snap->battle.weather == 4) {
        f.weather = Weather::Hail;
    }
    return f;
}

void applyBattler(Pokemon& mon, const BattleBattler& b) {
    mon.atkStage = b.stages[1];
    mon.defStage = b.stages[2];
    mon.speStage = b.stages[3];
    mon.spaStage = b.stages[4];
    mon.spdStage = b.stages[5];
    mon.accStage = b.stages[6];
    mon.evaStage = b.stages[7];
    if (b.level >= 1 && b.level <= 100) {
        mon.level = b.level;
    }
    if (b.maxHp) {
        if (b.maxHp > mon.maxHp) {
            mon.maxHp = b.maxHp;
        }
        mon.hp = b.hp;
        if (mon.hp > mon.maxHp) {
            mon.hp = mon.maxHp;
        }
    }
    mon.status = b.status;
}

}
