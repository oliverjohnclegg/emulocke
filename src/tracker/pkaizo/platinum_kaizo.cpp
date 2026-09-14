#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/platinum-kaizo_teams.inc"
#include "tracker/generated/platinum-kaizo_stops.inc"
}

const TrackerAtlas& platinum_kaizoAtlas() {
    static const TrackerAtlas atlas{"platinum-kaizo", kStops_platinum_kaizo,
        kStarters_platinum_kaizo};
    return atlas;
}

}
