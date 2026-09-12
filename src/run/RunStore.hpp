#pragma once

#include "run/Run.hpp"

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace emulocke {

class RunStore {
public:
    RunStore() = default;
    explicit RunStore(std::filesystem::path root);
    bool load();
    const std::vector<Run>& runs() const { return runs_; }
    const Run* find(const std::string& id) const;
    Run* find(const std::string& id);
    std::optional<Run> create(GameId game, std::string romPath, NuzlockeRules rules);
    std::optional<Run> createAttempt(const Run& source);
    bool touch(const std::string& id);
    bool updateRomPath(const std::string& id, std::string romPath);
    std::filesystem::path batteryPath(const std::string& id) const;
    std::vector<const Run*> byGame(GameId game) const;

private:
    std::optional<Run> persist(Run run);
    int nextAttempt(const std::string& lineageId) const;
    void erase(const std::string& id);
    void eraseLineageExcept(const std::string& lineageId, const std::string& keepId);
    std::filesystem::path root_;
    std::vector<Run> runs_;
};

}
