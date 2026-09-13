#include "ui/GameStrip.hpp"

#include "application/Application.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <SDL3/SDL.h>
#include <cstdint>
#include <string>
#include <string_view>

namespace emulocke {

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
    dl->PopClipRect();
}

bool drawTitleStripRow(Application& app, const CatalogTitle& title, std::string& catalogUuid) {
    const bool ready = app.romLibrary().ready(title);
    ImGui::PushID(title.uuid);
    const bool hit = ImGui::Selectable("##row", catalogUuid == title.uuid, 0, ImVec2(0.f, kTitleStripH));
    if (!ready && ImGui::IsItemHovered()) {
        if (title.kind == TitleKind::Hack) {
            const CatalogTitle* prereq = catalogByUuid(title.prerequisiteUuid);
            std::string_view spoken = prereq ? prereq->fullName : "a baseline";
            if (spoken.starts_with("Pokemon ")) {
                spoken.remove_prefix(8);
            }
            ImGui::SetTooltip("This game requires %s as a dependency to be played", spoken.data());
        } else {
            ImGui::SetTooltip("This game needs to be imported to play.");
        }
    }
    drawTitleStrip(app, title, ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), ready);
    ImGui::PopID();
    if (hit) {
        catalogUuid = title.uuid;
        if (!ready) {
            app.requestImportFor(title.uuid);
        }
    }
    return hit;
}

}
