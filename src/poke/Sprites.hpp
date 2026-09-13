#pragma once

#include <condition_variable>
#include <filesystem>
#include <mutex>
#include <optional>
#include <queue>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_set>

namespace emulocke {

enum class SpriteKind { Box, Front, Back };

class SpriteCache {
public:
    SpriteCache(std::filesystem::path cacheDir, std::filesystem::path fallbackDir);
    ~SpriteCache();
    SpriteCache(const SpriteCache&) = delete;
    SpriteCache& operator=(const SpriteCache&) = delete;
    std::filesystem::path get(std::string_view slug, SpriteKind kind);
    std::filesystem::path peek(std::string_view slug, SpriteKind kind) const;
    void request(std::string_view slug, SpriteKind kind);
    std::optional<std::filesystem::path> ifReady(std::string_view slug, SpriteKind kind) const;

private:
    struct Job {
        std::string slug;
        SpriteKind kind;
    };

    std::filesystem::path cacheFile(std::string_view slug, SpriteKind kind) const;
    std::filesystem::path fallbackFile(SpriteKind kind) const;
    std::filesystem::path fallbackOrFront(std::string_view slug, SpriteKind kind);
    void fetch(std::string_view slug, SpriteKind kind);
    void workerLoop();

    std::filesystem::path cacheDir_;
    std::filesystem::path fallbackDir_;
    std::unordered_set<std::string> misses_;
    std::unordered_set<std::string> queued_;
    std::queue<Job> jobs_;
    std::mutex mu_;
    std::condition_variable cv_;
    std::thread worker_;
    bool stop_{false};
};

}
