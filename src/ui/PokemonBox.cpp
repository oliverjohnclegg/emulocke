#include "ui/PokemonDraw.hpp"

#include <algorithm>
#include <imgui.h>

namespace emulocke {

void drawBoxGrid(BoxSprites& sprites, const MonView* mons, int n, int idBase) {
    const float inner = ImGui::GetContentRegionAvail().x;
    const float gap = 4.f;
    const float well = 36.f;
    int cols = static_cast<int>((inner + gap) / (well + gap));
    if (cols < 1) {
        cols = 1;
    }
    const float used = static_cast<float>(cols) * well + static_cast<float>(cols - 1) * gap;
    const float pad = std::max(0.f, (inner - used) * 0.5f);
    const ImVec2 size(well, well);
    for (int i = 0; i < n; ++i) {
        if (i % cols == 0) {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + pad);
        }
        ImGui::PushID(idBase + i);
        drawMonWell(sprites, mons[i], size, false);
        ImGui::PopID();
        if ((i + 1) % cols != 0 && i + 1 < n) {
            ImGui::SameLine(0.f, gap);
        }
    }
}

void drawRosterPane(BoxSprites& sprites, const MonView* mons, int n, const char* title, const char* empty,
                    int idBase) {
    ImGui::TextUnformatted(title);
    ImGui::Separator();
    if (n <= 0) {
        ImGui::TextDisabled("%s", empty);
        return;
    }
    drawBoxGrid(sprites, mons, n, idBase);
}

}