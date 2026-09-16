#include "tracker/Snap.hpp"

#include "tracker/Atlas.hpp"
#include "tracker/Log.hpp"

#include <cctype>

namespace emulocke {
namespace {

bool foldEq(const char* a, const char* b) {
    if (!a || !b || !a[0] || !b[0]) {
        return false;
    }
    while (*a && *b) {
        const unsigned char ca = static_cast<unsigned char>(*a++);
        const unsigned char cb = static_cast<unsigned char>(*b++);
        if (std::tolower(ca) != std::tolower(cb)) {
            return false;
        }
    }
    return *a == *b;
}

bool stopMatches(const TrackerStop& stop, const char* mapName) {
    return foldEq(stop.name, mapName) || foldEq(stop.locale, mapName);
}

}  // namespace

int snapTrackerRow(const TrackerAtlas& atlas, const TrackerLog& log, const char* mapName) {
    int emptyMatch = -1;
    int anyMatch = -1;
    int firstEmpty = -1;
    for (int i = 0; i < static_cast<int>(atlas.stops.size()); ++i) {
        const TrackerStop& stop = atlas.stops[static_cast<std::size_t>(i)];
        const bool encounter = stop.kind == TrackerStopKind::Encounter;
        const bool empty = encounter && log.caught(stop.id).status == EncounterStatus::Empty;
        if (empty && firstEmpty < 0) {
            firstEmpty = i;
        }
        if (!stopMatches(stop, mapName)) {
            continue;
        }
        if (anyMatch < 0) {
            anyMatch = i;
        }
        if (empty && emptyMatch < 0) {
            emptyMatch = i;
        }
    }
    if (emptyMatch >= 0) {
        return emptyMatch;
    }
    if (anyMatch >= 0) {
        return anyMatch;
    }
    return firstEmpty;
}

}
