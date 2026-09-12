#pragma once

#include "run/GameId.hpp"
#include "run/NuzlockeRules.hpp"

#include <string>

namespace emulocke {

struct Run {
    std::string id;
    std::string lineageId;
    int attempt = 1;
    GameId gameId{GameId::Ruby};
    std::string romPath;
    NuzlockeRules rules;
    std::string createdAt;
    std::string lastPlayedAt;

    const std::string& lineageKey() const {
        return lineageId.empty() ? id : lineageId;
    }
};

struct NewRunDraft {
    int gameIndex = 0;
    NuzlockeRules rules = regularRules();
};

}
