#pragma once

#include "emu/KeyMap.hpp"

#include <iosfwd>

namespace emulocke {

inline constexpr int kMinWindowSide = 320;
inline constexpr int kMaxWindowSide = 16384;

struct Prefs {
    int windowX = 0;
    int windowY = 0;
    int windowW = 0;
    int windowH = 0;
    bool hasWindowPos = false;
    bool fullscreen = false;
    bool rightPane = true;
    int scale = 0;
    bool mute = false;
    int volume = 100;
    int speedUp = 3;
    bool speedUpHold = true;
    bool bottomScreen = true;
    KeyMap keys{};

    static Prefs load();
    static Prefs parse(std::istream& in);
    void save() const;
};

}
