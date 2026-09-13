#include "cart/GameArt.hpp"

#include "cart/GameArtCanvas.hpp"
#include "cart/GameIndex.hpp"
#include "emu/Paths.hpp"
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

std::filesystem::path bundledArt(std::string_view slug) {
    return assetsDir() / "game-art" / (normalizeSlug(slug) + ".png");
}

}  // namespace

GameArtCache::GameArtCache(std::filesystem::path cacheDir) : cacheDir_(std::move(cacheDir)) {}

std::filesystem::path GameArtCache::cacheFile(std::string_view slug) const {
    return cacheDir_ / (normalizeSlug(slug) + ".png");
}

std::filesystem::path GameArtCache::plateFile(std::string_view slug) const {
    return cacheDir_ / "plates" / (normalizeSlug(slug) + ".png");
}

std::filesystem::path GameArtCache::ensurePlate(std::string_view slug) {
    const auto bundled = bundledArt(slug);
    if (isCachedArt(bundled)) {
        return bundled;
    }
    const auto plate = plateFile(slug);
    if (isCachedArt(plate)) {
        return plate;
    }
    std::error_code ec;
    std::filesystem::create_directories(plate.parent_path(), ec);
    writeTitlePlate(gameArtTitle(slug), plate);
    return plate;
}

std::filesystem::path GameArtCache::existing(std::string_view slug) {
    std::lock_guard lock(mu_);
    const auto cached = cacheFile(slug);
    if (isCachedArt(cached)) {
        return cached;
    }
    return ensurePlate(slug);
}

std::optional<std::filesystem::path> GameArtCache::ifReady(std::string_view slug) const {
    std::lock_guard lock(mu_);
    const auto cached = cacheFile(slug);
    if (isCachedArt(cached)) {
        return cached;
    }
    const auto bundled = bundledArt(slug);
    if (isCachedArt(bundled)) {
        return bundled;
    }
    const auto plate = plateFile(slug);
    if (isCachedArt(plate)) {
        return plate;
    }
    return std::nullopt;
}

std::filesystem::path GameArtCache::get(std::string_view slug) {
    const std::string key = normalizeSlug(slug);
    {
        std::lock_guard lock(mu_);
        const auto cached = cacheFile(slug);
        if (isCachedArt(cached)) {
            return cached;
        }
        if (misses_.count(key)) {
            return ensurePlate(slug);
        }
    }
    const auto url = gameArtUrl(slug);
    if (url) {
        if (const auto bytes = httpGetPng(*url)) {
            std::lock_guard lock(mu_);
            const auto cached = cacheFile(slug);
            if (isCachedArt(cached)) {
                return cached;
            }
            std::error_code ec;
            std::filesystem::create_directories(cached.parent_path(), ec);
            if (writeLetterboxedPng(*bytes, cached) && isCachedArt(cached)) {
                return cached;
            }
            misses_.insert(key);
            return ensurePlate(slug);
        }
        std::lock_guard lock(mu_);
        misses_.insert(key);
        return ensurePlate(slug);
    }
    std::lock_guard lock(mu_);
    return ensurePlate(slug);
}

}
