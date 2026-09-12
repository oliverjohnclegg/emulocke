#include "run/RunStore.hpp"

#include "run/RunMeta.hpp"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <random>

namespace emulocke {
namespace {

std::string makeRunId() {
    std::random_device rd;
    const uint64_t n = (static_cast<uint64_t>(rd()) << 32) ^ rd();
    char buf[17];
    std::snprintf(buf, sizeof buf, "%016llx", static_cast<unsigned long long>(n));
    return buf;
}

}  // namespace

RunStore::RunStore(std::filesystem::path root) : root_(std::move(root)) {
    std::error_code ec;
    std::filesystem::create_directories(root_, ec);
}

bool RunStore::load() {
    runs_.clear();
    std::error_code ec;
    if (!std::filesystem::is_directory(root_, ec)) {
        return true;
    }
    for (const auto& entry : std::filesystem::directory_iterator(root_, ec)) {
        if (!entry.is_directory(ec)) {
            continue;
        }
        auto run = readRunMeta(entry.path());
        if (run) {
            runs_.push_back(std::move(*run));
        }
    }
    return true;
}

const Run* RunStore::find(const std::string& id) const {
    for (const Run& run : runs_) {
        if (run.id == id) {
            return &run;
        }
    }
    return nullptr;
}

Run* RunStore::find(const std::string& id) {
    return const_cast<Run*>(static_cast<const RunStore*>(this)->find(id));
}

std::optional<Run> RunStore::persist(Run run) {
    while (run.id.empty() || std::filesystem::exists(root_ / run.id)) {
        run.id = makeRunId();
    }
    if (run.lineageId.empty()) {
        run.lineageId = run.id;
    }
    std::error_code ec;
    if (!std::filesystem::create_directory(root_ / run.id, ec)) {
        return std::nullopt;
    }
    if (!writeRunMeta(root_ / run.id, run)) {
        return std::nullopt;
    }
    runs_.push_back(run);
    return run;
}

int RunStore::nextAttempt(const std::string& lineageId) const {
    int highest = 0;
    for (const Run& run : runs_) {
        const std::string& lid = run.lineageId.empty() ? run.id : run.lineageId;
        if (lid == lineageId) {
            highest = std::max(highest, run.attempt);
        }
    }
    return highest + 1;
}

std::optional<Run> RunStore::create(GameId game, std::string romPath, NuzlockeRules rules) {
    Run run;
    run.gameId = game;
    run.romPath = std::move(romPath);
    run.rules = rules;
    run.attempt = 1;
    run.createdAt = isoTimestamp();
    run.lastPlayedAt = run.createdAt;
    return persist(std::move(run));
}

std::optional<Run> RunStore::createAttempt(const Run& source) {
    Run run = source;
    run.id.clear();
    run.lineageId = source.lineageId.empty() ? source.id : source.lineageId;
    run.attempt = nextAttempt(run.lineageId);
    run.createdAt = isoTimestamp();
    run.lastPlayedAt = run.createdAt;
    return persist(std::move(run));
}

bool RunStore::touch(const std::string& id) {
    Run* run = find(id);
    if (!run) {
        return false;
    }
    run->lastPlayedAt = isoTimestamp();
    return writeRunMeta(root_ / id, *run);
}

bool RunStore::updateRomPath(const std::string& id, std::string romPath) {
    Run* run = find(id);
    if (!run) {
        return false;
    }
    run->romPath = std::move(romPath);
    return writeRunMeta(root_ / id, *run);
}

std::filesystem::path RunStore::batteryPath(const std::string& id) const {
    return root_ / id / "battery.sav";
}

std::vector<const Run*> RunStore::byGame(GameId game) const {
    std::vector<const Run*> out;
    for (const Run& run : runs_) {
        if (run.gameId == game) {
            out.push_back(&run);
        }
    }
    std::sort(out.begin(), out.end(), [](const Run* a, const Run* b) {
        return a->lastPlayedAt > b->lastPlayedAt;
    });
    return out;
}

}
