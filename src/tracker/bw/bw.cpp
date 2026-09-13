#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/bw_teams.inc"
#include "tracker/generated/bw_stops.inc"
}

const TrackerAtlas& bwAtlas() {
    static const TrackerAtlas atlas{"bw", kStops_bw,
        kStarters_bw};
    return atlas;
}

}
