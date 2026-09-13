#include "emu/Paths.hpp"
#include "poke/SpriteIndex.hpp"
#include "poke/Sprites.hpp"

#include <SDL3/SDL.h>
#include <cstdio>
#include <filesystem>
#include <string>
#include <vector>

namespace {

int fail(const char* msg) {
    std::fprintf(stderr, "%s\n", msg);
    return 1;
}

}  // namespace

int main(int argc, char** argv) {
    if (!SDL_Init(SDL_INIT_EVENTS)) {
        std::fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    if (emulocke::pokemonId("pikachu") != 25) {
        return fail("pikachu id");
    }
    if (!emulocke::pokemonId("muk-alola")) {
        return fail("muk-alola id");
    }
    if (emulocke::pokemonId("not-a-pokemon")) {
        return fail("garbage id");
    }
    if (emulocke::normalizeSlug("MR. MIME") != "mr-mime") {
        return fail("mr mime slug");
    }
    if (emulocke::normalizeSlug("FARFETCH'D") != "farfetchd") {
        return fail("farfetchd slug");
    }
    if (emulocke::speciesSlug("BULBASAUR") != "bulbasaur") {
        return fail("bulbasaur slug");
    }
    if (emulocke::speciesSlug("TREECKO") != "treecko") {
        return fail("treecko slug");
    }
    if (!emulocke::speciesSlug("-----").empty() || !emulocke::speciesSlug("???").empty()) {
        return fail("empty slug");
    }

    emulocke::SpriteCache cache(emulocke::localDataPath("sprites"),
                                std::filesystem::path(emulocke::assetPath("sprites")));
    std::vector<std::string> slugs;
    if (argc <= 1) {
        slugs = {"pikachu", "muk-alola", "sprigatito", "not-a-pokemon"};
    } else {
        for (int i = 1; i < argc; ++i) {
            slugs.emplace_back(argv[i]);
        }
    }

    const auto missingBox = std::filesystem::path(emulocke::assetPath("sprites/missing-box.png"));
    const auto missingFront =
        std::filesystem::path(emulocke::assetPath("sprites/missing-front.png"));

    for (const auto& slug : slugs) {
        const auto box = cache.get(slug, emulocke::SpriteKind::Box);
        const auto front = cache.get(slug, emulocke::SpriteKind::Front);
        const auto back = cache.get(slug, emulocke::SpriteKind::Back);
        std::printf("%s\n  box   %s\n  front %s\n  back  %s\n", slug.c_str(), box.string().c_str(),
                    front.string().c_str(), back.string().c_str());
        if (!emulocke::pokemonId(slug)) {
            if (box != missingBox) {
                return fail("missing box");
            }
            if (front != missingFront) {
                return fail("missing front");
            }
            if (back != front) {
                return fail("missing back should be front");
            }
            continue;
        }
        if (!std::filesystem::exists(box) || box == missingBox) {
            return fail("expected box art");
        }
        if (!std::filesystem::exists(front) || front == missingFront) {
            return fail("expected front art");
        }
    }

    const auto again = cache.get("pikachu", emulocke::SpriteKind::Box);
    if (!std::filesystem::exists(again)) {
        return fail("cache hit");
    }
    SDL_Quit();
    return 0;
}
