#pragma once

namespace emulocke {

constexpr float kScreenGap = 5.f;
constexpr float kSuiteWidth = 460.f;
constexpr float kConsolePad = 21.f;
constexpr float kRightPaneSpan = kSuiteWidth + kConsolePad;
constexpr int kNativeW = 256;
constexpr int kNativeH = 192;
constexpr int kDefaultWindowW = 1035;
constexpr int kDefaultWindowH = 836;

constexpr int widthAfterRightPaneToggle(int width, bool show) {
    const int span = static_cast<int>(kRightPaneSpan);
    return show ? width + span : width - span;
}

static_assert(static_cast<int>(kRightPaneSpan) == 481);
static_assert(widthAfterRightPaneToggle(kDefaultWindowW, false) == 554);
static_assert(widthAfterRightPaneToggle(554, true) == kDefaultWindowW);

}
