#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/rr_teams.inc"
#include "tracker/generated/rr_stops.inc"
}

const TrackerAtlas& rrAtlas() {
    static const TrackerAtlas atlas{"rr", kStops_rr,
        kStarters_rr};
    return atlas;
}

}
