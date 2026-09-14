#pragma once

#include "run/Run.hpp"

#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
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
    std::optional<Run> create(std::string catalogUuid, NuzlockeRules rules, std::string patchOption = {},
                             std::string difficulty = {});
    std::optional<Run> createAttempt(const Run& source);
    bool touch(const std::string& id);
    bool addPlayMs(const std::string& id, uint64_t ms);
    std::filesystem::path batteryPath(const std::string& id) const;
    std::filesystem::path dir(const std::string& id) const;
    std::vector<const Run*> byCatalogUuid(std::string_view uuid) const;
    std::vector<const Run*> recentLineages() const;

private:
    std::optional<Run> persist(Run run);
    int nextAttempt(const std::string& lineageId) const;
    void erase(const std::string& id);
    void eraseLineageExcept(const std::string& lineageId, const std::string& keepId);
    std::filesystem::path root_;
    std::vector<Run> runs_;
};

}