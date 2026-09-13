#include "cart/GameArt.hpp"
#include "cart/GameIndex.hpp"
#include "emu/Paths.hpp"

#include <SDL3/SDL.h>
#include <cstdio>
#include <filesystem>
#include <string>

namespace {

int fail(const char* msg) {
    std::fprintf(stderr, "%s\n", msg);
    return 1;
}

bool isPlate(const std::filesystem::path& path) {
    return path.parent_path().filename() == "plates";
}

bool isCanvas(const std::filesystem::path& path) {
    int width = 0;
    int height = 0;
    return std::filesystem::exists(path) && emulocke::gameArtPngSize(path, width, height) &&
           width == emulocke::kGameArtWidth && height == emulocke::kGameArtHeight;
}

}  // namespace

int main() {
    if (!SDL_Init(SDL_INIT_EVENTS)) {
        std::fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    if (emulocke::gameArtTitle("firered") != "FIRE RED") {
        return fail("firered title");
    }
    if (emulocke::gameArtTitle("unbound") != "UNBOUND") {
        return fail("unbound title");
    }
    if (emulocke::gameArtTitle("radical-red") != "RADICAL RED") {
        return fail("hack title");
    }
    if (!emulocke::gameArtUrl("firered") || emulocke::gameArtUrl("unbound")) {
        return fail("url catalog");
    }
    if (emulocke::gameArtSlug("firered-us-1.0") != "firered") {
        return fail("firered catalog slug");
    }
    if (emulocke::gameArtSlug("black2-us") != "black-2") {
        return fail("black2 catalog slug");
    }
    if (emulocke::gameArtSlug("unbound-2.1.1.1") != "unbound") {
        return fail("unbound catalog slug");
    }

    emulocke::GameArtCache cache(emulocke::localDataPath("game-art"));
    const auto firered = cache.get("firered");
    const auto unbound = cache.get("unbound");
    const auto missing = cache.get("not-a-game");
    std::printf("firered  %s\n", firered.string().c_str());
    std::printf("unbound  %s\n", unbound.string().c_str());
    std::printf("missing  %s\n", missing.string().c_str());

    if (!isCanvas(firered) || isPlate(firered)) {
        return fail("expected firered title art");
    }
    if (!isCanvas(unbound) || !isPlate(unbound)) {
        return fail("expected unbound plate");
    }
    if (!isCanvas(missing) || !isPlate(missing)) {
        return fail("expected missing plate");
    }

    const auto again = cache.get("firered");
    if (again != firered || !std::filesystem::exists(again)) {
        return fail("cache hit");
    }
    SDL_Quit();
    return 0;
}
