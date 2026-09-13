#pragma once

#include <filesystem>
#include <memory>
#include <optional>
#include <string_view>

namespace emulocke {

class MediaFetch {
public:
    MediaFetch();
    ~MediaFetch();
    MediaFetch(const MediaFetch&) = delete;
    MediaFetch& operator=(const MediaFetch&) = delete;
    std::optional<std::filesystem::path> art(std::string_view slug);
    std::optional<std::filesystem::path> box(std::string_view slug);

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}
