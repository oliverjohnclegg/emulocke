#include "tracker/Difficulty.hpp"

#include <cctype>

namespace emulocke {
namespace {

bool has(std::string_view slug, const char* token) {
    return slug.find(token) != std::string_view::npos;
}

void lowerCopy(std::string_view in, char* out, std::size_t cap) {
    std::size_t n = 0;
    for (char c : in) {
        if (n + 1 >= cap) {
            break;
        }
        out[n++] = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    out[n] = 0;
}

}  // namespace

std::string_view atlasDifficultyKey(std::string_view slug, std::string_view raw) {
    char buf[24]{};
    lowerCopy(raw, buf, sizeof(buf));
    const std::string_view key{buf};
    if (has(slug, "radical-red")) {
        if (key == "hardcore" || key == "hard" || key == "restricted" || key == "2" || key == "3") {
            return "hardcore";
        }
        if (key == "easy" || key == "1") {
            return "easy";
        }
        return {};
    }
    if (has(slug, "unbound")) {
        if (key == "easy" || key == "vanilla" || key == "0") {
            return "easy";
        }
        if (key == "expert" || key == "2") {
            return "expert";
        }
        if (key == "insane" || key == "3") {
            return "insane";
        }
        return {};
    }
    if (has(slug, "volt-white-2")) {
        if (key == "challenge" || key == "c" || key == "1") {
            return "challenge";
        }
        return {};
    }
    if (has(slug, "inclement")) {
        if (key == "hard" || key == "hardcore" || key == "2") {
            return "hard";
        }
        if (key == "easy" || key == "1") {
            return "easy";
        }
        return {};
    }
    return {};
}

}
