#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/volt_teams.inc"
#include "tracker/generated/volt_stops.inc"
}

const TrackerAtlas& voltAtlas() {
    static const TrackerAtlas atlas{"volt", kStops_volt,
        kStarters_volt};
    return atlas;
}

}
