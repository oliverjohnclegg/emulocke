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
    prefs_.fullscreen = on;
    pendingHost_ = on ? PendingHost::FullscreenOn : PendingHost::FullscreenOff;
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

void Application::setSpeedUp(int speed) {
    prefs_.speedUp = std::clamp(speed, 2, 8);
    speedUp_ = prefs_.speedUp;
    prefs_.save();
}

void Application::setSpeedUpHold(bool hold) {
    prefs_.speedUpHold = hold;
    speedUpHold_ = hold;
    speedUpOn_ = false;
    prefs_.save();
}

void Application::restoreDefaultWindow() {
    prefs_.fullscreen = false;
    pendingHost_ = PendingHost::RestoreDefault;
}

void Application::applyPendingHost() {
    if (pendingHost_ == PendingHost::None) {
        return;
    }
    const PendingHost action = pendingHost_;
    pendingHost_ = PendingHost::None;
    if (action == PendingHost::RestoreDefault) {
        host_.restoreDefaultSize();
        host_.captureWindowed(prefs_);
        prefs_.save();
        return;
    }
    if (action == PendingHost::FullscreenOn) {
        host_.setFullscreen(true);
        return;
    }
    host_.setFullscreen(false);
    host_.captureWindowed(prefs_);
    prefs_.save();
}

}
