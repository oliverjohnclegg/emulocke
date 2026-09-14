#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/pt_teams.inc"
#include "tracker/generated/pt_stops.inc"
}

const TrackerAtlas& ptAtlas() {
    static const TrackerAtlas atlas{"pt", kStops_pt,
        kStarters_pt};
    return atlas;
}

}
