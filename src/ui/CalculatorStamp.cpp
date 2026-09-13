#include "ui/CalculatorDraw.hpp"

#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {

void calcStamp(const char* label) {
    if (!label || !label[0]) {
        return;
    }
    const ImVec2 ts = ImGui::CalcTextSize(label);
    const ImVec2 p = ImGui::GetCursorScreenPos();
    const ImVec2 b(p.x + ts.x + 8.f, p.y + ts.y + 2.f);
    ImGui::GetWindowDrawList()->AddRect(
        p, b, ImGui::GetColorU32(ImVec4(kMetal.x, kMetal.y, kMetal.z, 0.45f)));
    ImGui::SetCursorScreenPos(ImVec2(p.x + 4.f, p.y + 1.f));
    ImGui::TextDisabled("%s", label);
    ImGui::SameLine(0, 8.f);
}

}