#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/em_teams.inc"
#include "tracker/generated/em_stops.inc"
}

const TrackerAtlas& emAtlas() {
    static const TrackerAtlas atlas{"em", kStops_em,
        kStarters_em};
    return atlas;
}

}
