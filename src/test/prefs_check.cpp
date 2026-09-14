#include "application/Prefs.hpp"

#include <cstdio>
#include <sstream>

namespace {

int fails = 0;

void expect(bool cond, const char* msg) {
    if (!cond) {
        std::fprintf(stderr, "FAIL %s\n", msg);
        ++fails;
    }
}

emulocke::Prefs parse(const char* text) {
    std::istringstream in(text);
    return emulocke::Prefs::parse(in);
}

}  // namespace

int testPrefs() {
    const auto garbage = parse(
        "window_w=99999999999999999999\nwindow_h=abc\nvolume=-5\nscale=77\nspeed_up=1\n"
        "window_x=-99999999\nmute=yes\nfullscreen=1\r\nnot a pair\n=\n");
    expect(garbage.windowW == 0, "overflowing window_w falls back to default");
    expect(garbage.windowH == 0, "non-numeric window_h falls back to default");
    expect(garbage.volume == 0, "volume clamps low");
    expect(garbage.scale == 4, "scale clamps high");
    expect(garbage.speedUp == 2, "speed_up clamps low");
    expect(garbage.windowX == -emulocke::kMaxWindowSide, "window_x clamps");
    expect(!garbage.mute, "non-numeric flag keeps default");
    expect(garbage.fullscreen, "flag with trailing carriage return parses");

    expect(parse("window_w=200\n").windowW == 0, "window_w under minimum means unset");
    expect(parse("window_w=800\n").windowW == 800, "window_w in range kept");
    expect(parse("window_w=99999\n").windowW == emulocke::kMaxWindowSide, "window_w clamps high");
    expect(parse(" volume = 42 \n").volume == 42, "whitespace around key and value tolerated");
    expect(parse("").volume == 100, "empty file keeps defaults");
    return fails;
}
