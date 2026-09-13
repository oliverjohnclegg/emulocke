#pragma once

#include <algorithm>

namespace emulocke {

constexpr float kScreenGap = 5.f;
constexpr float kSuiteWidth = 460.f;
constexpr float kConsolePad = 21.f;
constexpr float kRightPaneSpan = kSuiteWidth + kConsolePad;
constexpr int kNativeW = 256;
constexpr int kNativeH = 192;
constexpr float kFitSlop = 32.f;
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
    const int fitW = std::max(1, static_cast<int>((paneW + kFitSlop) / static_cast<float>(nativeW)));
    const int stack = nativeH * screens;
    if (static_cast<float>(stack * fitW) > paneH + static_cast<float>(stack)) {
        return std::max(1, static_cast<int>((paneH + kFitSlop) / static_cast<float>(stack)));
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

struct LcdLayout {
    int scale{};
    float screenW{};
    float screenH{};
    float gap{};
    float stackH{};
    float x{};
    float y{};
};

inline LcdLayout layoutLcds(int wanted, int nativeW, int nativeH, int screens, float paneW,
    float paneH) {
    LcdLayout lcd;
    lcd.scale = resolveScreenScale(wanted, nativeW, nativeH, screens, paneW, paneH);
    lcd.screenW = static_cast<float>(nativeW * lcd.scale);
    lcd.screenH = static_cast<float>(nativeH * lcd.scale);
    lcd.gap = screenStackGap(screens > 1, paneH, lcd.screenH * static_cast<float>(screens));
    lcd.stackH = lcd.screenH * static_cast<float>(screens) + (screens > 1 ? lcd.gap : 0.f);
    lcd.x = std::max(0.f, (paneW - lcd.screenW) * 0.5f);
    lcd.y = std::max(0.f, (paneH - lcd.stackH) * 0.5f);
    return lcd;
}

constexpr int widthAfterRightPaneToggle(int width, bool show) {
    const int span = static_cast<int>(kRightPaneSpan);
    return show ? width + span : width - span;
}

static_assert(static_cast<int>(kFitSlop) == 32);
static_assert(static_cast<int>(kRightPaneSpan) == 481);
static_assert(widthAfterRightPaneToggle(kDefaultWindowW, false) == 554);
static_assert(widthAfterRightPaneToggle(554, true) == kDefaultWindowW);

}
