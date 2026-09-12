#include "run/RunMeta.hpp"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <map>
#include <string>

namespace emulocke {
namespace {

std::string trim(std::string s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == ' ')) {
        s.pop_back();
    }
    return s;
}

bool parseBool(const std::string& v, bool& out) {
    if (v == "1" || v == "true") {
        out = true;
        return true;
    }
    if (v == "0" || v == "false") {
        out = false;
        return true;
    }
    return false;
}

}  // namespace

std::string isoTimestamp() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
#ifdef _WIN32
    gmtime_s(&tm, &t);
#else
    gmtime_r(&t, &tm);
#endif
    char buf[21];
    std::strftime(buf, sizeof buf, "%Y-%m-%dT%H:%M:%SZ", &tm);
    return buf;
}

std::optional<Run> readRunMeta(const std::filesystem::path& dir) {
    std::ifstream in(dir / "meta.ini");
    if (!in) {
        return std::nullopt;
    }
    std::map<std::string, std::string> kv;
    std::string line;
    while (std::getline(in, line)) {
        line = trim(std::move(line));
        const auto eq = line.find('=');
        if (eq == std::string::npos || eq == 0) {
            continue;
        }
        kv[line.substr(0, eq)] = line.substr(eq + 1);
    }
    Run run;
    run.id = dir.filename().string();
    const auto game = gameIdFromKey(kv["game"]);
    if (!game || kv["romPath"].empty() || kv["createdAt"].empty()) {
        return std::nullopt;
    }
    run.gameId = *game;
    run.romPath = kv["romPath"];
    run.createdAt = kv["createdAt"];
    run.lastPlayedAt = kv.count("lastPlayedAt") ? kv["lastPlayedAt"] : run.createdAt;
    run.lineageId = kv.count("lineageId") && !kv["lineageId"].empty() ? kv["lineageId"] : run.id;
    run.attempt = 1;
    if (kv.count("attempt")) {
        try {
            run.attempt = std::max(1, std::stoi(kv["attempt"]));
        } catch (...) {
            run.attempt = 1;
        }
    }
    auto flag = [&](const char* key, bool& dst) {
        return kv.count(key) && parseBool(kv[key], dst);
    };
    if (!flag("firstEncounter", run.rules.firstEncounter) || !flag("nicknames", run.rules.nicknames) ||
        !flag("faintIsDeath", run.rules.faintIsDeath) || !flag("setMode", run.rules.setMode) ||
        !flag("noItemsInBattle", run.rules.noItemsInBattle) || !flag("levelCap", run.rules.levelCap) ||
        !flag("dupesClause", run.rules.dupesClause) || !flag("shinyClause", run.rules.shinyClause)) {
        return std::nullopt;
    }
    return run;
}

bool writeRunMeta(const std::filesystem::path& dir, const Run& run) {
    std::ofstream out(dir / "meta.ini", std::ios::trunc);
    if (!out) {
        return false;
    }
    auto yn = [](bool v) { return v ? "1" : "0"; };
    out << "game=" << gameKey(run.gameId) << "\n";
    out << "romPath=" << run.romPath << "\n";
    out << "lineageId=" << run.lineageId << "\n";
    out << "attempt=" << run.attempt << "\n";
    out << "firstEncounter=" << yn(run.rules.firstEncounter) << "\n";
    out << "nicknames=" << yn(run.rules.nicknames) << "\n";
    out << "faintIsDeath=" << yn(run.rules.faintIsDeath) << "\n";
    out << "setMode=" << yn(run.rules.setMode) << "\n";
    out << "noItemsInBattle=" << yn(run.rules.noItemsInBattle) << "\n";
    out << "levelCap=" << yn(run.rules.levelCap) << "\n";
    out << "dupesClause=" << yn(run.rules.dupesClause) << "\n";
    out << "shinyClause=" << yn(run.rules.shinyClause) << "\n";
    out << "createdAt=" << run.createdAt << "\n";
    out << "lastPlayedAt=" << run.lastPlayedAt << "\n";
    return static_cast<bool>(out);
}

}
