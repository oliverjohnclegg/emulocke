#include "run/RunLabel.hpp"

#include "run/Catalog.hpp"
#include "run/NuzlockeRules.hpp"

namespace emulocke {

std::string runHeadline(const Run& run) {
    const CatalogTitle* title = catalogByUuid(run.catalogUuid);
    const char* name = title ? title->fullName : "Pokemon";
    return std::string(name) + ": " + rulesPresetTitle(run.rules) + " Nuzlocke  |  Attempt #" +
        std::to_string(run.attempt);
}

}