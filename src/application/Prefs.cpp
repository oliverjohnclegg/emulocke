#include "application/Prefs.hpp"

#include "emu/Paths.hpp"

#include <fstream>

namespace emulocke {

Prefs Prefs::load() {
    std::ifstream in(localDataPath("prefs.ini"));
    if (!in) {
        return Prefs{};
    }
    return parse(in);
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
    out << "right_pane=" << (rightPane ? 1 : 0) << '\n';
    out << "scale=" << scale << '\n';
    out << "mute=" << (mute ? 1 : 0) << '\n';
    out << "volume=" << volume << '\n';
    out << "speed_up=" << speedUp << '\n';
    out << "speed_up_hold=" << (speedUpHold ? 1 : 0) << '\n';
    out << "bottom_screen=" << (bottomScreen ? 1 : 0) << '\n';
    for (int i = 0; i < kKeySlotCount; ++i) {
        out << "key_" << keySlotId(i) << '=' << scancodeLabel(keys.codes[i]) << '\n';
    }
}

}
