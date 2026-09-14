#include "ui/Layout.hpp"
#include "ui/WindowFit.hpp"

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
    expect(emulocke::consoleLeftWidth(544.f, 5.f, 0.f) == 512.f, "left width with suite hidden");
    expect(emulocke::consoleLeftHeight(800.f, 5.f) == 768.f, "home left height");

    const int oldDsFit = std::min(static_cast<int>(512.f / 256.f),
        static_cast<int>((788.f - 16.f - 5.f) / (192.f * 2)));
    expect(oldDsFit == 1, "old ds fit drops to 1x");
    expect(emulocke::fitScreenScale(256, 192, 2, 512.f, 768.f) == 2, "ds 2x in home pane");
    expect(emulocke::fitScreenScale(256, 192, 2, 512.f, 754.f) == 2, "ds 2x when a little short");
    expect(emulocke::fitScreenScale(256, 192, 2, 512.f, 200.f) == 1, "ds 1x when far too short");
    expect(emulocke::fitScreenScale(240, 160, 1, 512.f, 768.f) == 2, "gba 2x in home pane");
    expect(emulocke::fitScreenScale(240, 160, 2, 512.f, 768.f) == 2, "gba party 2x in home pane");
    expect(emulocke::fitScreenScale(256, 192, 2, 502.f, 768.f) == 2, "ds 2x from padded avail");
    expect(emulocke::fitScreenScale(256, 192, 2, 511.f, 768.f) == 2, "ds 2x from 511 pane");
    expect(emulocke::fitScreenScale(256, 192, 2, 480.f, 768.f) == 2, "ds 2x when gba is 2x");
    expect(emulocke::fitScreenScale(256, 192, 2, 256.f, 768.f) == 1, "ds 1x in native pane");
    expect(emulocke::fitScreenScale(256, 192, 2, 257.f, 768.f) == 1, "ds 1x in 257 pane");
    expect(emulocke::resolveScreenScale(0, 256, 192, 2, 502.f, 768.f) == 2, "fit ds padded");
    expect(emulocke::resolveScreenScale(2, 256, 192, 2, 502.f, 768.f) == 2, "explicit 2x padded");
    expect(emulocke::resolveScreenScale(0, 256, 192, 2, 512.f, 768.f) == 2, "fit ds");
    expect(emulocke::resolveScreenScale(1, 256, 192, 2, 512.f, 768.f) == 1, "explicit 1x");
    expect(emulocke::resolveScreenScale(4, 256, 192, 2, 512.f, 768.f) == 2, "explicit 4x caps");
    expect(emulocke::screenStackGap(true, 768.f, 768.f) == 0.f, "tight ds hinge");
    expect(emulocke::screenStackGap(true, 773.f, 768.f) == 5.f, "hinge when column has 5px");
    expect(emulocke::screenStackGap(true, 780.f, 768.f) == 5.f, "roomy ds hinge");
    expect(emulocke::screenStackGap(false, 768.f, 320.f) == 0.f, "gba no hinge");

    const auto dsTight = emulocke::layoutLcds(0, 256, 192, 2, 512.f, 768.f);
    expect(dsTight.scale == 2 && dsTight.gap == 0.f, "ds 2x without hinge room");

    const auto ds = emulocke::layoutLcds(0, 256, 192, 2, 512.f, 768.f + emulocke::kScreenGap);
    expect(ds.scale == 2, "ds stack 2x");
    expect(ds.screenW == 512.f, "ds stack width");
    expect(ds.screenH == 384.f, "ds stack height");
    expect(ds.x == 0.f, "ds stack flush");
    expect(ds.y == 0.f, "ds stack fills y");
    expect(ds.gap == 5.f, "ds stack hinge");
    expect(ds.stackH == 773.f, "ds stack with hinge");

    const auto ds1x = emulocke::layoutLcds(1, 256, 192, 2, 512.f, 768.f + emulocke::kScreenGap);
    expect(ds1x.scale == 1, "ds 1x");
    expect(ds1x.screenW == 256.f, "ds 1x width");
    expect(ds1x.gap == 5.f, "ds 1x hinge");
    expect(ds1x.stackH == 389.f, "ds 1x stack");
    expect(ds1x.x == 128.f, "ds 1x centered x");
    expect(ds1x.y == 192.f, "ds 1x centered y");

    const auto gbaParty = emulocke::layoutLcds(0, 240, 160, 2, 512.f, 768.f + emulocke::kScreenGap);
    expect(gbaParty.scale == 2, "gba party 2x");
    expect(gbaParty.screenW == 480.f, "gba party width");
    expect(gbaParty.screenH == 320.f, "gba party height");
    expect(gbaParty.x == 16.f, "gba party centered x");
    expect(gbaParty.y == 64.f, "gba party centered y");
    expect(gbaParty.gap == 5.f, "gba party hinge");
    expect(gbaParty.stackH == 645.f, "gba party stack");

    const auto gbaOnly = emulocke::layoutLcds(0, 240, 160, 1, 512.f, 768.f);
    expect(gbaOnly.x == 16.f, "gba only centered x");
    expect(gbaOnly.y == 224.f, "gba only centered y");

    const auto ds2xWanted = emulocke::layoutLcds(2, 256, 192, 2, 512.f, 768.f + emulocke::kScreenGap);
    expect(ds2xWanted.scale == 2 && ds2xWanted.x == 0.f && ds2xWanted.gap == 5.f, "explicit 2x matches fit");

    const auto dsPadded = emulocke::layoutLcds(0, 256, 192, 2, 502.f, 768.f);
    expect(dsPadded.scale == 2, "padded ds 2x");
    expect(dsPadded.screenW == 512.f, "padded ds fills 2x width");
    expect(dsPadded.x == 0.f, "padded ds flush");

    expect(emulocke::lcdClusterW(256, 1) == 256.f, "ds 1x cluster w");
    expect(emulocke::lcdClusterH(192, 2, 1) == 389.f, "ds 1x cluster h");
    expect(emulocke::lcdClusterH(192, 2, 2) == 773.f, "ds 2x cluster h");
    expect(emulocke::lcdClusterW(240, 2) == 480.f, "gba 2x cluster w");
    expect(emulocke::lcdClusterH(160, 2, 2) == 645.f, "gba party 2x cluster h");
    expect(emulocke::lcdClusterH(160, 1, 2) == 320.f, "gba only 2x cluster h");
    expect(emulocke::windowWidthForLeft(512.f, true) == 1035, "home window w");
    expect(emulocke::windowWidthForLeft(256.f, true, 1) == 549, "ds 1x window w");
    expect(emulocke::windowWidthForLeft(256.f, false, 1) == 298, "ds 1x no suite");
    expect(emulocke::windowHeightForLeft(768.f) == 836, "home window h");
    expect(emulocke::windowHeightForLeft(773.f) == 841, "ds 2x window h");
    expect(emulocke::windowHeightForLeft(389.f) == 457, "ds 1x window h");
    expect(emulocke::suiteWidthForScale(0) == 460.f, "fit suite");
    expect(emulocke::suiteWidthForScale(1) == 230.f, "1x suite");
    expect(emulocke::suiteWidthForScale(2) == 460.f, "2x suite");
    expect(emulocke::rightPaneSpanForScale(1) == 251.f, "1x right span");

    const float pad = 5.f;
    const int ds1xW = emulocke::windowWidthForLeft(emulocke::lcdClusterW(256, 1), true, 1);
    const float ds1xAvail = static_cast<float>(ds1xW) - pad * 2.f;
    expect(emulocke::consoleLeftWidth(ds1xAvail, pad, emulocke::rightPaneSpanForScale(1)) == 256.f,
        "1x window hugs ds width");
    const float inset = emulocke::kConsolePad - pad;
    expect(ds1xAvail - inset * 2.f - 256.f - emulocke::kConsolePad == 230.f, "1x suite leftover");
    const int ds1xWinH = emulocke::windowHeightForLeft(emulocke::lcdClusterH(192, 2, 1));
    expect(ds1xWinH - (emulocke::kDefaultWindowH - emulocke::kHomeLeftH) == 389, "1x window hugs ds height");

    const auto dsHug = emulocke::layoutLcds(1, 256, 192, 2, 256.f, 389.f);
    expect(dsHug.scale == 1 && dsHug.x == 0.f && dsHug.y == 0.f && dsHug.gap == 5.f, "1x ds fills snapped pane");
    const auto ds2Hug = emulocke::layoutLcds(2, 256, 192, 2, 512.f, 773.f);
    expect(ds2Hug.scale == 2 && ds2Hug.x == 0.f && ds2Hug.y == 0.f && ds2Hug.gap == 5.f, "2x ds fills snapped pane");
    const auto gbaHug = emulocke::layoutLcds(2, 240, 160, 2, 480.f, 645.f);
    expect(gbaHug.scale == 2 && gbaHug.x == 0.f && gbaHug.y == 0.f && gbaHug.gap == 5.f, "2x gba fills snapped pane");
    const auto gbaOnlyHug = emulocke::layoutLcds(2, 240, 160, 1, 480.f, 320.f);
    expect(gbaOnlyHug.scale == 2 && gbaOnlyHug.x == 0.f && gbaOnlyHug.y == 0.f, "2x gba only fills snapped pane");
    return fails;
}
