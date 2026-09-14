#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/emrunbun_teams.inc"
#include "tracker/generated/emrunbun_stops.inc"
}

const TrackerAtlas& emrunbunAtlas() {
    static const TrackerAtlas atlas{"emrunbun", kStops_emrunbun,
        kStarters_emrunbun};
    return atlas;
}

}
