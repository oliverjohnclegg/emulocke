#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/blaze_teams.inc"
#include "tracker/generated/blaze_stops.inc"
}

const TrackerAtlas& blazeAtlas() {
    static const TrackerAtlas atlas{"blaze", kStops_blaze,
        kStarters_blaze};
    return atlas;
}

}
