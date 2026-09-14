#include "cheats/Lines.hpp"

#include "cheats/Limits.hpp"

#include <cctype>
#include <charconv>

namespace emulocke {
namespace {

bool hexWord(std::string_view text, uint32_t& out, std::size_t& used) {
    if (text.size() < 8) {
        return false;
    }
    const auto [end, ec] = std::from_chars(text.data(), text.data() + 8, out, 16);
    if (ec != std::errc{} || end != text.data() + 8) {
        return false;
    }
    used = 8;
    return true;
}

}  // namespace

std::string_view trimCheat(std::string_view text) {
    while (!text.empty() && (text.front() == ' ' || text.front() == '\t')) {
        text.remove_prefix(1);
    }
    while (!text.empty() &&
        (text.back() == ' ' || text.back() == '\t' || text.back() == '\r')) {
        text.remove_suffix(1);
    }
    return text;
}

bool cheatComment(std::string_view line) {
    return line.starts_with("#") || line.starts_with("//");
}

std::vector<std::string> cheatLines(std::string_view code) {
    std::vector<std::string> lines;
    while (!code.empty()) {
        const auto nl = code.find('\n');
        const auto row = trimCheat(nl == std::string_view::npos ? code : code.substr(0, nl));
        if (nl == std::string_view::npos) {
            code = {};
        } else {
            code.remove_prefix(nl + 1);
        }
        if (!row.empty()) {
            lines.emplace_back(row);
        }
    }
    return lines;
}

bool parseArWords(std::string_view code, std::vector<uint32_t>& words) {
    words.clear();
    bool any = false;
    for (const std::string& raw : cheatLines(code)) {
        if (cheatComment(raw)) {
            continue;
        }
        if (raw.size() > kMaxCheatLine) {
            words.clear();
            return false;
        }
        std::string_view line = raw;
        uint32_t a = 0;
        uint32_t b = 0;
        std::size_t used = 0;
        if (!hexWord(line, a, used)) {
            words.clear();
            return false;
        }
        line.remove_prefix(used);
        line = trimCheat(line);
        if (!hexWord(line, b, used)) {
            words.clear();
            return false;
        }
        line.remove_prefix(used);
        line = trimCheat(line);
        if (!line.empty() && !cheatComment(line)) {
            words.clear();
            return false;
        }
        words.push_back(a);
        words.push_back(b);
        any = true;
    }
    return any;
}

}
