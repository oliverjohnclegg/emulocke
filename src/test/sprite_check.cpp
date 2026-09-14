#include "emu/Paths.hpp"
#include "poke/SlugLabel.hpp"
#include "poke/SpriteIndex.hpp"
#include "poke/Sprites.hpp"
#include "cart/GameArtPng.hpp"
#include "cart/RgbaFit.hpp"
#include "ui/Tracker.hpp"

#include <SDL3/SDL.h>
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iterator>
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
    if (emulocke::pokemonId("meowscarada") != 908) {
        return fail("meowscarada id");
    }
    if (emulocke::pokemonId("deoxys") != 386) {
        return fail("deoxys id");
    }
    if (emulocke::pokemonId("shaymin") != 492) {
        return fail("shaymin id");
    }
    if (emulocke::pokemonId("squawkabilly") != 931) {
        return fail("squawkabilly id");
    }
    if (emulocke::speciesSlug("MEOWSCARADA") != "meowscarada") {
        return fail("meowscarada slug");
    }
    if (emulocke::speciesSlug("WALKING WAKE") != "walking-wake") {
        return fail("walking-wake slug");
    }
    if (emulocke::speciesSlug("GOUGING FIRE") != "gouging-fire") {
        return fail("gouging-fire slug");
    }
    if (!emulocke::pokemonId("muk-alola")) {
        return fail("muk-alola id");
    }
    if (emulocke::pokemonId("not-a-pokemon")) {
        return fail("garbage id");
    }
    if (emulocke::pokemonId("doubletrue") || emulocke::knownPokemonSlug("doubletrue") ||
        emulocke::knownPokemonSlug("effectsandstorm")) {
        return fail("note slug");
    }
    if (!emulocke::knownPokemonSlug("arceus-ground") || !emulocke::knownPokemonSlug("floette")) {
        return fail("form slug");
    }
    if (emulocke::slugDisplayName("floette") != "Floette") {
        return fail("floette label");
    }
    if (emulocke::slugDisplayName("beldum") != "Beldum") {
        return fail("beldum label");
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
        slugs = {"pikachu", "muk-alola", "sprigatito", "meowscarada", "not-a-pokemon"};
    } else {
        for (int i = 1; i < argc; ++i) {
            slugs.emplace_back(argv[i]);
        }
    }

    {
        const auto t0 = std::chrono::steady_clock::now();
        const auto peeked = cache.peek("not-a-pokemon-xyz", emulocke::SpriteKind::Box);
        const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                            std::chrono::steady_clock::now() - t0)
                            .count();
        if (!peeked.empty()) {
            return fail("peek miss should be empty");
        }
        if (ms > 200) {
            return fail("peek blocked");
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

    auto loadRgba = [](const std::filesystem::path& path) -> emulocke::RgbaImage {
        std::ifstream in(path, std::ios::binary);
        std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        auto image = emulocke::decodePngRgba(bytes);
        return image ? *image : emulocke::RgbaImage{};
    };
    auto contentMax = [](const emulocke::RgbaImage& src) {
        int minX = src.width;
        int minY = src.height;
        int maxX = -1;
        int maxY = -1;
        for (int y = 0; y < src.height; ++y) {
            for (int x = 0; x < src.width; ++x) {
                if (src.pixels[static_cast<std::size_t>((y * src.width + x) * 4 + 3)] >= 12) {
                    minX = std::min(minX, x);
                    minY = std::min(minY, y);
                    maxX = std::max(maxX, x);
                    maxY = std::max(maxY, y);
                }
            }
        }
        if (maxX < 0) {
            return 0;
        }
        return std::max(maxX - minX + 1, maxY - minY + 1);
    };
    const auto diglettPath = cache.get("diglett", emulocke::SpriteKind::Box);
    const auto zapdosPath = cache.get("zapdos", emulocke::SpriteKind::Box);
    const auto digRaw = loadRgba(diglettPath);
    const auto zapRaw = loadRgba(zapdosPath);
    if (contentMax(digRaw) >= contentMax(zapRaw)) {
        return fail("diglett should be the smaller raw sprite");
    }
    const auto digFit = emulocke::fitRgbaCell(digRaw, emulocke::kBoxSpriteW, emulocke::kBoxSpriteH);
    const auto zapFit = emulocke::fitRgbaCell(zapRaw, emulocke::kBoxSpriteW, emulocke::kBoxSpriteH);
    if (digFit.width != emulocke::kBoxSpriteW || digFit.height != emulocke::kBoxSpriteH ||
        zapFit.width != emulocke::kBoxSpriteW || zapFit.height != emulocke::kBoxSpriteH) {
        return fail("fit cell size");
    }
    const int digSpan = contentMax(digFit);
    const int zapSpan = contentMax(zapFit);
    if (digSpan < emulocke::kBoxSpriteH - 2 || zapSpan < emulocke::kBoxSpriteH - 2) {
        return fail("fit should fill the cell");
    }
    if (std::max(digSpan, zapSpan) > std::min(digSpan, zapSpan) * 2) {
        return fail("fit should normalise small and large sprites");
    }

    SDL_Quit();
    return 0;
}
