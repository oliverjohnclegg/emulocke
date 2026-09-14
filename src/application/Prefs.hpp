#pragma once

namespace emulocke {

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

    static Prefs load();
    void save() const;
};

}