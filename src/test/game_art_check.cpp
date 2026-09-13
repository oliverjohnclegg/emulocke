#include "cart/GameArt.hpp"
#include "cart/GameArtCanvas.hpp"
#include "cart/GameArtPng.hpp"
#include "cart/GameIndex.hpp"
#include "emu/Paths.hpp"

#include <SDL3/SDL.h>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <optional>
#include <string>
#include <system_error>
#include <vector>

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

std::optional<emulocke::RgbaImage> loadCanvas(const std::filesystem::path& path) {
    std::ifstream in(path, std::ios::binary);
    std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return emulocke::decodePngRgba(bytes);
}

bool noSideBars(const std::filesystem::path& path) {
    const auto img = loadCanvas(path);
    if (!img || img->width != emulocke::kGameArtWidth || img->height != emulocke::kGameArtHeight) {
        return false;
    }
    auto darkCol = [&](int x) {
        for (int y = 0; y < img->height; ++y) {
            const uint8_t* px = img->pixels.data() + (static_cast<size_t>(y) * img->width + x) * 4;
            if (px[0] + px[1] + px[2] > 24) {
                return false;
            }
        }
        return true;
    };
    int left = 0;
    int right = 0;
    while (left < img->width && darkCol(left)) {
        ++left;
    }
    while (right < img->width && darkCol(img->width - 1 - right)) {
        ++right;
    }
    return left < 24 && right < 24;
}

bool stackedTopSurvives(const std::filesystem::path& dir) {
    std::vector<uint8_t> stacked(static_cast<size_t>(256) * 384 * 4, 0);
    for (int y = 0; y < 192; ++y) {
        for (int x = 0; x < 256; ++x) {
            uint8_t* px = stacked.data() + (static_cast<size_t>(y) * 256 + x) * 4;
            px[0] = 200;
            px[3] = 255;
        }
    }
    for (int y = 192; y < 384; ++y) {
        for (int x = 0; x < 256; ++x) {
            uint8_t* px = stacked.data() + (static_cast<size_t>(y) * 256 + x) * 4;
            px[2] = 200;
            px[3] = 255;
        }
    }
    const auto src = dir / "stack-src.png";
    const auto out = dir / "stack-out.png";
    std::error_code ec;
    std::filesystem::create_directories(dir, ec);
    if (!emulocke::writeRgbaPng(src, 256, 384, stacked.data())) {
        return false;
    }
    std::ifstream in(src, std::ios::binary);
    std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    if (!emulocke::writeFittedPng(bytes, out)) {
        return false;
    }
    const auto img = loadCanvas(out);
    if (!img || img->width != 256 || img->height != 192) {
        return false;
    }
    const uint8_t* tl = img->pixels.data();
    const uint8_t* br = img->pixels.data() + (191 * 256 + 255) * 4;
    return tl[0] == 200 && tl[2] == 0 && br[0] == 200 && br[2] == 0;
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
    if (emulocke::gameArtSlug("blaze-black-3.1") != "blaze-black") {
        return fail("blaze black slug");
    }
    if (emulocke::gameArtSlug("volt-white-2-redux") != "volt-white-2") {
        return fail("vw2 slug");
    }
    if (emulocke::gameArtSlug("volt-white-3.1") != "volt-white") {
        return fail("volt white slug");
    }
    if (emulocke::gameArtSlug("fire-red-omega") != "fire-red-omega") {
        return fail("fro slug");
    }
    if (emulocke::gameArtTitle("sacred-gold") != "SACRED GOLD") {
        return fail("sacred gold title");
    }
    if (emulocke::gameArtTitle("platinum-kaizo") != "PLATINUM KAIZO") {
        return fail("platinum kaizo title");
    }
    if (emulocke::gameArtTitle("run-and-bun") != "RUN AND BUN") {
        return fail("run and bun title");
    }
    if (emulocke::gameArtUrl("blaze-black") || emulocke::gameArtUrl("inclement-emerald")) {
        return fail("hack url");
    }

    emulocke::GameArtCache cache(emulocke::localDataPath("game-art"));
    if (!stackedTopSurvives(std::filesystem::path(emulocke::localDataPath("game-art")))) {
        return fail("stacked ds title crop");
    }
    const auto firered = cache.get("firered");
    const auto heartgold = cache.get("heartgold");
    const auto unbound = cache.get("unbound");
    const auto blaze = cache.get("blaze-black");
    const auto missing = cache.get("not-a-game");
    std::printf("firered    %s\n", firered.string().c_str());
    std::printf("heartgold  %s\n", heartgold.string().c_str());
    std::printf("unbound    %s\n", unbound.string().c_str());
    std::printf("missing    %s\n", missing.string().c_str());

    if (!isCanvas(firered) || isPlate(firered) || !noSideBars(firered)) {
        return fail("expected firered title art");
    }
    if (!isCanvas(heartgold) || isPlate(heartgold) || !noSideBars(heartgold)) {
        return fail("expected heartgold title art");
    }
    if (!isCanvas(unbound) || isPlate(unbound)) {
        return fail("expected unbound still");
    }
    if (!isCanvas(blaze) || isPlate(blaze)) {
        return fail("expected blaze still");
    }
    for (const char* slug : {"radical-red", "volt-white", "volt-white-2", "sacred-gold",
                             "renegade-platinum", "platinum-kaizo", "fire-red-omega",
                             "inclement-emerald", "emerald-kaizo", "run-and-bun"}) {
        const auto art = cache.get(slug);
        if (!isCanvas(art) || isPlate(art)) {
            return fail(slug);
        }
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
