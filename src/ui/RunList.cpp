#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "run/GameId.hpp"
#include "run/RunLabel.hpp"

#include <imgui.h>
#include <string>

namespace emulocke {

std::string drawGroupedRunList(Application& app, const char* idPrefix, bool showNewAttempt) {
    std::string clicked;
    const RunStore& store = app.runStore();
    for (int i = 0; i < kGameCount; ++i) {
        const GameId game = gameIdAt(i);
        const auto runs = store.byGame(game);
        if (runs.empty()) {
            continue;
        }
        if (ImFont* display = app.displayFont()) {
            ImGui::PushFont(display);
        }
        ImGui::Dummy(ImVec2(0, 8));
        ImGui::TextUnformatted(gameTitle(game));
        if (app.displayFont()) {
            ImGui::PopFont();
        }
        ImGui::Separator();
        for (const Run* run : runs) {
            ImGui::PushID((std::string(idPrefix) + run->id).c_str());
            const std::string headline = runHeadline(*run);
            if (showNewAttempt) {
                if (ImGui::BeginTable("run_row", 2, ImGuiTableFlags_SizingStretchProp)) {
                    ImGui::TableSetupColumn("name", ImGuiTableColumnFlags_WidthStretch);
                    ImGui::TableSetupColumn("act", ImGuiTableColumnFlags_WidthFixed, 150.f);
                    ImGui::TableNextColumn();
                    if (ImGui::Selectable(headline.c_str())) {
                        clicked = run->id;
                    }
                    ImGui::TableNextColumn();
                    if (ImGui::Button("NEW ATTEMPT")) {
                        app.queueNewAttempt(run->id);
                    }
                    ImGui::EndTable();
                }
            } else if (ImGui::Selectable(headline.c_str())) {
                clicked = run->id;
            }
            ImGui::PopID();
        }
    }
    return clicked;
}

}
