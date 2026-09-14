#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/rs_teams.inc"
#include "tracker/generated/rs_stops.inc"
}

const TrackerAtlas& rsAtlas() {
    static const TrackerAtlas atlas{"rs", kStops_rs,
        kStarters_rs};
    return atlas;
}

}
