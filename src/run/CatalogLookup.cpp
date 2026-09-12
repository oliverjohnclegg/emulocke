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