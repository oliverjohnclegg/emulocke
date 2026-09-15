#include "run/RunStore.hpp"

#include "run/RunMeta.hpp"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstdio>

namespace emulocke {
namespace {

std::string makeRunId() {
    static std::atomic<uint64_t> seq{1};
    uint64_t mix = static_cast<uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count());
    mix ^= seq++ * 0x9e3779b97f4a7c15ull;
    char buf[17];
    std::snprintf(buf, sizeof buf, "%016llx", static_cast<unsigned long long>(mix));
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
    std::error_code ec;
    std::filesystem::create_directories(root_, ec);
    for (int i = 0; i < 64; ++i) {
        if (run.id.empty() || std::filesystem::exists(root_ / run.id, ec)) {
            run.id = makeRunId();
            continue;
        }
        break;
    }
    if (run.id.empty() || std::filesystem::exists(root_ / run.id, ec)) {
        return std::nullopt;
    }
    if (run.lineageId.empty()) {
        run.lineageId = run.id;
    }
    if (!std::filesystem::create_directory(root_ / run.id, ec)) {
        return std::nullopt;
    }
    if (!writeRunMeta(root_ / run.id, run)) {
        return std::nullopt;
    }
    runs_.push_back(run);
    return run;
}

std::optional<Run> RunStore::create(std::string catalogUuid, NuzlockeRules rules, std::string patchOption,
                                   std::string difficulty, bool allowCheats) {
    Run run;
    run.catalogUuid = std::move(catalogUuid);
    run.rules = rules;
    run.allowCheats = allowCheats;
    run.patchOption = std::move(patchOption);
    run.difficulty = std::move(difficulty);
    run.attempt = 1;
    run.createdAt = isoTimestamp();
    run.lastPlayedAt = run.createdAt;
    return persist(std::move(run));
}

void RunStore::erase(const std::string& id) {
    std::error_code ec;
    std::filesystem::remove_all(root_ / id, ec);
    runs_.erase(std::remove_if(runs_.begin(), runs_.end(),
                    [&](const Run& run) { return run.id == id; }),
        runs_.end());
}

bool RunStore::touch(const std::string& id) {
    Run* run = find(id);
    if (!run) {
        return false;
    }
    run->lastPlayedAt = isoTimestamp();
    return writeRunMeta(root_ / id, *run);
}

bool RunStore::addPlayMs(const std::string& id, uint64_t ms) {
    Run* run = find(id);
    if (!run) {
        return false;
    }
    if (ms == 0) {
        return true;
    }
    run->playMs += ms;
    return writeRunMeta(root_ / id, *run);
}

bool RunStore::importBattery(const std::string& id, const std::filesystem::path& source) const {
    std::error_code exists;
    if (!find(id) || !std::filesystem::is_regular_file(source, exists)) {
        return false;
    }
    std::error_code ec;
    std::filesystem::copy_file(source, batteryPath(id), std::filesystem::copy_options::overwrite_existing, ec);
    return !ec;
}

std::filesystem::path RunStore::batteryPath(const std::string& id) const {
    return root_ / id / "battery.sav";
}

std::filesystem::path RunStore::dir(const std::string& id) const {
    return root_ / id;
}

}
