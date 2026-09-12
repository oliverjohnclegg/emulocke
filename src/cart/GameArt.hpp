#pragma once

#include <filesystem>
#include <string>
#include <string_view>
#include <unordered_set>

namespace emulocke {

constexpr int kGameArtWidth = 256;
constexpr int kGameArtHeight = 192;

class GameArtCache {
public:
    explicit GameArtCache(std::filesystem::path cacheDir);
    std::filesystem::path get(std::string_view slug);

private:
    std::filesystem::path cacheFile(std::string_view slug) const;
    std::filesystem::path plateFile(std::string_view slug) const;

    std::filesystem::path cacheDir_;
    std::unordered_set<std::string> misses_;
};

bool gameArtPngSize(const std::filesystem::path& path, int& width, int& height);

}
