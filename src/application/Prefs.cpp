#include "application/Prefs.hpp"

#include "emu/Paths.hpp"

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <string>

namespace emulocke {
namespace {

int parseInt(const std::string& value) {
    return std::atoi(value.c_str());
}

bool parseFlag(const std::string& value) {
    return parseInt(value) != 0;
}

}  // namespace

Prefs Prefs::load() {
    Prefs prefs;
    std::ifstream in(localDataPath("prefs.ini"));
    if (!in) {
        return prefs;
    }
    std::string line;
    while (std::getline(in, line)) {
        const auto eq = line.find('=');
        if (eq == std::string::npos) {
            continue;
        }
        const std::string key = line.substr(0, eq);
        const std::string value = line.substr(eq + 1);
        if (key == "window_x") {
            prefs.windowX = parseInt(value);
            prefs.hasWindowPos = true;
        } else if (key == "window_y") {
            prefs.windowY = parseInt(value);
            prefs.hasWindowPos = true;
        } else if (key == "window_w") {
            prefs.windowW = parseInt(value);
        } else if (key == "window_h") {
            prefs.windowH = parseInt(value);
        } else if (key == "has_window_pos") {
            prefs.hasWindowPos = parseFlag(value);
        } else if (key == "fullscreen") {
            prefs.fullscreen = parseFlag(value);
        } else if (key == "scale") {
            prefs.scale = parseInt(value);
        } else if (key == "mute") {
            prefs.mute = parseFlag(value);
        } else if (key == "volume") {
            prefs.volume = parseInt(value);
        } else if (key == "speed_up") {
            prefs.speedUp = parseInt(value);
        } else if (key == "speed_up_hold") {
            prefs.speedUpHold = parseFlag(value);
        } else if (key == "bottom_screen") {
            prefs.bottomScreen = parseFlag(value);
        }
    }
    prefs.scale = std::clamp(prefs.scale, 0, 4);
    prefs.volume = std::clamp(prefs.volume, 0, 100);
    prefs.speedUp = std::clamp(prefs.speedUp, 2, 8);
    return prefs;
}

void Prefs::save() const {
    std::ofstream out(localDataPath("prefs.ini"), std::ios::trunc);
    if (!out) {
        return;
    }
    out << "window_x=" << windowX << '\n';
    out << "window_y=" << windowY << '\n';
    out << "window_w=" << windowW << '\n';
    out << "window_h=" << windowH << '\n';
    out << "has_window_pos=" << (hasWindowPos ? 1 : 0) << '\n';
    out << "fullscreen=" << (fullscreen ? 1 : 0) << '\n';
    out << "scale=" << scale << '\n';
    out << "mute=" << (mute ? 1 : 0) << '\n';
    out << "volume=" << volume << '\n';
    out << "speed_up=" << speedUp << '\n';
    out << "speed_up_hold=" << (speedUpHold ? 1 : 0) << '\n';
    out << "bottom_screen=" << (bottomScreen ? 1 : 0) << '\n';
}

}