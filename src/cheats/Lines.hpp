#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace emulocke {

std::string_view trimCheat(std::string_view text);
bool cheatComment(std::string_view line);
std::vector<std::string> cheatLines(std::string_view code);
bool parseArWords(std::string_view code, std::vector<uint32_t>& words);

}
