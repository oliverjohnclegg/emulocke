#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/sacredgold_teams.inc"
#include "tracker/generated/sacredgold_stops.inc"
}

const TrackerAtlas& sacredgoldAtlas() {
    static const TrackerAtlas atlas{"sacredgold", kStops_sacredgold,
        kStarters_sacredgold};
    return atlas;
}

}
