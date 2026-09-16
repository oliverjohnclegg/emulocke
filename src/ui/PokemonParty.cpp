#include "ui/PokemonDraw.hpp"

#include <imgui.h>

namespace emulocke {

void drawPartyStrip(BoxSprites& sprites, const MonView* party, int n, int focus, bool act) {
    const float inner = ImGui::GetContentRegionAvail().x;
    const float gap = 4.f;
    const float wellW = (inner - gap * static_cast<float>(n - 1)) / static_cast<float>(n);
    const ImVec2 size(wellW, 48.f);
    for (int i = 0; i < n; ++i) {
        ImGui::PushID(i);
        drawMonWell(sprites, party[i], size, true, focus == i, act && focus == i);
        ImGui::PopID();
        if (i + 1 < n) {
            ImGui::SameLine(0.f, gap);
        }
    }
}

}  // namespace emulocke
