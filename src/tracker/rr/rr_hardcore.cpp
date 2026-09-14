#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/rr-hardcore_teams.inc"
#include "tracker/generated/rr-hardcore_stops.inc"
}

const TrackerAtlas& rr_hardcoreAtlas() {
    static const TrackerAtlas atlas{"rr-hardcore", kStops_rr_hardcore,
        kStarters_rr_hardcore};
    return atlas;
}

}
