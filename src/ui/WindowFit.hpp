#pragma once

#include "ui/Layout.hpp"

namespace emulocke {

constexpr int kHomeLeftW = kNativeW * 2;
constexpr int kHomeLeftH = kNativeH * 4;
constexpr int kWindowSideChrome =
    kDefaultWindowW - kHomeLeftW - static_cast<int>(kRightPaneSpan);

constexpr float lcdClusterW(int nativeW, int scale) {
    return static_cast<float>(nativeW * (scale < 1 ? 1 : scale));
}

constexpr float lcdClusterH(int nativeH, int screens, int scale) {
    const int s = scale < 1 ? 1 : scale;
    return static_cast<float>(nativeH * s * screens) + (screens > 1 ? kScreenGap : 0.f);
}

constexpr float suiteWidthForScale(int scale) {
    if (scale <= 0) {
        return kSuiteWidth;
    }
    return kSuiteWidth * static_cast<float>(scale) * 0.5f;
}

constexpr float rightPaneSpanForScale(int scale) {
    return suiteWidthForScale(scale) + kConsolePad;
}

constexpr int windowWidthForLeft(float leftW, bool showRight, int scale = 0) {
    const float right = showRight ? rightPaneSpanForScale(scale) : 0.f;
    return static_cast<int>(leftW + 0.5f) + kWindowSideChrome + static_cast<int>(right + 0.5f);
}

constexpr int windowHeightForLeft(float leftH) {
    return static_cast<int>(leftH + 0.5f) + kDefaultWindowH - kHomeLeftH;
}

static_assert(kHomeLeftW == 512);
static_assert(kHomeLeftH == 768);
static_assert(kWindowSideChrome == 42);
static_assert(suiteWidthForScale(1) == 230.f);
static_assert(rightPaneSpanForScale(1) == 251.f);
static_assert(windowWidthForLeft(512.f, true) == kDefaultWindowW);
static_assert(windowWidthForLeft(256.f, true, 1) == 549);
static_assert(windowHeightForLeft(768.f) == kDefaultWindowH);
static_assert(windowHeightForLeft(773.f) == 841);

}
