#pragma once

#include "cheats/Cheat.hpp"

#include <filesystem>
#include <string>
#include <string_view>
#include <vector>

namespace emulocke {

class CheatBook {
public:
    void clear();
    bool loadGame(const std::filesystem::path& path);
    bool saveGame(const std::filesystem::path& path) const;
    bool loadEnabled(const std::filesystem::path& path);
    bool saveEnabled(const std::filesystem::path& path) const;
    bool add(std::string name, std::string code);
    bool remove(std::string_view id);
    bool setEnabled(std::string_view id, bool on);
    const std::vector<Cheat>& items() const { return items_; }
    std::vector<CheatSpec> enabledSpecs() const;

private:
    std::string nextId() const;
    std::vector<Cheat> items_;
};

}
