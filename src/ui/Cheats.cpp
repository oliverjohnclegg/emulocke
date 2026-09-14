#include "ui/Cheats.hpp"

#include "application/Application.hpp"
#include "cheats/Book.hpp"
#include "ui/IconAction.hpp"

#include <imgui.h>
#include <string>

namespace emulocke {

void drawCheats(Application& app) {
    if (app.bodyFont()) {
        ImGui::PushFont(app.bodyFont());
    }
    ImGui::Dummy(ImVec2(0, 8));
    if (app.activeRunId().empty()) {
        ImGui::TextDisabled("No cart seated.");
        ImGui::Spacing();
        ImGui::TextWrapped("Cheats attach to a game once a run is going.");
        if (app.bodyFont()) {
            ImGui::PopFont();
        }
        return;
    }
    const auto& items = app.cheats().items();
    if (items.empty()) {
        ImGui::TextDisabled("No cheats for this title.");
        ImGui::Spacing();
        ImGui::TextWrapped("Add one below. They stay with this game on new attempts.");
    } else if (ImGui::BeginTable("cheat-rows", 3, ImGuiTableFlags_SizingStretchProp)) {
        ImGui::TableSetupColumn("on", ImGuiTableColumnFlags_WidthFixed, 22.f);
        ImGui::TableSetupColumn("name", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("del", ImGuiTableColumnFlags_WidthFixed, 18.f);
        std::string doomed;
        for (const Cheat& row : items) {
            ImGui::PushID(row.id.c_str());
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            bool on = row.enabled;
            if (ImGui::Checkbox("##on", &on) && on != row.enabled) {
                app.setCheatEnabled(row.id, on);
            }
            ImGui::TableNextColumn();
            ImGui::TextUnformatted(row.name.c_str());
            ImGui::TableNextColumn();
            const ImVec2 pos = ImGui::GetCursorScreenPos();
            if (iconAction("del", "Delete", ImVec2(18.f, 18.f))) {
                doomed = row.id;
            }
            iconX(pos, ImVec2(18.f, 18.f));
            ImGui::PopID();
        }
        ImGui::EndTable();
        if (!doomed.empty()) {
            app.removeCheat(doomed);
        }
    }
    ImGui::Dummy(ImVec2(0, 10));
    drawCheatsAdd(app);
    if (app.bodyFont()) {
        ImGui::PopFont();
    }
}

}
