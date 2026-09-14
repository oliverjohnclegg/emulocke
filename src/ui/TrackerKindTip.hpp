#pragma once

#include "tracker/Atlas.hpp"

#include <cstddef>
#include <imgui.h>

namespace emulocke {

ImU32 battleWeatherTint(const char* weather);
void fillBattleTip(const TrackerStop& stop, char* out, std::size_t cap);

}
