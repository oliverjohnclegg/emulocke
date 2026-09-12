#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "run/GameId.hpp"
#include "run/NuzlockeRules.hpp"

#include <imgui.h>

namespace emulocke {
namespace {

void drawPresetCombo(NuzlockeRules& rules) {
    if (!ImGui::BeginCombo("Preset", rulesPresetTitle(rules))) {
        return;
    }
    if (ImGui::Selectable("Regular", rules == regularRules())) {
        rules = regularRules();
    }
    if (ImGui::Selectable("Hardcore", rules == hardcoreRules())) {
        rules = hardcoreRules();
    }
    ImGui::EndCombo();
}

}  // namespace

void drawNewRunModal(Application& app) {
    if (app.showNewRun()) {
        ImGui::OpenPopup("NEW RUN");
    }
    if (ImGui::IsPopupOpen("NEW RUN")) {
        const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    }
    if (!ImGui::BeginPopupModal("NEW RUN", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        return;
    }
    NewRunDraft& draft = app.newRunDraft();
    const auto& games = app.detectedGames();
    if (games.empty()) {
        ImGui::TextWrapped("No Pokemon ROM in the roms folder.");
        ImGui::TextDisabled("%s", app.romsHint().c_str());
    } else {
        if (draft.gameIndex >= static_cast<int>(games.size())) {
            draft.gameIndex = 0;
        }
        const char* current = gameTitle(games[static_cast<size_t>(draft.gameIndex)].gameId);
        if (ImGui::BeginCombo("Game", current)) {
            for (int i = 0; i < static_cast<int>(games.size()); ++i) {
                const char* label = gameTitle(games[static_cast<size_t>(i)].gameId);
                if (ImGui::Selectable(label, i == draft.gameIndex)) {
                    draft.gameIndex = i;
                }
            }
            ImGui::EndCombo();
        }
        drawPresetCombo(draft.rules);
        if (ImGui::BeginTable("rules", 2, ImGuiTableFlags_SizingStretchProp)) {
            ImGui::TableNextColumn();
            ImGui::Checkbox("First encounter", &draft.rules.firstEncounter);
            ImGui::Checkbox("Nicknames", &draft.rules.nicknames);
            ImGui::Checkbox("Faint is death", &draft.rules.faintIsDeath);
            ImGui::Checkbox("Dupes clause", &draft.rules.dupesClause);
            ImGui::TableNextColumn();
            ImGui::Checkbox("Set mode", &draft.rules.setMode);
            ImGui::Checkbox("No items in battle", &draft.rules.noItemsInBattle);
            ImGui::Checkbox("Level cap", &draft.rules.levelCap);
            ImGui::Checkbox("Shiny clause", &draft.rules.shinyClause);
            ImGui::EndTable();
        }
    }
    const bool canStart = !games.empty();
    if (!canStart) {
        ImGui::BeginDisabled();
    }
    if (ImGui::Button("START RUN")) {
        app.confirmNewRun();
        ImGui::CloseCurrentPopup();
    }
    if (!canStart) {
        ImGui::EndDisabled();
    }
    ImGui::SameLine();
    if (ImGui::Button("CANCEL")) {
        app.dismissNewRun();
        ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
}

}
