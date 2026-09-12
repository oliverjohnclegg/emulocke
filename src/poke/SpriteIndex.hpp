#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

namespace emulocke {

std::string normalizeSlug(std::string_view raw);
std::optional<uint16_t> pokemonId(std::string_view slug);

}
