#pragma once

#include "adapter/GameAdapter.hpp"
#include "tracker/Atlas.hpp"

#include <cstdint>
#include <filesystem>
#include <string>
#include <string_view>
#include <unordered_map>

namespace emulocke {

enum class EncounterStatus : uint8_t { Empty, Captured, Dead, Missed, Traded };

inline EncounterStatus nextEncounterStatus(EncounterStatus status) {
    return static_cast<EncounterStatus>((static_cast<uint8_t>(status) + 1) % 5);
}

struct Caught {
    uint16_t species{};
    uint32_t personality{};
    EncounterStatus status{EncounterStatus::Empty};
    std::string slug;
};

class TrackerLog {
public:
    bool load(const std::filesystem::path& path);
    bool save(const std::filesystem::path& path) const;
    Caught caught(std::string_view id) const;
    void setCaught(std::string_view id, uint16_t species, uint32_t personality, std::string_view slug = {});
    void setStatus(std::string_view id, EncounterStatus status);
    bool defeated(std::string_view id) const;
    void setDefeated(std::string_view id, bool on);
    bool dirty() const { return dirty_; }
    void clearDirty() { dirty_ = false; }
    bool markedDead(uint32_t personality) const;
    const std::unordered_map<std::string, Caught>& caughtRows() const { return caught_; }

private:
    std::unordered_map<std::string, Caught> caught_;
    std::unordered_map<std::string, bool> boss_;
    bool dirty_{};
};

void applyTrackerFill(TrackerLog& log, const TrackerAtlas& atlas, const GameSnapshot& snap);
void applyFaintDeath(TrackerLog& log, const GameSnapshot& snap);
uint16_t matchSpeciesName(const GameAdapter& adapter, std::string_view typed);

}