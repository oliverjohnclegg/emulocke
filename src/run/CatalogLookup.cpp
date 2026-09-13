#include "run/Catalog.hpp"

#include <cctype>

namespace emulocke {
namespace {

bool same(std::string_view a, std::string_view b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        const char ca = static_cast<char>(std::tolower(static_cast<unsigned char>(a[i])));
        const char cb = static_cast<char>(std::tolower(static_cast<unsigned char>(b[i])));
        if (ca != cb) {
            return false;
        }
    }
    return true;
}

}  // namespace

const CatalogTitle* catalogByUuid(std::string_view uuid) {
    for (const CatalogTitle& title : catalogTitles()) {
        if (uuid == title.uuid) {
            return &title;
        }
    }
    return nullptr;
}

const CatalogTitle* catalogBySha1(std::string_view sha1) {
    if (sha1.empty()) {
        return nullptr;
    }
    for (const CatalogTitle& title : catalogTitles()) {
        if (title.kind == TitleKind::Baseline && same(sha1, title.sha1)) {
            return &title;
        }
    }
    static constexpr struct {
        const char* sha1;
        const char* uuid;
    } kAliases[] = {
        {"66d2fbfb0dbc1f86a3d726971196989b950092bc", "2ef1748f-beca-5b08-bc8f-6a3042489f37"},
        {"5da09a39424f1a76c52a3eebad9b5e8dcacb71ba", "8634f4f3-c0ff-57eb-894c-fc94405678f0"},
    };
    for (const auto& alias : kAliases) {
        if (same(sha1, alias.sha1)) {
            return catalogByUuid(alias.uuid);
        }
    }
    return nullptr;
}

const CatalogTitle* catalogBySlug(std::string_view slug) {
    for (const CatalogTitle& title : catalogTitles()) {
        if (slug == title.slug) {
            return &title;
        }
    }
    return nullptr;
}

}