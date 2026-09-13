#pragma once

#include "adapter/Snapshot.hpp"
#include "run/Run.hpp"

#include <filesystem>
#include <string>
#include <unordered_map>

namespace emulocke {

class RunStore;

class SavePeek {
public:
    const GameSnapshot& get(const RunStore& store, const Run& run);

private:
    struct Slot {
        std::filesystem::file_time_type mtime{};
        GameSnapshot snap;
    };
    std::unordered_map<std::string, Slot> cache_;
    GameSnapshot empty_{};
};

}
