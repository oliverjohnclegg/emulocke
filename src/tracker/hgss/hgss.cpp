#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/hgss_teams.inc"
#include "tracker/generated/hgss_stops.inc"
}

const TrackerAtlas& hgssAtlas() {
    static const TrackerAtlas atlas{"hgss", kStops_hgss,
        kStarters_hgss};
    return atlas;
}

}
