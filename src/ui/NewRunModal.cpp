#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "run/Catalog.hpp"
#include "run/NuzlockeRules.hpp"

#include <imgui.h>
#include <algorithm>

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

bool titleReady(const RomLibrary& lib, const CatalogTitle& title) {
    if (title.kind == TitleKind::Baseline) {
        return lib.has(title.uuid);
    }
    return title.prerequisiteUuid && lib.has(title.prerequisiteUuid);
}

}  // namespace

void drawNewRunModal(Application& app) {
    if (!app.showNewRun()) {
        return;
    }
    const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    if (!ImGui::Begin("NEW RUN", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse)) {
        ImGui::End();
        return;
    }
    NewRunDraft& draft = app.newRunDraft();
    const auto titles = app.romLibrary().playableTitles();
    const CatalogTitle* selected = catalogByUuid(draft.catalogUuid);
    if (!titles.empty() && (!selected || std::find(titles.begin(), titles.end(), selected) == titles.end())) {
        draft.catalogUuid = titles.front()->uuid;
        selected = titles.front();
    }
    if (titles.empty()) {
        ImGui::TextWrapped("Import a Pokemon dump to start a run.");
    } else {
        const char* current = selected ? selected->title : "Game";
        if (ImGui::BeginCombo("Game", current)) {
            for (const CatalogTitle* title : titles) {
                if (ImGui::Selectable(title->title, title->uuid == draft.catalogUuid)) {
                    draft.catalogUuid = title->uuid;
                    selected = title;
                }
            }
            ImGui::EndCombo();
        }
        if (selected && selected->kind == TitleKind::Hack) {
            const CatalogTitle* prereq = catalogByUuid(selected->prerequisiteUuid);
            if (prereq && !app.romLibrary().has(prereq->uuid)) {
                ImGui::TextWrapped("%s is a prerequisite for this ROM hack.", prereq->fullName);
            }
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
    const bool canStart = selected && titleReady(app.romLibrary(), *selected);
    if (!canStart) {
        ImGui::BeginDisabled();
    }
    if (ImGui::Button("START RUN")) {
        app.confirmNewRun();
    }
    if (!canStart) {
        ImGui::EndDisabled();
    }
    ImGui::SameLine();
    if (ImGui::Button("CANCEL")) {
        app.dismissNewRun();
    }
    ImGui::End();
}

}
