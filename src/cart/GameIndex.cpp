#include "cart/GameIndex.hpp"

#include "poke/SpriteIndex.hpp"

#include <algorithm>
#include <cctype>
#include <cstring>

namespace emulocke {
namespace {

struct Entry {
    const char* slug;
    const char* title;
    const char* system;
    const char* file;
};

constexpr Entry kEntries[] = {
#include "cart/GameIndex.inc"
};

bool lessSlug(const Entry& entry, const std::string& slug) {
    return std::strcmp(entry.slug, slug.c_str()) < 0;
}

const Entry* findEntry(const std::string& key) {
    const Entry* end = kEntries + sizeof(kEntries) / sizeof(kEntries[0]);
    const Entry* it = std::lower_bound(kEntries, end, key, lessSlug);
    if (it != end && key == it->slug) {
        return it;
    }
    return nullptr;
}

std::string encodePath(std::string_view raw) {
    std::string out;
    out.reserve(raw.size() * 3);
    for (unsigned char c : raw) {
        if (c == ' ') {
            out += "%20";
        } else if (c == ',') {
            out += "%2C";
        } else {
            out.push_back(static_cast<char>(c));
        }
    }
    return out;
}

}  // namespace

std::string gameArtTitle(std::string_view slug) {
    const std::string key = normalizeSlug(slug);
    if (const Entry* entry = findEntry(key)) {
        return entry->title;
    }
    std::string title;
    title.reserve(key.size());
    for (char c : key) {
        if (c == '-') {
            title.push_back(' ');
        } else {
            title.push_back(static_cast<char>(std::toupper(static_cast<unsigned char>(c))));
        }
    }
    return title.empty() ? "UNKNOWN" : title;
}

std::optional<std::string> gameArtUrl(std::string_view slug) {
    const std::string key = normalizeSlug(slug);
    const Entry* entry = findEntry(key);
    if (!entry) {
        return std::nullopt;
    }
    return std::string("https://raw.githubusercontent.com/libretro-thumbnails/") + entry->system +
           "/master/Named_Titles/" + encodePath(entry->file);
}

}
