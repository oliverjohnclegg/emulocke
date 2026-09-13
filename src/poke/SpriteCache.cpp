#include "poke/Sprites.hpp"

#include "poke/HttpGet.hpp"
#include "poke/SpriteIndex.hpp"
#include "poke/SpriteUrls.hpp"

#include <algorithm>
#include <fstream>

namespace emulocke {
namespace {

const char* kindDir(SpriteKind kind) {
    switch (kind) {
        case SpriteKind::Box:
            return "box";
        case SpriteKind::Front:
            return "front";
        case SpriteKind::Back:
            return "back";
    }
    return "box";
}

bool isPngFile(const std::filesystem::path& path) {
    std::ifstream in(path, std::ios::binary);
    unsigned char sig[8];
    if (!in.read(reinterpret_cast<char*>(sig), 8)) {
        return false;
    }
    static const unsigned char png[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    return std::equal(std::begin(png), std::end(png), sig);
}

std::string missKey(SpriteKind kind, std::string_view slug) {
    return std::string(1, "bfk"[static_cast<int>(kind)]) + normalizeSlug(slug);
}

}  // namespace

SpriteCache::SpriteCache(std::filesystem::path cacheDir, std::filesystem::path fallbackDir)
    : cacheDir_(std::move(cacheDir)), fallbackDir_(std::move(fallbackDir)) {}

std::filesystem::path SpriteCache::cacheFile(std::string_view slug, SpriteKind kind) const {
    return cacheDir_ / kindDir(kind) / (normalizeSlug(slug) + ".png");
}

std::filesystem::path SpriteCache::fallbackFile(SpriteKind kind) const {
    if (kind == SpriteKind::Box) {
        return fallbackDir_ / "missing-box.png";
    }
    return fallbackDir_ / "missing-front.png";
}

std::filesystem::path SpriteCache::get(std::string_view slug, SpriteKind kind) {
    const std::string key = missKey(kind, slug);
    const auto cached = cacheFile(slug, kind);
    if (std::filesystem::exists(cached) && isPngFile(cached)) {
        return cached;
    }
    if (misses_.count(key)) {
        if (kind == SpriteKind::Back) {
            return get(slug, SpriteKind::Front);
        }
        return fallbackFile(kind);
    }
    for (const auto& url : spriteUrls(slug, kind)) {
        if (const auto bytes = httpGetPng(url)) {
            std::error_code ec;
            std::filesystem::create_directories(cached.parent_path(), ec);
            std::ofstream out(cached, std::ios::binary | std::ios::trunc);
            out.write(reinterpret_cast<const char*>(bytes->data()),
                      static_cast<std::streamsize>(bytes->size()));
            if (out) {
                return cached;
            }
        }
    }
    misses_.insert(key);
    if (kind == SpriteKind::Back) {
        return get(slug, SpriteKind::Front);
    }
    return fallbackFile(kind);
}

std::optional<std::filesystem::path> SpriteCache::ifReady(std::string_view slug, SpriteKind kind) const {
    const auto cached = cacheFile(slug, kind);
    if (std::filesystem::exists(cached) && isPngFile(cached)) {
        return cached;
    }
    return std::nullopt;
}

}  // namespace emulocke
