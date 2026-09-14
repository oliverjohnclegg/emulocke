#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/blazevolt2_teams.inc"
#include "tracker/generated/blazevolt2_stops.inc"
}

const TrackerAtlas& blazevolt2Atlas() {
    static const TrackerAtlas atlas{"blazevolt2", kStops_blazevolt2,
        kStarters_blazevolt2};
    return atlas;
}

}
