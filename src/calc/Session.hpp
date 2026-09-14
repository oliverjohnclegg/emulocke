#pragma once

#include "adapter/Snapshot.hpp"
#include "calc/Field.hpp"
#include "calc/Pack.hpp"

#include <string_view>
#include <vector>

namespace emulocke {

class CalcSession {
public:
    void setPack(const CalcPack* pack);
    void sync(std::string_view uuid, std::string_view variant, const GameSnapshot* snap);
    void search(const char* query);
    void pickTrainer(const PackTrainer* trainer);
    void pickLocation(const PackLocation* loc);
    void lockParty(int slot);
    void lockFoe(int slot);
    const CalcPack* pack() const { return pack_; }
    const PackTrainer* trainer() const { return trainer_; }
    const GameSnapshot* snap() const { return snap_.ok ? &snap_ : nullptr; }
    int partySlot() const { return partySlot_; }
    int foeSlot() const { return foeSlot_; }
    const std::vector<const PackTrainer*>& trainerHits() const { return trainers_; }
    const std::vector<const PackLocation*>& locationHits() const { return locations_; }
    char* query() { return query_; }
    bool browsing() const { return browsing_; }
    bool fainted(int slot) const;
    int nextIn() const;
    void foeOrder(int slots[6]) const;
    FieldState& fieldState() { return field_; }
    const FieldState& fieldState() const { return field_; }
    bool& sideCrit(bool foe) { return foe ? critTheirs_ : critOurs_; }
    bool sideCrit(bool foe) const { return foe ? critTheirs_ : critOurs_; }
    void pickMove(bool foe, int slot) {
        pickFoe_ = foe;
        pickSlot_ = slot;
    }
    bool pickFoe() const { return pickFoe_; }
    int pickSlot() const { return pickSlot_; }
    void seedWeather(Weather w);

private:
    void refreshFoe();
    const CalcPack* pack_{};
    PackTrainer const* trainer_{};
    GameSnapshot snap_{};
    int partySlot_{};
    int foeSlot_{};
    int liveParty_{-1};
    int liveFoe_{-1};
    bool pinParty_{};
    bool pinFoe_{};
    char query_[48]{};
    bool browsing_{};
    std::vector<const PackTrainer*> trainers_;
    std::vector<const PackLocation*> locations_;
    FieldState field_{};
    Weather liveWeather_{Weather::None};
    bool critOurs_{};
    bool critTheirs_{};
    bool pickFoe_{};
    int pickSlot_{};
};

}
