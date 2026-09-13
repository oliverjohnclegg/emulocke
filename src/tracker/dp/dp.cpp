#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/dp_teams.inc"
#include "tracker/generated/dp_stops.inc"
}

const TrackerAtlas& dpAtlas() {
    static const TrackerAtlas atlas{"dp", kStops_dp,
        kStarters_dp};
    return atlas;
}

}
