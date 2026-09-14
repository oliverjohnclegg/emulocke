#include "cheats/Book.hpp"

#include "cheats/BookParse.hpp"
#include "cheats/Lines.hpp"

#include <fstream>
#include <string>
#include <system_error>

namespace emulocke {

bool CheatBook::loadEnabled(const std::filesystem::path& path) {
    for (Cheat& row : items_) {
        row.enabled = false;
    }
    std::error_code ec;
    if (!std::filesystem::exists(path, ec) || ec) {
        return !ec;
    }
    if (!cheatFileSmallEnough(path)) {
        return false;
    }
    std::ifstream in(path);
    if (!in) {
        return false;
    }
    std::string line;
    while (std::getline(in, line)) {
        const auto text = trimCheat(line);
        const auto eq = text.find('=');
        if (eq == std::string_view::npos) {
            continue;
        }
        if (trimCheat(text.substr(0, eq)) != "on") {
            continue;
        }
        setEnabled(trimCheat(text.substr(eq + 1)), true);
    }
    return true;
}

bool CheatBook::saveEnabled(const std::filesystem::path& path) const {
    std::ofstream out(path, std::ios::trunc);
    if (!out) {
        return false;
    }
    for (const Cheat& row : items_) {
        if (row.enabled) {
            out << "on=" << row.id << '\n';
        }
    }
    return static_cast<bool>(out);
}

}
