#include "calc/Session.hpp"

#include "calc/SwitchIn.hpp"

namespace emulocke {

void CalcSession::setPack(const CalcPack* pack) {
    pack_ = pack;
    trainer_ = nullptr;
    trainers_.clear();
    locations_.clear();
    foeSlot_ = 0;
    browsing_ = false;
}

void CalcSession::sync(std::string_view uuid, std::string_view variant, const GameSnapshot* snap) {
    const CalcPack* next = calcPack(uuid, variant);
    if (next != pack_) {
        setPack(next);
    }
    if (snap) {
        snap_ = *snap;
    } else {
        snap_ = {};
    }
    refreshFoe();
}

void CalcSession::lockParty(int slot) {
    partySlot_ = slot;
}

bool CalcSession::fainted(int slot) const {
    if (!trainer_ || !pack_) {
        return true;
    }
    if (snap_.battle.inBattle && slot >= 0 && slot < 6) {
        return snap_.battle.foeHp[slot] == 0 && snap_.battle.foeMaxHp[slot] > 0;
    }
    return false;
}

int CalcSession::nextIn() const {
    if (!pack_ || !trainer_) {
        return 0;
    }
    bool down[6]{};
    for (int i = 0; i < 6; ++i) {
        down[i] = fainted(i);
    }
    return nextSwitchSlot(*pack_, *trainer_, down, pack_->switchIn);
}

void CalcSession::refreshFoe() {
    if (!pack_ || !snap_.battle.inBattle) {
        return;
    }
    if (snap_.battle.trainerId) {
        if (const PackTrainer* t = packTrainer(*pack_, snap_.battle.trainerId)) {
            trainer_ = t;
        }
    } else {
        for (int i = 0; i < pack_->trainerCount; ++i) {
            const PackTrainer& t = pack_->trainers[i];
            if (t.count != snap_.battle.foeCount) {
                continue;
            }
            bool ok = true;
            for (int s = 0; s < t.count; ++s) {
                const PackMon* mon = trainerMon(*pack_, t, s);
                if (!mon || mon->species != snap_.battle.foeSpecies[s] ||
                    mon->level != snap_.battle.foeLevel[s]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                trainer_ = &t;
                break;
            }
        }
    }
    foeSlot_ = snap_.battle.foe.partyIndex;
    partySlot_ = snap_.battle.player.partyIndex;
}

}
