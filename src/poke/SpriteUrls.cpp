#include "poke/SpriteUrls.hpp"

#include "poke/SpriteIndex.hpp"

namespace emulocke {

std::vector<std::string> spriteUrls(std::string_view slug, SpriteKind kind) {
    const std::string key = normalizeSlug(slug);
    const auto id = pokemonId(key);
    std::vector<std::string> urls;
    if (kind == SpriteKind::Box) {
        urls.push_back(
            "https://raw.githubusercontent.com/msikma/pokesprite/master/pokemon-gen8/regular/" +
            key + ".png");
        urls.push_back(
            "https://raw.githubusercontent.com/bamq/pokemon-sprites/main/pokemon/regular/" + key +
            ".png");
        if (id) {
            const std::string n = std::to_string(*id);
            urls.push_back(
                "https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/"
                "versions/generation-viii/icons/" +
                n + ".png");
            urls.push_back(
                "https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/" + n +
                ".png");
        }
        return urls;
    }
    if (!id) {
        return urls;
    }
    const std::string n = std::to_string(*id);
    if (kind == SpriteKind::Front) {
        urls.push_back("https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/" +
                       n + ".png");
        urls.push_back(
            "https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/versions/"
            "generation-v/black-white/" +
            n + ".png");
    } else {
        urls.push_back(
            "https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/back/" + n +
            ".png");
        urls.push_back(
            "https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/versions/"
            "generation-v/black-white/back/" +
            n + ".png");
    }
    return urls;
}

}  // namespace emulocke
