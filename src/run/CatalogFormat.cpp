#include "run/Catalog.hpp"

#include <algorithm>
#include <string_view>

namespace emulocke {
namespace {

void pushVersionParts(std::string_view s, int* parts, int& n) {
    int cur = 0;
    bool in = false;
    for (const char c : s) {
        if (c >= '0' && c <= '9') {
            in = true;
            cur = cur * 10 + (c - '0');
        } else if (in) {
            if (n < 8) {
                parts[n++] = cur;
            }
            cur = 0;
            in = false;
        }
    }
    if (in && n < 8) {
        parts[n++] = cur;
    }
}

int groupRank(std::string_view slug) {
    int i = 0;
    for (const CatalogTitle& title : catalogTitles()) {
        if (title.artSlug == slug) {
            return i;
        }
        ++i;
    }
    return i;
}

}  // namespace

std::string catalogListTitle(const CatalogTitle& title) {
    if (title.version == nullptr || title.version[0] == '\0') {
        return title.title;
    }
    return std::string(title.title) + " (" + title.version + ")";
}

int catalogVersionCompare(std::string_view a, std::string_view b) {
    int pa[8]{};
    int pb[8]{};
    int na = 0;
    int nb = 0;
    pushVersionParts(a, pa, na);
    pushVersionParts(b, pb, nb);
    const int n = na > nb ? na : nb;
    for (int i = 0; i < n; ++i) {
        const int va = i < na ? pa[i] : 0;
        const int vb = i < nb ? pb[i] : 0;
        if (va != vb) {
            return va < vb ? -1 : 1;
        }
    }
    return 0;
}

std::vector<const CatalogTitle*> catalogPickerRows() {
    std::vector<const CatalogTitle*> rows;
    const auto titles = catalogTitles();
    rows.reserve(titles.size());
    for (const CatalogTitle& title : titles) {
        rows.push_back(&title);
    }
    std::sort(rows.begin(), rows.end(), [&](const CatalogTitle* a, const CatalogTitle* b) {
        const int ga = groupRank(a->artSlug);
        const int gb = groupRank(b->artSlug);
        if (ga != gb) {
            return ga < gb;
        }
        const int v = catalogVersionCompare(a->version, b->version);
        if (v != 0) {
            return v > 0;
        }
        return a < b;
    });
    return rows;
}

}
