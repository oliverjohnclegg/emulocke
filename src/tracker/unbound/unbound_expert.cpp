#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/unbound-expert_teams.inc"
#include "tracker/generated/unbound-expert_stops.inc"
}

const TrackerAtlas& unbound_expertAtlas() {
    static const TrackerAtlas atlas{"unbound-expert", kStops_unbound_expert,
        kStarters_unbound_expert};
    return atlas;
}

}
