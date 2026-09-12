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
            const std::string label = runHeadline(*run) + "##row";
            const float btn = showNewAttempt ? 148.f : 0.f;
            const float gap = showNewAttempt ? 8.f : 0.f;
            if (ImGui::Selectable(label.c_str(), false, 0, ImVec2(-btn - gap, 0))) {
                clicked = run->id;
            }
            if (showNewAttempt) {
                ImGui::SameLine();
                if (ImGui::Button("NEW ATTEMPT")) {
                    app.queueNewAttempt(run->id);
                }
            }
            ImGui::PopID();
        }
    }
    return clicked;
}

}
