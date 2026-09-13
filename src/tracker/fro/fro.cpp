#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/fro_teams.inc"
#include "tracker/generated/fro_stops.inc"
}

const TrackerAtlas& froAtlas() {
    static const TrackerAtlas atlas{"fro", kStops_fro,
        kStarters_fro};
    return atlas;
}

}
