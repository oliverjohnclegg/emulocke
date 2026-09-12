#include "run/NuzlockeRules.hpp"

namespace emulocke {

NuzlockeRules regularRules() {
    return NuzlockeRules{};
}

NuzlockeRules hardcoreRules() {
    NuzlockeRules rules;
    rules.setMode = true;
    rules.noItemsInBattle = true;
    rules.levelCap = true;
    return rules;
}

const char* rulesLabel(const NuzlockeRules& rules) {
    if (rules == regularRules()) {
        return "REGULAR";
    }
    if (rules == hardcoreRules()) {
        return "HARDCORE";
    }
    return "CUSTOM";
}

const char* rulesPresetTitle(const NuzlockeRules& rules) {
    if (rules == regularRules()) {
        return "Regular";
    }
    if (rules == hardcoreRules()) {
        return "Hardcore";
    }
    return "Custom";
}

}
