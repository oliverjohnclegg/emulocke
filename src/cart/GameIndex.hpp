#pragma once

#include <optional>
#include <string>
#include <string_view>

namespace emulocke {

std::string gameArtTitle(std::string_view slug);
std::optional<std::string> gameArtUrl(std::string_view slug);
std::string gameArtSlug(std::string_view catalogSlug);

}
