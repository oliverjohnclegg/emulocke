#pragma once

#include <string>
#include <string_view>

namespace emulocke {

bool knownPokemonSlug(std::string_view slug);
std::string slugDisplayName(std::string_view slug);

}
