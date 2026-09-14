#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/b2w2_teams.inc"
#include "tracker/generated/b2w2_stops.inc"
}

const TrackerAtlas& b2w2Atlas() {
    static const TrackerAtlas atlas{"b2w2", kStops_b2w2,
        kStarters_b2w2};
    return atlas;
}

}
