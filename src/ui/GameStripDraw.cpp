#include "ui/GameStrip.hpp"

#include "application/Application.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <SDL3/SDL.h>
#include <cstdint>
#include <cstdio>
#include <string>

namespace emulocke {
namespace {

void drawCreatorStamp(ImDrawList* dl, ImFont* body, const char* creator, ImVec2 detailPos, ImVec2 max,
    bool ready) {
    if (!creator || creator[0] == '\0') {
        return;
    }
    char credit[48];
    std::snprintf(credit, sizeof credit, "by %s", creator);
    const float size = 11.f;
    const ImVec2 pad(4.f, 2.f);
    const ImVec2 sz = body ? body->CalcTextSizeA(size, FLT_MAX, 0.f, credit) : ImGui::CalcTextSize(credit);
    const ImVec2 tagMax(max.x - 6.f, detailPos.y + size + pad.y * 2.f);
    const ImVec2 tagMin(tagMax.x - sz.x - pad.x * 2.f, detailPos.y);
    dl->AddRectFilled(tagMin, tagMax, ImGui::GetColorU32(kButton));
    dl->AddRect(tagMin, tagMax, ImGui::GetColorU32(kBorder));
    const ImU32 col = ImGui::GetColorU32(ready ? kMetal : kDisabled);
    const ImVec2 text(tagMin.x + pad.x, tagMin.y + pad.y);
    if (body) {
        dl->AddText(body, size, text, col, credit);
    } else {
        dl->AddText(text, col, credit);
    }
}

}  // namespace

void drawTitleStrip(Application& app, const CatalogTitle& title, ImVec2 min, ImVec2 max, bool ready) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->PushClipRect(min, max, true);
    const ImVec2 well(min.x + 4.f, min.y + (max.y - min.y - kTitleArtH) * 0.5f);
    const ImVec2 wellMax(well.x + kTitleArtW, well.y + kTitleArtH);
    dl->AddRectFilled(well, wellMax, ImGui::GetColorU32(kScreenWell));
    if (SDL_Texture* tex = app.gameArt().texture(app.renderer(), title.artSlug)) {
        ImGuiPlatformIO& pio = ImGui::GetPlatformIO();
        if (pio.DrawCallback_SetSamplerNearest) {
            dl->AddCallback(pio.DrawCallback_SetSamplerNearest, nullptr);
        }
        const ImU32 tint = ready ? IM_COL32_WHITE : ImGui::GetColorU32(kDisabled);
        dl->AddImage(ImTextureRef(static_cast<ImTextureID>(reinterpret_cast<uintptr_t>(tex))), well, wellMax,
            ImVec2(0, 0), ImVec2(1, 1), tint);
        if (pio.DrawCallback_SetSamplerLinear) {
            dl->AddCallback(pio.DrawCallback_SetSamplerLinear, nullptr);
        }
    }
    dl->AddRect(well, wellMax, ImGui::GetColorU32(kBorder));
    const ImVec2 text(wellMax.x + 8.f, min.y + 8.f);
    const std::string listed = catalogListTitle(title);
    const ImU32 nameCol = ImGui::GetColorU32(ready ? kMetal : kDisabled);
    const ImVec4 detail = ready ? ImVec4(kMetal.x, kMetal.y, kMetal.z, 0.65f) : kDisabled;
    ImFont* display = app.displayFont();
    ImFont* body = app.bodyFont();
    const float nameSize = 20.f;
    const float detailSize = 15.f;
    if (display) {
        dl->AddText(display, nameSize, text, nameCol, listed.c_str());
    } else {
        dl->AddText(text, nameCol, listed.c_str());
    }
    const ImVec2 detailPos(text.x, text.y + nameSize + 2.f);
    if (body) {
        dl->AddText(body, detailSize, detailPos, ImGui::GetColorU32(detail), title.details);
    } else {
        dl->AddText(detailPos, ImGui::GetColorU32(detail), title.details);
    }
    drawCreatorStamp(dl, body, title.creator, detailPos, max, ready);
    dl->PopClipRect();
}

}
