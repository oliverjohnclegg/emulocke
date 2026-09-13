#pragma once

#include <algorithm>

namespace emulocke {

constexpr float kScreenGap = 5.f;
constexpr float kSuiteWidth = 460.f;
constexpr float kConsolePad = 21.f;
constexpr float kRightPaneSpan = kSuiteWidth + kConsolePad;
constexpr int kNativeW = 256;
constexpr int kNativeH = 192;
constexpr int kDefaultWindowW = 1035;
constexpr int kDefaultWindowH = 836;

inline float consoleLeftWidth(float availX, float windowPadX, float rightSpan = kRightPaneSpan) {
    const float insetX = kConsolePad - windowPadX;
    return availX - insetX - rightSpan - insetX;
}

inline float consoleLeftHeight(float availY, float windowPadY) {
    const float insetY = kConsolePad - windowPadY;
    return availY - insetY - insetY;
}

inline int fitScreenScale(int nativeW, int nativeH, int screens, float paneW, float paneH) {
    const int fitW = std::max(1, static_cast<int>(paneW / static_cast<float>(nativeW)));
    const int stack = nativeH * screens;
    if (static_cast<float>(stack * fitW) > paneH + static_cast<float>(stack)) {
        return std::max(1, static_cast<int>(paneH / static_cast<float>(stack)));
    }
    return fitW;
}

inline int resolveScreenScale(int wanted, int nativeW, int nativeH, int screens, float paneW,
    float paneH) {
    const int fit = fitScreenScale(nativeW, nativeH, screens, paneW, paneH);
    if (wanted <= 0) {
        return fit;
    }
    return std::max(1, std::min(wanted, fit));
}

inline float screenStackGap(bool stacked, float paneH, float pixelH) {
    if (!stacked) {
        return 0.f;
    }
    return std::min(kScreenGap, std::max(0.f, paneH - pixelH));
}

constexpr int widthAfterRightPaneToggle(int width, bool show) {
    const int span = static_cast<int>(kRightPaneSpan);
    return show ? width + span : width - span;
}

static_assert(static_cast<int>(kRightPaneSpan) == 481);
static_assert(widthAfterRightPaneToggle(kDefaultWindowW, false) == 554);
static_assert(widthAfterRightPaneToggle(554, true) == kDefaultWindowW);

}
