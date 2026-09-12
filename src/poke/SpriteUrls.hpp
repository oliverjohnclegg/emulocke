#pragma once

#include "poke/Sprites.hpp"

#include <string>
#include <string_view>
#include <vector>

namespace emulocke {

std::vector<std::string> spriteUrls(std::string_view slug, SpriteKind kind);

}
