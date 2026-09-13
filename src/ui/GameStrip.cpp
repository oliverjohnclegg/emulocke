#include "ui/GameStrip.hpp"

#include "application/Application.hpp"

#include <imgui.h>
#include <string_view>

namespace emulocke {

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
