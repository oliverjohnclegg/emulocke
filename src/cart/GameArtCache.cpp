#include "cart/GameArt.hpp"

#include "cart/GameArtCanvas.hpp"
#include "cart/GameIndex.hpp"
#include "poke/HttpGet.hpp"
#include "poke/SpriteIndex.hpp"

namespace emulocke {
namespace {

bool isCachedArt(const std::filesystem::path& path) {
    int width = 0;
    int height = 0;
    return std::filesystem::exists(path) && gameArtPngSize(path, width, height) &&
           width == kGameArtWidth && height == kGameArtHeight;
}

}  // namespace

GameArtCache::GameArtCache(std::filesystem::path cacheDir) : cacheDir_(std::move(cacheDir)) {}

std::filesystem::path GameArtCache::cacheFile(std::string_view slug) const {
    return cacheDir_ / (normalizeSlug(slug) + ".png");
}

std::filesystem::path GameArtCache::plateFile(std::string_view slug) const {
    return cacheDir_ / "plates" / (normalizeSlug(slug) + ".png");
}

std::filesystem::path GameArtCache::get(std::string_view slug) {
    const std::string key = normalizeSlug(slug);
    const auto cached = cacheFile(slug);
    if (isCachedArt(cached)) {
        return cached;
    }
    const auto plate = plateFile(slug);
    const auto url = gameArtUrl(slug);
    if (!misses_.count(key) && url) {
        if (const auto bytes = httpGetPng(*url)) {
            std::error_code ec;
            std::filesystem::create_directories(cached.parent_path(), ec);
            if (writeLetterboxedPng(*bytes, cached) && isCachedArt(cached)) {
                return cached;
            }
        }
        misses_.insert(key);
    }
    if (isCachedArt(plate)) {
        return plate;
    }
    std::error_code ec;
    std::filesystem::create_directories(plate.parent_path(), ec);
    writeTitlePlate(gameArtTitle(slug), plate);
    return plate;
}

std::optional<std::filesystem::path> GameArtCache::ifReady(std::string_view slug) const {
    const auto cached = cacheFile(slug);
    if (isCachedArt(cached)) {
        return cached;
    }
    const auto plate = plateFile(slug);
    if (isCachedArt(plate)) {
        return plate;
    }
    return std::nullopt;
}

}
