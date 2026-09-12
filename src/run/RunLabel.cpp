#include "run/RunLabel.hpp"

#include "run/GameId.hpp"
#include "run/NuzlockeRules.hpp"

namespace emulocke {

std::string runHeadline(const Run& run) {
    return std::string(gameFullName(run.gameId)) + ": " + rulesPresetTitle(run.rules) +
        " Nuzlocke  |  Attempt #" + std::to_string(run.attempt);
}

}
