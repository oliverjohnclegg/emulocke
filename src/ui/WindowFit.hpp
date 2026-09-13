#pragma once

#include "ui/Layout.hpp"

namespace emulocke {

constexpr int kHomeLeftW = kNativeW * 2;
constexpr int kHomeLeftH = kNativeH * 4;

constexpr float lcdClusterW(int nativeW, int scale) {
    return static_cast<float>(nativeW * (scale < 1 ? 1 : scale));
}

constexpr float lcdClusterH(int nativeH, int screens, int scale) {
    const int s = scale < 1 ? 1 : scale;
    return static_cast<float>(nativeH * s * screens) + (screens > 1 ? kScreenGap : 0.f);
}

constexpr int windowWidthForLeft(float leftW, bool showRight) {
    return static_cast<int>(leftW + 0.5f) + kDefaultWindowW - kHomeLeftW
        - (showRight ? 0 : static_cast<int>(kRightPaneSpan));
}

constexpr int windowHeightForLeft(float leftH) {
    return static_cast<int>(leftH + 0.5f) + kDefaultWindowH - kHomeLeftH;
}

static_assert(kHomeLeftW == 512);
static_assert(kHomeLeftH == 768);
static_assert(windowWidthForLeft(512.f, true) == kDefaultWindowW);
static_assert(windowHeightForLeft(768.f) == kDefaultWindowH);
static_assert(windowHeightForLeft(773.f) == 841);

}
