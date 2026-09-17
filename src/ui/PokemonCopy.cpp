#include "ui/PokemonCopy.hpp"

#include "poke/Showdown.hpp"
#include "ui/IconAction.hpp"
#include "ui/PokemonDraw.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <string>

namespace emulocke {
namespace {

std::string showdownTeam(const MonView* views, int n) {
    std::string out;
    for (int i = 0; i < n; ++i) {
        if (!views[i].mon) {
            continue;
        }
        appendSet(out, *views[i].mon, views[i].ref, views[i].gen3);
    }
    return out;
}

void iconClip(ImVec2 p, ImVec2 size, int cols, int rows) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImU32 metal = ImGui::GetColorU32(kMetal);
    const float t = 1.5f;
    const float x0 = p.x + size.x * 0.22f;
    const float y0 = p.y + size.y * 0.28f;
    const float x1 = p.x + size.x * 0.78f;
    const float y1 = p.y + size.y * 0.86f;
    dl->AddRect(ImVec2(x0, y0), ImVec2(x1, y1), metal, 0.f, 0, t);
    const float cx = p.x + size.x * 0.5f;
    const float cw = size.x * 0.22f;
    const float ch = size.y * 0.16f;
    dl->AddRectFilled(ImVec2(cx - cw, p.y + size.y * 0.12f), ImVec2(cx + cw, p.y + size.y * 0.12f + ch), metal);
    const float ix0 = x0 + 2.5f;
    const float iy0 = y0 + ch * 0.35f + 2.f;
    const float ix1 = x1 - 2.5f;
    const float iy1 = y1 - 2.5f;
    const float gw = (ix1 - ix0) / static_cast<float>(cols);
    const float gh = (iy1 - iy0) / static_cast<float>(rows);
    const float d = 1.15f;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            const float x = ix0 + gw * (static_cast<float>(c) + 0.5f);
            const float y = iy0 + gh * (static_cast<float>(r) + 0.5f);
            dl->AddRectFilled(ImVec2(x - d, y - d), ImVec2(x + d, y + d), metal);
        }
    }
}

}  // namespace

void drawPokemonCopyButtons(const MonView* party, int partyN, const MonView* boxed, int boxedN) {
    const ImVec2 size(18.f, 18.f);
    const ImVec2 partyPos = ImGui::GetCursorScreenPos();
    if (iconAction("copy-party", "Copy party to clipboard", size)) {
        ImGui::SetClipboardText(showdownTeam(party, partyN).c_str());
    }
    iconClip(partyPos, size, 3, 2);
    ImGui::SameLine(0.f, 4.f);
    const ImVec2 allPos = ImGui::GetCursorScreenPos();
    if (iconAction("copy-all", "Copy all Pokemon to clipboard", size)) {
        std::string text = showdownTeam(party, partyN);
        const std::string rest = showdownTeam(boxed, boxedN);
        if (!text.empty() && !rest.empty()) {
            text += '\n';
        }
        text += rest;
        ImGui::SetClipboardText(text.c_str());
    }
    iconClip(allPos, size, 4, 3);
}

}
