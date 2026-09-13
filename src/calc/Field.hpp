#pragma once

#include <cstdint>

namespace emulocke {

enum class Weather : uint8_t { None, Sun, Rain, Sand, Hail };

struct Field {
    Weather weather{Weather::None};
    bool reflect{};
    bool lightScreen{};
    bool helpingHand{};
    bool charge{};
    bool switchingOut{};
};

}
