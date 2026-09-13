#include "application/Application.hpp"

#include "adapter/frlg/FrlgNames.hpp"
#include "run/Catalog.hpp"

#include <cstdio>
#include <cstring>

namespace emulocke {
namespace {

Mon previewMon(uint16_t species, uint8_t level, uint16_t hp, uint16_t maxHp, uint16_t atk, uint16_t def,
    uint16_t spa, uint16_t spd, uint16_t spe, uint16_t m0, uint16_t m1, uint16_t m2, uint16_t m3) {
    Mon mon;
    mon.species = species;
    mon.level = level;
    mon.hp = hp;
    mon.maxHp = maxHp;
    mon.attack = atk;
    mon.defense = def;
    mon.spAttack = spa;
    mon.spDefense = spd;
    mon.speed = spe;
    mon.ivHp = mon.ivAtk = mon.ivDef = mon.ivSpe = mon.ivSpa = mon.ivSpd = 31;
    mon.moves[0] = m0;
    mon.moves[1] = m1;
    mon.moves[2] = m2;
    mon.moves[3] = m3;
    std::snprintf(mon.speciesName, sizeof(mon.speciesName), "%s", frlgSpeciesName(species));
    return mon;
}

}  // namespace

void Application::seedPreviewCalc() {
    snapshot_.ok = true;
    snapshot_.adapterId = "firered-us-1.0";
    snapshot_.origin = SnapshotOrigin::Live;
    std::snprintf(snapshot_.trainer.name, sizeof(snapshot_.trainer.name), "%s", "RED");
    snapshot_.party.count = 3;
    snapshot_.party.mons[0] = previewMon(3, 32, 80, 80, 52, 53, 70, 70, 50, 75, 202, 73, 22);
    snapshot_.party.mons[1] = previewMon(25, 25, 55, 55, 35, 25, 40, 35, 70, 84, 86, 98, 21);
    snapshot_.party.mons[2] = previewMon(6, 36, 90, 90, 64, 58, 85, 65, 80, 53, 126, 52, 19);
    calc_.sync(kFireRedUs10Uuid, {}, &snapshot_);
    calc_.search("brock");
    if (!calc_.trainerHits().empty()) {
        calc_.pickTrainer(calc_.trainerHits().front());
    }
    status_ = "Calculator preview";
    previewCalcSelect_ = true;
}

bool Application::consumePreviewCalcSelect() {
    if (!previewCalc_ || !previewCalcSelect_) {
        return false;
    }
    previewCalcSelect_ = false;
    return true;
}

}
