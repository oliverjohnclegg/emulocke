#pragma once

#include "run/NuzlockeRules.hpp"

#include <string>

namespace emulocke {

struct Run {
    std::string id;
    std::string lineageId;
    int attempt = 1;
    std::string catalogUuid;
    NuzlockeRules rules;
    std::string createdAt;
    std::string lastPlayedAt;

    const std::string& lineageKey() const {
        return lineageId.empty() ? id : lineageId;
    }
};

struct NewRunDraft {
    std::string catalogUuid;
    NuzlockeRules rules = regularRules();
};

}