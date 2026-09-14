#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/unbound_teams.inc"
#include "tracker/generated/unbound_stops.inc"
}

const TrackerAtlas& unboundAtlas() {
    static const TrackerAtlas atlas{"unbound", kStops_unbound,
        kStarters_unbound};
    return atlas;
}

}
