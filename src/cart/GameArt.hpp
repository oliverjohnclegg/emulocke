#pragma once

#include <filesystem>
#include <mutex>
#include <optional>
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
    std::filesystem::path existing(std::string_view slug);
    std::optional<std::filesystem::path> ifReady(std::string_view slug) const;

private:
    std::filesystem::path cacheFile(std::string_view slug) const;
    std::filesystem::path plateFile(std::string_view slug) const;
    std::filesystem::path ensurePlate(std::string_view slug);

    std::filesystem::path cacheDir_;
    std::unordered_set<std::string> misses_;
    mutable std::mutex mu_;
};

bool gameArtPngSize(const std::filesystem::path& path, int& width, int& height);

}
