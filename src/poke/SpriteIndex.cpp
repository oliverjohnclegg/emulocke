#include "poke/SpriteIndex.hpp"

#include <algorithm>
#include <cctype>
#include <cstring>

namespace emulocke {
namespace {

struct Entry {
    const char* slug;
    uint16_t id;
};

constexpr Entry kEntries[] = {
#include "poke/SpriteIndex.inc"
};

bool lessSlug(const Entry& entry, const std::string& slug) {
    return std::strcmp(entry.slug, slug.c_str()) < 0;
}

bool isSlugSeparator(char c) {
    return c == ' ' || c == '_' || c == '-';
}

bool isSlugLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

}  // namespace

std::string normalizeSlug(std::string_view raw) {
    std::string out;
    out.reserve(raw.size());
    for (const char c : raw) {
        if (isSlugSeparator(c)) {
            if (!out.empty() && out.back() != '-') {
                out.push_back('-');
            }
            continue;
        }
        const auto lower = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        if (isSlugLetter(lower)) {
            out.push_back(lower);
        }
    }
    while (!out.empty() && out.back() == '-') {
        out.pop_back();
    }
    return out;
}

std::optional<uint16_t> pokemonId(std::string_view slug) {
    const std::string key = normalizeSlug(slug);
    const Entry* end = kEntries + sizeof(kEntries) / sizeof(kEntries[0]);
    const Entry* it = std::lower_bound(kEntries, end, key, lessSlug);
    if (it != end && key == it->slug) {
        return it->id;
    }
    if (key.size() > 6 && key.compare(0, 6, "unown-") == 0) {
        return static_cast<uint16_t>(201);
    }
    const std::string prefix = key + "-";
    std::optional<uint16_t> best;
    for (; it != end; ++it) {
        if (std::strncmp(it->slug, prefix.c_str(), prefix.size()) != 0) {
            break;
        }
        if (!best || it->id < *best) {
            best = it->id;
        }
    }
    return best;
}

std::string speciesSlug(std::string_view name) {
    if (name.empty() || name == "???" || name[0] == '-') {
        return {};
    }
    return normalizeSlug(name);
}

}  // namespace emulocke
