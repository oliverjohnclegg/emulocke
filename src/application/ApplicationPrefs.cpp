#include "application/Application.hpp"
#include "ui/WindowFit.hpp"

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

void Application::syncWindowToScale() {
    if (!session_ || prefs_.scale <= 0) {
        return;
    }
    const int nativeW = session_->screenWidth(0);
    const int nativeH = session_->screenHeight(0);
    const int screens = (session_->kind() == ConsoleKind::Nds || prefs_.bottomScreen) ? 2 : 1;
    const int logicalW =
        windowWidthForLeft(lcdClusterW(nativeW, prefs_.scale), prefs_.rightPane, prefs_.scale);
    const int logicalH = windowHeightForLeft(lcdClusterH(nativeH, screens, prefs_.scale));
    if (host_.fullscreen() || pendingHost_ == PendingHost::FullscreenOn) {
        int w = logicalW;
        int h = logicalH;
        host_.contentWindowSize(logicalW, logicalH, w, h);
        prefs_.windowW = w;
        prefs_.windowH = h;
        return;
    }
    host_.sizeToContent(logicalW, logicalH);
    host_.captureWindowed(prefs_);
}

void Application::setRightPane(bool on) {
    if (prefs_.rightPane == on) {
        return;
    }
    prefs_.rightPane = on;
    if (session_ && prefs_.scale > 0) {
        syncWindowToScale();
        prefs_.save();
        return;
    }
    const int delta = widthAfterRightPaneToggle(0, on);
    if (host_.fullscreen() || pendingHost_ == PendingHost::FullscreenOn) {
        prefs_.windowW = std::max(1, prefs_.windowW + delta);
    } else {
        host_.adjustWidth(delta);
        host_.captureWindowed(prefs_);
    }
    prefs_.save();
}

void Application::setScreenScale(int scale) {
    prefs_.scale = std::clamp(scale, 0, 4);
    if (prefs_.scale > 0) {
        syncWindowToScale();
    }
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

void Application::setBottomScreen(bool on) {
    prefs_.bottomScreen = on;
    if (prefs_.scale > 0) {
        syncWindowToScale();
    }
    prefs_.save();
}

void Application::restoreDefaultWindow() {
    prefs_.fullscreen = false;
    prefs_.rightPane = true;
    prefs_.scale = 0;
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
        if (!prefs_.rightPane) {
            host_.adjustWidth(-static_cast<int>(kRightPaneSpan));
        }
        host_.captureWindowed(prefs_);
        prefs_.save();
        return;
    }
    if (action == PendingHost::FullscreenOn) {
        host_.setFullscreen(true);
        return;
    }
    host_.setFullscreen(false);
    if (prefs_.windowW > 0 && prefs_.windowH > 0) {
        host_.setWindowSize(prefs_.windowW, prefs_.windowH);
    }
    host_.captureWindowed(prefs_);
    prefs_.save();
}

}
