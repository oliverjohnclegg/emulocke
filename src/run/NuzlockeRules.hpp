#pragma once

namespace emulocke {

struct NuzlockeRules {
    bool firstEncounter = true;
    bool nicknames = true;
    bool faintIsDeath = true;
    bool setMode = false;
    bool noItemsInBattle = false;
    bool levelCap = false;
    bool dupesClause = true;
    bool shinyClause = true;

    bool operator==(const NuzlockeRules&) const = default;
};

NuzlockeRules regularRules();
NuzlockeRules hardcoreRules();
const char* rulesLabel(const NuzlockeRules& rules);
const char* rulesPresetTitle(const NuzlockeRules& rules);

}