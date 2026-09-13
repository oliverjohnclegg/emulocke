#include "tracker/Log.hpp"

#include <fstream>
#include <map>

namespace emulocke {
namespace {

std::string trim(std::string s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == ' ')) {
        s.pop_back();
    }
    return s;
}

char statusMark(EncounterStatus status) {
    static constexpr char kMarks[] = {'e', 'c', 'd', 'm', 't'};
    const auto i = static_cast<uint8_t>(status);
    return i < 5 ? kMarks[i] : 'e';
}

EncounterStatus statusFrom(char mark) {
    switch (mark) {
        case 'c':
            return EncounterStatus::Captured;
        case 'd':
            return EncounterStatus::Dead;
        case 'm':
            return EncounterStatus::Missed;
        case 't':
            return EncounterStatus::Traded;
        default:
            return EncounterStatus::Empty;
    }
}

Caught parseCaught(const std::string& val) {
    Caught row;
    const auto colon = val.find(':');
    row.species = static_cast<uint16_t>(std::stoi(val.substr(0, colon)));
    if (colon == std::string::npos) {
        if (row.species != 0) {
            row.status = EncounterStatus::Captured;
        }
        return row;
    }
    const std::string rest = val.substr(colon + 1);
    const auto mark = rest.find(':');
    row.personality = static_cast<uint32_t>(std::stoul(rest.substr(0, mark)));
    if (mark != std::string::npos && mark + 1 < rest.size()) {
        row.status = statusFrom(rest[mark + 1]);
    }
    if (row.status == EncounterStatus::Empty && row.species != 0) {
        row.status = EncounterStatus::Captured;
    }
    return row;
}

}  // namespace

bool TrackerLog::load(const std::filesystem::path& path) {
    caught_.clear();
    boss_.clear();
    dirty_ = false;
    std::ifstream in(path);
    if (!in) {
        return true;
    }
    std::string section;
    std::string line;
    while (std::getline(in, line)) {
        line = trim(std::move(line));
        if (line.empty()) {
            continue;
        }
        if (line == "[caught]") {
            section = "caught";
            continue;
        }
        if (line == "[boss]") {
            section = "boss";
            continue;
        }
        const auto eq = line.find('=');
        if (eq == std::string::npos || eq == 0) {
            continue;
        }
        const std::string key = line.substr(0, eq);
        const std::string val = line.substr(eq + 1);
        if (section == "caught") {
            try {
                caught_[key] = parseCaught(val);
            } catch (...) {
                continue;
            }
        } else if (section == "boss") {
            boss_[key] = val == "1" || val == "true";
        }
    }
    return true;
}

bool TrackerLog::save(const std::filesystem::path& path) const {
    std::ofstream out(path, std::ios::trunc);
    if (!out) {
        return false;
    }
    out << "[caught]\n";
    std::map<std::string, Caught> caught(caught_.begin(), caught_.end());
    for (const auto& [id, row] : caught) {
        if (row.species == 0 && row.status == EncounterStatus::Empty) {
            continue;
        }
        out << id << '=' << row.species << ':' << row.personality << ':' << statusMark(row.status) << '\n';
    }
    out << "[boss]\n";
    std::map<std::string, bool> boss(boss_.begin(), boss_.end());
    for (const auto& [id, on] : boss) {
        if (on) {
            out << id << "=1\n";
        }
    }
    return static_cast<bool>(out);
}

}
