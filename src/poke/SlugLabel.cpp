#include "poke/SlugLabel.hpp"

#include "poke/SpriteIndex.hpp"

#include <cctype>
#include <string>

namespace emulocke {

bool knownPokemonSlug(std::string_view slug) {
    if (pokemonId(slug)) {
        return true;
    }
    const std::string key = normalizeSlug(slug);
    const auto dash = key.find('-');
    if (dash == std::string::npos || dash == 0) {
        return false;
    }
    return pokemonId(key.substr(0, dash)).has_value();
}

std::string slugDisplayName(std::string_view slug) {
    const std::string key = normalizeSlug(slug);
    std::string out;
    out.reserve(key.size());
    bool upper = true;
    for (char c : key) {
        if (c == '-') {
            out.push_back(' ');
            upper = true;
            continue;
        }
        const unsigned char u = static_cast<unsigned char>(c);
        if (std::isalpha(u)) {
            out.push_back(static_cast<char>(upper ? std::toupper(u) : std::tolower(u)));
            upper = false;
        } else {
            out.push_back(c);
            upper = !std::isalnum(u);
        }
    }
    return out;
}

}
