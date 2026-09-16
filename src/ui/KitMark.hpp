#pragma once

#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {

inline void kitStroke(ImVec2 a, ImVec2 b, bool on) {
    if (!on) {
        return;
    }
    ImGui::GetWindowDrawList()->AddRect(a, b, ImGui::GetColorU32(kMetal), 0.f, 0, 1.8f);
}

inline ImU32 kitPlate(bool lit) {
    return ImGui::GetColorU32(lit ? kHeaderHover : kButton);
}

}
