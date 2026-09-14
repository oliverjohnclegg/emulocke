#include "cheats/Book.hpp"

#include "cheats/BookParse.hpp"
#include "cheats/Limits.hpp"
#include "cheats/Lines.hpp"

#include <fstream>
#include <system_error>
#include <utility>

namespace emulocke {
namespace {

void flushCheat(std::vector<Cheat>& items, Cheat& row) {
    if (items.size() >= static_cast<std::size_t>(kMaxCheats) || !keepCheat(row)) {
        row = {};
        return;
    }
    row.enabled = false;
    items.push_back(std::move(row));
    row = {};
}

}  // namespace

bool CheatBook::loadGame(const std::filesystem::path& path) {
    clear();
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
    Cheat row;
    std::string line;
    while (std::getline(in, line)) {
        const auto text = trimCheat(line);
        if (text.empty()) {
            continue;
        }
        if (text.front() == '[' && text.back() == ']' && text.size() >= 3) {
            flushCheat(items_, row);
            row.id = std::string(text.substr(1, text.size() - 2));
            continue;
        }
        const auto eq = text.find('=');
        if (eq == std::string_view::npos || eq == 0) {
            continue;
        }
        const auto key = trimCheat(text.substr(0, eq));
        const auto val = text.substr(eq + 1);
        if (key == "name") {
            row.name = std::string(trimCheat(val));
        } else if (key == "code") {
            if (!row.code.empty()) {
                row.code.push_back('\n');
            }
            row.code.append(val);
        }
    }
    flushCheat(items_, row);
    return true;
}

bool CheatBook::saveGame(const std::filesystem::path& path) const {
    std::error_code ec;
    std::filesystem::create_directories(path.parent_path(), ec);
    std::ofstream out(path, std::ios::trunc);
    if (!out) {
        return false;
    }
    for (const Cheat& row : items_) {
        out << '[' << row.id << "]\n";
        out << "name=" << row.name << '\n';
        for (const std::string& line : cheatLines(row.code)) {
            out << "code=" << line << '\n';
        }
        out << '\n';
    }
    return static_cast<bool>(out);
}

}
