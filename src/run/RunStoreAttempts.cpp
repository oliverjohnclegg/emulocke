#include "run/RunStore.hpp"

#include "run/RunMeta.hpp"

#include <algorithm>
#include <string_view>

namespace emulocke {

int RunStore::nextAttempt(const std::string& lineageId) const {
    int highest = 0;
    for (const Run& run : runs_) {
        if (run.lineageKey() == lineageId) {
            highest = std::max(highest, run.attempt);
        }
    }
    return highest + 1;
}

void RunStore::eraseLineageExcept(const std::string& lineageId, const std::string& keepId) {
    std::vector<std::string> doomed;
    for (const Run& run : runs_) {
        if (run.lineageKey() == lineageId && run.id != keepId) {
            doomed.push_back(run.id);
        }
    }
    for (const std::string& id : doomed) {
        erase(id);
    }
}

std::optional<Run> RunStore::createAttempt(const Run& source) {
    const std::string lineage = source.lineageKey();
    const int attempt = nextAttempt(lineage);
    Run run = source;
    run.id.clear();
    run.lineageId = lineage;
    run.attempt = attempt;
    run.createdAt = isoTimestamp();
    run.lastPlayedAt = run.createdAt;
    run.playMs = 0;
    auto created = persist(std::move(run));
    if (!created) {
        return std::nullopt;
    }
    eraseLineageExcept(created->lineageId, created->id);
    return created;
}

std::vector<const Run*> RunStore::byCatalogUuid(std::string_view uuid) const {
    std::vector<const Run*> out;
    for (const Run& run : runs_) {
        if (run.catalogUuid != uuid) {
            continue;
        }
        auto it = std::find_if(out.begin(), out.end(), [&](const Run* existing) {
            return existing->lineageKey() == run.lineageKey();
        });
        if (it == out.end()) {
            out.push_back(&run);
        } else if (run.attempt > (*it)->attempt ||
            (run.attempt == (*it)->attempt && run.lastPlayedAt > (*it)->lastPlayedAt)) {
            *it = &run;
        }
    }
    std::sort(out.begin(), out.end(), [](const Run* a, const Run* b) {
        return a->lastPlayedAt > b->lastPlayedAt;
    });
    return out;
}

std::vector<const Run*> RunStore::recentLineages() const {
    std::vector<const Run*> out;
    for (const Run& run : runs_) {
        auto it = std::find_if(out.begin(), out.end(), [&](const Run* existing) {
            return existing->lineageKey() == run.lineageKey();
        });
        if (it == out.end()) {
            out.push_back(&run);
        } else if (run.attempt > (*it)->attempt ||
            (run.attempt == (*it)->attempt && run.lastPlayedAt > (*it)->lastPlayedAt)) {
            *it = &run;
        }
    }
    std::sort(out.begin(), out.end(), [](const Run* a, const Run* b) {
        return a->lastPlayedAt > b->lastPlayedAt;
    });
    return out;
}

}