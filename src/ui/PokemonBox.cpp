#include "ui/PokemonDraw.hpp"

#include <imgui.h>

namespace emulocke {

void drawBoxGrid(BoxSprites& sprites, const MonView* mons, int n) {
    const float inner = ImGui::GetContentRegionAvail().x;
    const float gap = 4.f;
    const float well = 36.f;
    int cols = static_cast<int>((inner + gap) / (well + gap));
    if (cols < 1) {
        cols = 1;
    }
    const ImVec2 size(well, well);
    for (int i = 0; i < n; ++i) {
        ImGui::PushID(1000 + i);
        drawMonWell(sprites, mons[i], size, false);
        ImGui::PopID();
        if ((i + 1) % cols != 0 && i + 1 < n) {
            ImGui::SameLine(0.f, gap);
        }
    }
}

}  // namespace emulocke
