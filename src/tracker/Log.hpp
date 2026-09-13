#pragma once

#include "adapter/GameAdapter.hpp"
#include "tracker/Atlas.hpp"

#include <cstdint>
#include <filesystem>
#include <string>
#include <string_view>
#include <unordered_map>

namespace emulocke {

struct Caught {
    uint16_t species{};
    uint32_t personality{};
};

class TrackerLog {
public:
    bool load(const std::filesystem::path& path);
    bool save(const std::filesystem::path& path) const;
    Caught caught(std::string_view id) const;
    void setCaught(std::string_view id, uint16_t species, uint32_t personality);
    bool defeated(std::string_view id) const;
    void setDefeated(std::string_view id, bool on);
    bool dirty() const { return dirty_; }
    void clearDirty() { dirty_ = false; }

private:
    std::unordered_map<std::string, Caught> caught_;
    std::unordered_map<std::string, bool> boss_;
    bool dirty_{};
};

void applyTrackerFill(TrackerLog& log, const TrackerAtlas& atlas, const GameSnapshot& snap);
uint16_t matchSpeciesName(const GameAdapter& adapter, std::string_view typed);

}