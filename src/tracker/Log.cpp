#include "tracker/Log.hpp"

namespace emulocke {

Caught TrackerLog::caught(std::string_view id) const {
    const auto it = caught_.find(std::string(id));
    if (it == caught_.end()) {
        return {};
    }
    return it->second;
}

void TrackerLog::setCaught(std::string_view id, uint16_t species, uint32_t personality) {
    Caught& row = caught_[std::string(id)];
    if (row.species != species || row.personality != personality) {
        row.species = species;
        row.personality = personality;
        dirty_ = true;
    }
    if (species != 0 && row.status == EncounterStatus::Empty) {
        row.status = EncounterStatus::Captured;
        dirty_ = true;
    }
}

void TrackerLog::setStatus(std::string_view id, EncounterStatus status) {
    Caught& row = caught_[std::string(id)];
    if (row.status == status) {
        return;
    }
    row.status = status;
    dirty_ = true;
}

bool TrackerLog::defeated(std::string_view id) const {
    const auto it = boss_.find(std::string(id));
    return it != boss_.end() && it->second;
}

void TrackerLog::setDefeated(std::string_view id, bool on) {
    bool& slot = boss_[std::string(id)];
    if (slot == on) {
        return;
    }
    slot = on;
    dirty_ = true;
}

}
