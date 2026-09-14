#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/renplat_teams.inc"
#include "tracker/generated/renplat_stops.inc"
}

const TrackerAtlas& renplatAtlas() {
    static const TrackerAtlas atlas{"renplat", kStops_renplat,
        kStarters_renplat};
    return atlas;
}

}
