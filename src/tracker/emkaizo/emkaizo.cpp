#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/emkaizo_teams.inc"
#include "tracker/generated/emkaizo_stops.inc"
}

const TrackerAtlas& emkaizoAtlas() {
    static const TrackerAtlas atlas{"emkaizo", kStops_emkaizo,
        kStarters_emkaizo};
    return atlas;
}

}
