#include "cheats/Book.hpp"

#include "cheats/BookParse.hpp"
#include "cheats/Limits.hpp"
#include "cheats/Lines.hpp"

#include <algorithm>
#include <sstream>
#include <utility>

namespace emulocke {

void CheatBook::clear() {
    items_.clear();
}

bool CheatBook::add(std::string_view name, std::string_view code) {
    Cheat row;
    row.id = nextId();
    row.name = std::string(trimCheat(name));
    std::ostringstream joined;
    for (const std::string& line : cheatLines(code)) {
        if (joined.tellp() > 0) {
            joined << '\n';
        }
        joined << line;
    }
    row.code = joined.str();
    row.enabled = false;
    if (items_.size() >= static_cast<std::size_t>(kMaxCheats) || !keepCheat(row)) {
        return false;
    }
    items_.push_back(std::move(row));
    return true;
}

bool CheatBook::remove(std::string_view id) {
    const auto it = std::remove_if(items_.begin(), items_.end(),
        [&](const Cheat& row) { return row.id == id; });
    if (it == items_.end()) {
        return false;
    }
    items_.erase(it, items_.end());
    return true;
}

bool CheatBook::setEnabled(std::string_view id, bool on) {
    for (Cheat& row : items_) {
        if (row.id == id) {
            row.enabled = on;
            return true;
        }
    }
    return false;
}

std::vector<CheatSpec> CheatBook::enabledSpecs() const {
    std::vector<CheatSpec> out;
    for (const Cheat& row : items_) {
        if (row.enabled) {
            out.push_back({row.name, row.code});
        }
    }
    return out;
}

std::string CheatBook::nextId() const {
    int high = 0;
    for (const Cheat& row : items_) {
        if (cheatIdOk(row.id)) {
            high = std::max(high, cheatIdNum(row.id));
        }
    }
    return "c" + std::to_string(high + 1);
}

}
