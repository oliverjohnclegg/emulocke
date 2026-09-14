#include "tracker/Difficulty.hpp"

#include <string>

namespace emulocke {
namespace {

bool slugHas(std::string_view slug, const char* token) {
    return slug.find(token) != std::string_view::npos;
}

constexpr DifficultyChoice kRr[] = {
    {"easy", "Easy"},
    {"normal", "Normal"},
    {"hardcore", "Hardcore"},
    {"restricted", "Restricted"},
};
constexpr DifficultyChoice kUnbound[] = {
    {"vanilla", "Vanilla"},
    {"difficult", "Difficult"},
    {"expert", "Expert"},
    {"insane", "Insane"},
};
constexpr DifficultyChoice kVw2[] = {
    {"standard", "Standard"},
    {"challenge", "Challenge"},
};
constexpr DifficultyChoice kInclement[] = {
    {"easy", "Easy"},
    {"normal", "Normal"},
    {"hard", "Hard"},
};

}  // namespace

std::span<const DifficultyChoice> titleDifficultyChoices(std::string_view slug) {
    if (slugHas(slug, "radical-red")) {
        return kRr;
    }
    if (slugHas(slug, "unbound")) {
        return kUnbound;
    }
    if (slugHas(slug, "volt-white-2")) {
        return kVw2;
    }
    if (slugHas(slug, "inclement")) {
        return kInclement;
    }
    return {};
}

const char* titleDefaultDifficulty(std::string_view slug) {
    if (slugHas(slug, "radical-red")) {
        return "normal";
    }
    if (slugHas(slug, "unbound")) {
        return "difficult";
    }
    if (slugHas(slug, "volt-white-2")) {
        return "standard";
    }
    if (slugHas(slug, "inclement")) {
        return "normal";
    }
    return "";
}

void bindTitleDifficulty(std::string& difficulty, std::string_view slug) {
    for (const DifficultyChoice& choice : titleDifficultyChoices(slug)) {
        if (difficulty == choice.id) {
            return;
        }
    }
    difficulty = titleDefaultDifficulty(slug);
}

}
