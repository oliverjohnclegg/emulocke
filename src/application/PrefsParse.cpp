#include "application/Prefs.hpp"

#include <SDL3/SDL_scancode.h>
#include <algorithm>
#include <charconv>
#include <istream>
#include <string>
#include <string_view>

namespace emulocke {
namespace {

std::string_view trim(std::string_view text) {
    while (!text.empty() && (text.front() == ' ' || text.front() == '\t')) {
        text.remove_prefix(1);
    }
    while (!text.empty() && (text.back() == ' ' || text.back() == '\t' || text.back() == '\r')) {
        text.remove_suffix(1);
    }
    return text;
}

int parseInt(std::string_view value, int fallback) {
    value = trim(value);
    int parsed = 0;
    const auto [end, ec] = std::from_chars(value.data(), value.data() + value.size(), parsed);
    return ec == std::errc{} && end == value.data() + value.size() ? parsed : fallback;
}

bool parseFlag(std::string_view value, bool fallback) {
    return parseInt(value, fallback ? 1 : 0) != 0;
}

int clampWindowSide(int side) {
    return side < kMinWindowSide ? 0 : std::min(side, kMaxWindowSide);
}

void applyKey(Prefs& prefs, std::string_view key, std::string_view value) {
    if (key == "window_x") {
        prefs.windowX = parseInt(value, prefs.windowX);
        prefs.hasWindowPos = true;
    } else if (key == "window_y") {
        prefs.windowY = parseInt(value, prefs.windowY);
        prefs.hasWindowPos = true;
    } else if (key == "window_w") {
        prefs.windowW = parseInt(value, prefs.windowW);
    } else if (key == "window_h") {
        prefs.windowH = parseInt(value, prefs.windowH);
    } else if (key == "has_window_pos") {
        prefs.hasWindowPos = parseFlag(value, prefs.hasWindowPos);
    } else if (key == "fullscreen") {
        prefs.fullscreen = parseFlag(value, prefs.fullscreen);
    } else if (key == "right_pane") {
        prefs.rightPane = parseFlag(value, prefs.rightPane);
    } else if (key == "scale") {
        prefs.scale = parseInt(value, prefs.scale);
    } else if (key == "mute") {
        prefs.mute = parseFlag(value, prefs.mute);
    } else if (key == "volume") {
        prefs.volume = parseInt(value, prefs.volume);
    } else if (key == "speed_up") {
        prefs.speedUp = parseInt(value, prefs.speedUp);
    } else if (key == "speed_up_hold") {
        prefs.speedUpHold = parseFlag(value, prefs.speedUpHold);
    } else if (key == "bottom_screen") {
        prefs.bottomScreen = parseFlag(value, prefs.bottomScreen);
    } else if (key.substr(0, 4) == "key_") {
        const int slot = keySlotFromId(std::string(key.substr(4)));
        const SDL_Scancode code = parseScancode(std::string(trim(value)));
        if (slot >= 0 && code != SDL_SCANCODE_UNKNOWN) {
            prefs.keys.codes[slot] = code;
        }
    }
}

}  // namespace

Prefs Prefs::parse(std::istream& in) {
    Prefs prefs;
    std::string line;
    while (std::getline(in, line)) {
        const auto eq = line.find('=');
        if (eq == std::string::npos) {
            continue;
        }
        const std::string_view text(line);
        applyKey(prefs, trim(text.substr(0, eq)), text.substr(eq + 1));
    }
    prefs.windowX = std::clamp(prefs.windowX, -kMaxWindowSide, kMaxWindowSide);
    prefs.windowY = std::clamp(prefs.windowY, -kMaxWindowSide, kMaxWindowSide);
    prefs.windowW = clampWindowSide(prefs.windowW);
    prefs.windowH = clampWindowSide(prefs.windowH);
    prefs.scale = std::clamp(prefs.scale, 0, 4);
    prefs.volume = std::clamp(prefs.volume, 0, 100);
    prefs.speedUp = std::clamp(prefs.speedUp, 2, 8);
    return prefs;
}

}
