#pragma once

#include <span>
#include <string_view>

namespace emulocke {

struct DifficultyChoice {
    const char* id;
    const char* label;
};

std::string_view atlasDifficultyKey(std::string_view slug, std::string_view raw);
std::span<const DifficultyChoice> titleDifficultyChoices(std::string_view slug);
const char* titleDefaultDifficulty(std::string_view slug);
void bindTitleDifficulty(std::string& difficulty, std::string_view slug);

}
