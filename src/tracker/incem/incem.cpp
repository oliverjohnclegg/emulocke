#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/incem_teams.inc"
#include "tracker/generated/incem_stops.inc"
}

const TrackerAtlas& incemAtlas() {
    static const TrackerAtlas atlas{"incem", kStops_incem,
        kStarters_incem};
    return atlas;
}

}
