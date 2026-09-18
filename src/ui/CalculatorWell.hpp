#pragma once

#include <cstdint>
#include <imgui.h>

namespace emulocke {

class Application;

inline constexpr float kCalcWell = 36.f;

const char* calcStageMark(const int8_t stages[8]);
void drawCalcWell(Application& app, ImVec2 a, const char* slug, bool dim, bool selected, bool next,
    int level, const char* stage);

}
