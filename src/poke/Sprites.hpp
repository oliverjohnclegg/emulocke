#pragma once

#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_set>

namespace emulocke {

enum class SpriteKind { Box, Front, Back };

class SpriteCache {
public:
    SpriteCache(std::filesystem::path cacheDir, std::filesystem::path fallbackDir);
    std::filesystem::path get(std::string_view slug, SpriteKind kind);
    std::optional<std::filesystem::path> ifReady(std::string_view slug, SpriteKind kind) const;

private:
    std::filesystem::path cacheFile(std::string_view slug, SpriteKind kind) const;
    std::filesystem::path fallbackFile(SpriteKind kind) const;

    std::filesystem::path cacheDir_;
    std::filesystem::path fallbackDir_;
    std::unordered_set<std::string> misses_;
};

}
