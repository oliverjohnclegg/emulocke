#pragma once

#include "cheats/Cheat.hpp"
#include "cheats/Limits.hpp"
#include "cheats/Lines.hpp"

#include <cctype>
#include <filesystem>
#include <string_view>

namespace emulocke {

inline bool cheatIdOk(std::string_view id) {
    if (id.size() < 2 || id.front() != 'c') {
        return false;
    }
    for (std::size_t i = 1; i < id.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(id[i]))) {
            return false;
        }
    }
    return true;
}

inline int cheatIdNum(std::string_view id) {
    int n = 0;
    for (std::size_t i = 1; i < id.size(); ++i) {
        n = n * 10 + (id[i] - '0');
        if (n > 100000) {
            return n;
        }
    }
    return n;
}

inline bool keepCheat(const Cheat& row) {
    if (row.id.empty() || !cheatIdOk(row.id) || row.name.empty() || row.code.empty()) {
        return false;
    }
    if (row.name.size() > kMaxCheatName || row.code.size() > kMaxCheatCode) {
        return false;
    }
    for (const std::string& line : cheatLines(row.code)) {
        if (line.size() > kMaxCheatLine) {
            return false;
        }
    }
    return true;
}

inline bool cheatFileSmallEnough(const std::filesystem::path& path) {
    std::error_code ec;
    const auto size = std::filesystem::file_size(path, ec);
    return !ec && size <= kMaxCheatFile;
}

}
