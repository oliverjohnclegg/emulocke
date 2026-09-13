#include "run/RunLabel.hpp"

#include "run/Catalog.hpp"
#include "run/NuzlockeRules.hpp"

#include <cstdio>

namespace emulocke {

std::string runHeadline(const Run& run) {
    const CatalogTitle* title = catalogByUuid(run.catalogUuid);
    const char* name = title ? title->fullName : "Pokemon";
    return std::string(name) + ": " + rulesPresetTitle(run.rules) + " Nuzlocke  |  Attempt #" +
        std::to_string(run.attempt);
}

std::string formatPlayClock(uint64_t ms) {
    const uint64_t totalMinutes = ms / 60000ull;
    char buf[32];
    std::snprintf(buf, sizeof buf, "%02llu:%02llu",
        static_cast<unsigned long long>(totalMinutes / 60ull),
        static_cast<unsigned long long>(totalMinutes % 60ull));
    return buf;
}

}
