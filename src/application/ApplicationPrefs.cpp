#include "application/Application.hpp"

#include <algorithm>

namespace emulocke {

void Application::persistPrefs() {
    if (!host_.fullscreen()) {
        host_.captureWindowed(prefs_);
    }
    prefs_.save();
}

void Application::setFullscreen(bool on) {
    if (on) {
        host_.captureWindowed(prefs_);
    }
    host_.setFullscreen(on);
    prefs_.fullscreen = on;
    prefs_.save();
}

void Application::setScreenScale(int scale) {
    prefs_.scale = std::clamp(scale, 0, 4);
    prefs_.save();
}

void Application::setMuted(bool mute) {
    prefs_.mute = mute;
    audio_.setMuted(mute);
    prefs_.save();
}

void Application::setVolume(int volume) {
    prefs_.volume = std::clamp(volume, 0, 100);
    audio_.setVolume(prefs_.volume);
    prefs_.save();
}

void Application::restoreDefaultWindow() {
    host_.restoreDefaultSize();
    prefs_.fullscreen = false;
    host_.captureWindowed(prefs_);
    prefs_.save();
}

}
