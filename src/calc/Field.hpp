#pragma once

#include <cstdint>

namespace emulocke {

enum class Weather : uint8_t { None, Sun, Rain, Sand, Hail };

struct Field {
    Weather weather{Weather::None};
    bool doubles{};
    bool reflect{};
    bool lightScreen{};
    bool helpingHand{};
    bool charge{};
    bool switchingOut{};
    bool protect{};
    bool foresight{};
};

struct SideMods {
    bool reflect{};
    bool lightScreen{};
    bool protect{};
    bool seeded{};
    bool foresight{};
    bool helpingHand{};
    bool switchingOut{};
};

struct FieldState {
    Weather weather{Weather::None};
    bool doubles{};
    SideMods ours;
    SideMods theirs;
};

inline Field aimField(const FieldState& s, bool intoFoe) {
    const SideMods& atk = intoFoe ? s.ours : s.theirs;
    const SideMods& def = intoFoe ? s.theirs : s.ours;
    Field f;
    f.weather = s.weather;
    f.doubles = s.doubles;
    f.reflect = def.reflect;
    f.lightScreen = def.lightScreen;
    f.protect = def.protect;
    f.foresight = def.foresight;
    f.helpingHand = atk.helpingHand;
    f.switchingOut = def.switchingOut;
    return f;
}

}
