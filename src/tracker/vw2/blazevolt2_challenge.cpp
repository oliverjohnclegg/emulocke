#include "tracker/Atlas.hpp"

namespace emulocke {
namespace {
#include "tracker/generated/blazevolt2-challenge_teams.inc"
#include "tracker/generated/blazevolt2-challenge_stops.inc"
}

const TrackerAtlas& blazevolt2_challengeAtlas() {
    static const TrackerAtlas atlas{"blazevolt2-challenge", kStops_blazevolt2_challenge,
        kStarters_blazevolt2_challenge};
    return atlas;
}

}
