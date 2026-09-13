#include "ui/MediaFetch.hpp"

#include "cart/GameArt.hpp"
#include "emu/Paths.hpp"
#include "poke/Sprites.hpp"

#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace emulocke {

struct MediaFetch::Impl {
    GameArtCache art;
    SpriteCache sprites;
    std::mutex mu;
    std::condition_variable cv;
    std::vector<std::pair<char, std::string>> queue;
    std::unordered_set<std::string> inflight;
    std::unordered_map<std::string, std::filesystem::path> done[2];
    std::thread thread;
    bool stop = false;

    Impl()
        : art(localDataPath("game-art")),
          sprites(localDataPath("sprites"), std::filesystem::path(assetPath("sprites"))) {}

    void request(char kind, const std::string& slug) {
        std::lock_guard lock(mu);
        const std::string key = std::string(1, kind) + slug;
        if (inflight.count(key)) {
            return;
        }
        inflight.insert(key);
        queue.emplace_back(kind, slug);
        cv.notify_one();
    }

    std::optional<std::filesystem::path> peek(char kind, const std::string& slug) {
        if (kind == 'a') {
            if (auto ready = art.ifReady(slug)) {
                return ready;
            }
        } else if (auto ready = sprites.ifReady(slug, SpriteKind::Box)) {
            return ready;
        }
        {
            std::lock_guard lock(mu);
            auto it = done[kind == 'a' ? 0 : 1].find(slug);
            if (it != done[kind == 'a' ? 0 : 1].end()) {
                return it->second;
            }
        }
        request(kind, slug);
        return std::nullopt;
    }

    void loop() {
        while (true) {
            std::pair<char, std::string> job;
            {
                std::unique_lock lock(mu);
                cv.wait(lock, [&] { return stop || !queue.empty(); });
                if (stop && queue.empty()) {
                    return;
                }
                job = std::move(queue.back());
                queue.pop_back();
            }
            const auto path = job.first == 'a' ? art.get(job.second) : sprites.get(job.second, SpriteKind::Box);
            std::lock_guard lock(mu);
            done[job.first == 'a' ? 0 : 1][job.second] = path;
            inflight.erase(std::string(1, job.first) + job.second);
        }
    }
};

MediaFetch::MediaFetch() : impl_(std::make_unique<Impl>()) {
    impl_->thread = std::thread([this] { impl_->loop(); });
}

MediaFetch::~MediaFetch() {
    {
        std::lock_guard lock(impl_->mu);
        impl_->stop = true;
    }
    impl_->cv.notify_one();
    if (impl_->thread.joinable()) {
        impl_->thread.join();
    }
}

std::optional<std::filesystem::path> MediaFetch::art(std::string_view slug) {
    return impl_->peek('a', std::string(slug));
}

std::optional<std::filesystem::path> MediaFetch::box(std::string_view slug) {
    return impl_->peek('b', std::string(slug));
}

}
