#include "cheats/Uuid.hpp"

#include "emu/Paths.hpp"

#include <cctype>
#include <string>

namespace emulocke {

bool catalogUuidOk(std::string_view uuid) {
    if (uuid.size() != 36) {
        return false;
    }
    for (std::size_t i = 0; i < uuid.size(); ++i) {
        const char c = uuid[i];
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            if (c != '-') {
                return false;
            }
            continue;
        }
        if (!std::isxdigit(static_cast<unsigned char>(c)) || std::isupper(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

std::filesystem::path cheatGamePath(std::string_view catalogUuid) {
    if (!catalogUuidOk(catalogUuid)) {
        return {};
    }
    return prefDir() / "cheats" / (std::string(catalogUuid) + ".ini");
}

}
