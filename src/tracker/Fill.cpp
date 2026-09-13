#include "tracker/Log.hpp"

#include "adapter/Snapshot.hpp"

#include <cctype>
#include <cstring>
#include <unordered_set>
#include <vector>

namespace emulocke {
namespace {

bool catchMatches(const TrackerStop& stop, const Mon& mon) {
    if (mon.species == 0 || mon.egg) {
        return false;
    }
    if (stop.catchKind == CatchKind::Starter) {
        return mon.species == 1 || mon.species == 4 || mon.species == 7;
    }
    if (stop.catchKind != CatchKind::Met || !stop.mets) {
        return false;
    }
    for (uint8_t i = 0; i < stop.metCount; ++i) {
        if (mon.metLocation == stop.mets[i]) {
            return true;
        }
    }
    return false;
}

void gatherMons(const GameSnapshot& snap, std::vector<const Mon*>& out) {
    for (uint8_t i = 0; i < snap.party.count; ++i) {
        out.push_back(&snap.party.mons[i]);
    }
    for (const PcBox& box : snap.boxes.boxes) {
        for (const Mon& mon : box.mons) {
            if (mon.species != 0) {
                out.push_back(&mon);
            }
        }
    }
}

}  // namespace

void applyTrackerFill(TrackerLog& log, const TrackerAtlas& atlas, const GameSnapshot& snap) {
    std::vector<const Mon*> mons;
    gatherMons(snap, mons);
    std::unordered_set<uint32_t> claimed;
    for (const TrackerStop& stop : atlas.stops) {
        if (stop.kind != TrackerStopKind::Encounter) {
            continue;
        }
        const Caught row = log.caught(stop.id);
        if (row.personality != 0) {
            claimed.insert(row.personality);
        }
    }
    for (const TrackerStop& stop : atlas.stops) {
        if (stop.kind == TrackerStopKind::Boss) {
            if (stop.defeatFlag != 0 && progressFlag(snap.progress, stop.defeatFlag)) {
                log.setDefeated(stop.id, true);
            }
            continue;
        }
        Caught row = log.caught(stop.id);
        if (row.personality != 0) {
            for (const Mon* mon : mons) {
                if (mon->personality == row.personality && mon->species != 0 && !mon->egg) {
                    log.setCaught(stop.id, mon->species, mon->personality);
                    break;
                }
            }
            continue;
        }
        if (row.status != EncounterStatus::Empty && row.status != EncounterStatus::Captured) {
            continue;
        }
        if (row.species != 0) {
            continue;
        }
        for (const Mon* mon : mons) {
            if (mon->personality != 0 && claimed.count(mon->personality)) {
                continue;
            }
            if (!catchMatches(stop, *mon)) {
                continue;
            }
            log.setCaught(stop.id, mon->species, mon->personality);
            if (mon->personality != 0) {
                claimed.insert(mon->personality);
            }
            break;
        }
    }
}

uint16_t matchSpeciesName(const GameAdapter& adapter, std::string_view typed) {
    std::string want;
    want.reserve(typed.size());
    for (char c : typed) {
        if (c == ' ' || c == '_') {
            if (!want.empty() && want.back() != '-') {
                want.push_back('-');
            }
            continue;
        }
        if (c == '\'') {
            continue;
        }
        want.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
    }
    if (want.empty()) {
        return 0;
    }
    auto compact = [](std::string_view s) {
        std::string out;
        for (char c : s) {
            if (std::isalnum(static_cast<unsigned char>(c))) {
                out.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
            }
        }
        return out;
    };
    const std::string wantCompact = compact(want);
    for (uint16_t id = 1; id < 440; ++id) {
        const SpeciesRef ref = adapter.species(id);
        if (ref.slug && std::strcmp(ref.slug, want.c_str()) == 0) {
            return id;
        }
        if (ref.slug && compact(ref.slug) == wantCompact) {
            return id;
        }
    }
    return 0;
}

}