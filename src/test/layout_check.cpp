#include "ui/Layout.hpp"

#include <algorithm>
#include <cstdio>

int testLayout() {
    int fails = 0;
    auto expect = [&](bool cond, const char* msg) {
        if (!cond) {
            std::fprintf(stderr, "FAIL %s\n", msg);
            ++fails;
        }
    };

    expect(emulocke::consoleLeftWidth(1025.f, 5.f) == 512.f, "home left width");
    expect(emulocke::consoleLeftHeight(800.f, 5.f) == 768.f, "home left height");

    const int oldDsFit = std::min(static_cast<int>(512.f / 256.f),
        static_cast<int>((788.f - 16.f - 5.f) / (192.f * 2)));
    expect(oldDsFit == 1, "old ds fit drops to 1x");
    expect(emulocke::fitScreenScale(256, 192, 2, 512.f, 768.f) == 2, "ds 2x in home pane");
    expect(emulocke::fitScreenScale(256, 192, 2, 512.f, 754.f) == 2, "ds 2x when a little short");
    expect(emulocke::fitScreenScale(256, 192, 2, 512.f, 200.f) == 1, "ds 1x when far too short");
    expect(emulocke::fitScreenScale(240, 160, 1, 512.f, 768.f) == 2, "gba 2x in home pane");
    expect(emulocke::resolveScreenScale(0, 256, 192, 2, 512.f, 768.f) == 2, "fit ds");
    expect(emulocke::resolveScreenScale(1, 256, 192, 2, 512.f, 768.f) == 1, "explicit 1x");
    expect(emulocke::resolveScreenScale(4, 256, 192, 2, 512.f, 768.f) == 2, "explicit 4x caps");
    expect(emulocke::screenStackGap(true, 768.f, 768.f) == 0.f, "tight ds hinge");
    expect(emulocke::screenStackGap(true, 780.f, 768.f) == 5.f, "roomy ds hinge");
    expect(emulocke::screenStackGap(false, 768.f, 320.f) == 0.f, "gba no hinge");
    return fails;
}
