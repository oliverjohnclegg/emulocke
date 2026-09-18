#include "calc/Session.hpp"

#include "calc/Build.hpp"
#include "calc/SwitchIn.hpp"

namespace emulocke {
namespace {

void followLive(int live, int& last, int& slot, bool& pin) {
    if (live != last) {
        last = live;
        slot = live;
        pin = false;
    } else if (!pin) {
        slot = live;
    }
}

}  // namespace

void CalcSession::setPack(const CalcPack* pack) {
    pack_ = pack;
    trainer_ = nullptr;
    trainers_.clear();
    locations_.clear();
    foeSlot_ = 0;
    pinFoe_ = false;
    pinParty_ = false;
    liveFoe_ = -1;
    liveParty_ = -1;
    browsing_ = false;
    field_ = {};
    liveWeather_ = Weather::None;
    critOurs_ = false;
    critTheirs_ = false;
    pickFoe_ = false;
    pickSlot_ = 0;
    atlas_ = nullptr;
    starter_ = 0;
}

void CalcSession::seedWeather(Weather w) {
    if (w != liveWeather_) {
        field_.weather = w;
        liveWeather_ = w;
    }
}

void CalcSession::sync(std::string_view uuid, std::string_view variant, const GameSnapshot* snap,
    uint16_t starter, const TrackerAtlas* atlas) {
    const CalcPack* next = calcPack(uuid, variant);
    if (next != pack_) {
        setPack(next);
    }
    if (snap) {
        snap_ = *snap;
    } else {
        snap_ = {};
    }
    starter_ = starter;
    atlas_ = atlas;
    refreshFoe();
    seedWeather(fieldFromSnap(snap ? &snap_ : nullptr).weather);
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

void CalcSession::foeOrder(int slots[6]) const {
    for (int i = 0; i < 6; ++i) {
        slots[i] = -1;
    }
    if (!pack_ || !trainer_) {
        return;
    }
    bool down[6]{};
    for (int i = 0; i < 6; ++i) {
        down[i] = fainted(i);
    }
    Pokemon player{};
    if (snap_.ok && partySlot_ >= 0 && partySlot_ < 6 &&
        snap_.party.mons[static_cast<std::size_t>(partySlot_)].species) {
        player = pokemonFromSnap(snap_.party.mons[static_cast<std::size_t>(partySlot_)], pack_);
    }
    switchOrder(*pack_, *trainer_, down, player, pack_->switchIn, slots,
        snap_.battle.inBattle ? snap_.battle.foe.partyIndex : -1);
}

int CalcSession::nextIn() const {
    int slots[6];
    foeOrder(slots);
    if (snap_.battle.inBattle && slots[1] >= 0) {
        return slots[1];
    }
    return slots[0] >= 0 ? slots[0] : 0;
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
    followLive(snap_.battle.foe.partyIndex, liveFoe_, foeSlot_, pinFoe_);
    followLive(snap_.battle.player.partyIndex, liveParty_, partySlot_, pinParty_);
}

}