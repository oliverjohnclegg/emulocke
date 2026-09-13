#pragma once

#include "run/NuzlockeRules.hpp"

#include <cstdint>
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
    uint64_t playMs = 0;
    std::string difficulty;

    const std::string& lineageKey() const {
        return lineageId.empty() ? id : lineageId;
    }
};

struct NewRunDraft {
    std::string catalogUuid;
    NuzlockeRules rules = regularRules();
};

}