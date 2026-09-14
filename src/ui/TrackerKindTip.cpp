#include "ui/TrackerKindTip.hpp"

#include "poke/SlugLabel.hpp"
#include "ui/Theme.hpp"

#include <cstdio>
#include <cstring>
#include <string>

namespace emulocke {

ImU32 battleWeatherTint(const char* weather) {
    if (!weather || !weather[0]) {
        return ImGui::GetColorU32(kMetal);
    }
    if (std::strstr(weather, "sand")) {
        return IM_COL32(196, 168, 120, 255);
    }
    if (std::strcmp(weather, "hail") == 0 || std::strstr(weather, "snow")) {
        return IM_COL32(188, 204, 212, 255);
    }
    if (std::strstr(weather, "rain")) {
        return IM_COL32(168, 186, 196, 255);
    }
    if (std::strstr(weather, "fog") || std::strstr(weather, "mist")) {
        return IM_COL32(176, 172, 164, 255);
    }
    if (std::strstr(weather, "electric") || std::strstr(weather, "sun")) {
        return IM_COL32(210, 198, 150, 255);
    }
    if (std::strstr(weather, "grassy")) {
        return IM_COL32(176, 186, 156, 255);
    }
    if (std::strstr(weather, "psychic")) {
        return IM_COL32(196, 176, 186, 255);
    }
    return IM_COL32(210, 194, 168, 255);
}

void fillBattleTip(const TrackerStop& stop, char* out, std::size_t cap) {
    const int n = stop.fieldCount >= 1 ? stop.fieldCount : 1;
    const char* kind = "Single battle";
    if (n >= 3) {
        kind = "Triple battle";
    } else if (stop.tag) {
        kind = "Tag battle";
    } else if (n >= 2) {
        kind = "Double battle";
    }
    std::string weather;
    if (stop.weather && stop.weather[0]) {
        weather = slugDisplayName(stop.weather);
    }
    if (weather.empty() && !(stop.note && stop.note[0])) {
        std::snprintf(out, cap, "%s", kind);
        return;
    }
    if (weather.empty()) {
        std::snprintf(out, cap, "%s\n%s", kind, stop.note);
        return;
    }
    if (stop.note && stop.note[0]) {
        std::snprintf(out, cap, "%s\n%s\n%s", kind, weather.c_str(), stop.note);
        return;
    }
    std::snprintf(out, cap, "%s\n%s", kind, weather.c_str());
}

}
