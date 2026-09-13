#include "poke/Sprites.hpp"

#include "poke/HttpGet.hpp"
#include "poke/SpriteIndex.hpp"
#include "poke/SpriteUrls.hpp"

#include <algorithm>
#include <fstream>
#include <vector>

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

bool readyPng(const std::filesystem::path& path) {
    return std::filesystem::exists(path) && isPngFile(path);
}

bool writePngAtomic(const std::filesystem::path& dest, const std::vector<uint8_t>& bytes) {
    std::error_code ec;
    std::filesystem::create_directories(dest.parent_path(), ec);
    auto part = dest;
    part += ".part";
    {
        std::ofstream out(part, std::ios::binary | std::ios::trunc);
        out.write(reinterpret_cast<const char*>(bytes.data()), static_cast<std::streamsize>(bytes.size()));
        if (!out) {
            return false;
        }
    }
    std::filesystem::rename(part, dest, ec);
    return !ec;
}

}  // namespace

SpriteCache::SpriteCache(std::filesystem::path cacheDir, std::filesystem::path fallbackDir)
    : cacheDir_(std::move(cacheDir)), fallbackDir_(std::move(fallbackDir)) {
    worker_ = std::thread([this] { workerLoop(); });
}

SpriteCache::~SpriteCache() {
    {
        std::lock_guard lock(mu_);
        stop_ = true;
    }
    cv_.notify_all();
    if (worker_.joinable()) {
        worker_.join();
    }
}

std::filesystem::path SpriteCache::cacheFile(std::string_view slug, SpriteKind kind) const {
    return cacheDir_ / kindDir(kind) / (normalizeSlug(slug) + ".png");
}

std::filesystem::path SpriteCache::fallbackFile(SpriteKind kind) const {
    if (kind == SpriteKind::Box) {
        return fallbackDir_ / "missing-box.png";
    }
    return fallbackDir_ / "missing-front.png";
}

std::filesystem::path SpriteCache::fallbackOrFront(std::string_view slug, SpriteKind kind) {
    if (kind == SpriteKind::Back) {
        return get(slug, SpriteKind::Front);
    }
    return fallbackFile(kind);
}

std::filesystem::path SpriteCache::peek(std::string_view slug, SpriteKind kind) const {
    const auto cached = cacheFile(slug, kind);
    if (readyPng(cached)) {
        return cached;
    }
    return {};
}

void SpriteCache::request(std::string_view slug, SpriteKind kind) {
    if (slug.empty()) {
        return;
    }
    const std::string key = missKey(kind, slug);
    {
        std::lock_guard lock(mu_);
        if (stop_ || misses_.count(key) || queued_.count(key)) {
            return;
        }
        if (readyPng(cacheFile(slug, kind))) {
            return;
        }
        queued_.insert(key);
        jobs_.push(Job{std::string(slug), kind});
    }
    cv_.notify_one();
}

void SpriteCache::fetch(std::string_view slug, SpriteKind kind) {
    const std::string key = missKey(kind, slug);
    {
        std::lock_guard lock(mu_);
        if (misses_.count(key)) {
            return;
        }
    }
    const auto cached = cacheFile(slug, kind);
    if (readyPng(cached)) {
        return;
    }
    for (const auto& url : spriteUrls(slug, kind)) {
        if (const auto bytes = httpGetPng(url)) {
            if (writePngAtomic(cached, *bytes)) {
                return;
            }
        }
    }
    std::lock_guard lock(mu_);
    misses_.insert(key);
}

void SpriteCache::workerLoop() {
    while (true) {
        Job job;
        {
            std::unique_lock lock(mu_);
            cv_.wait(lock, [&] { return stop_ || !jobs_.empty(); });
            if (stop_ && jobs_.empty()) {
                return;
            }
            job = std::move(jobs_.front());
            jobs_.pop();
        }
        fetch(job.slug, job.kind);
        {
            std::lock_guard lock(mu_);
            queued_.erase(missKey(job.kind, job.slug));
        }
    }
}

std::filesystem::path SpriteCache::get(std::string_view slug, SpriteKind kind) {
    const std::string key = missKey(kind, slug);
    const auto cached = cacheFile(slug, kind);
    if (readyPng(cached)) {
        return cached;
    }
    {
        std::lock_guard lock(mu_);
        if (misses_.count(key)) {
            return fallbackOrFront(slug, kind);
        }
    }
    fetch(slug, kind);
    if (readyPng(cached)) {
        return cached;
    }
    {
        std::lock_guard lock(mu_);
        misses_.insert(key);
    }
    return fallbackOrFront(slug, kind);
}

}  // namespace emulocke
