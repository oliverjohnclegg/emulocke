#pragma once

#include "adapter/Snapshot.hpp"

#include <cstdint>
#include <filesystem>

namespace emulocke {

class GameAdapter;

class BatteryWatch {
public:
    bool refresh(const std::filesystem::path& path, const GameAdapter& adapter);
    void mergeInto(GameSnapshot& live) const;
    const GameSnapshot& snapshot() const { return snapshot_; }

private:
    std::filesystem::path path_;
    std::filesystem::file_time_type mtime_{};
    std::uintmax_t bytes_{};
    GameSnapshot snapshot_{};
};

}
