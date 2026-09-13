#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "run/Catalog.hpp"
#include "run/NuzlockeRules.hpp"
#include "ui/GamePicker.hpp"

#include <imgui.h>

namespace emulocke {
namespace {

void drawPresetCombo(NuzlockeRules& rules) {
    ImGui::AlignTextToFramePadding();
    ImGui::TextUnformatted("Preset");
    ImGui::SameLine();
    const bool regular = rules == regularRules();
    if (regular) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive));
    }
    if (ImGui::Button("Regular")) {
        rules = regularRules();
    }
    if (regular) {
        ImGui::PopStyleColor();
    }
    ImGui::SameLine();
    const bool hardcore = rules == hardcoreRules();
    if (hardcore) {
        ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonActive));
    }
    if (ImGui::Button("Hardcore")) {
        rules = hardcoreRules();
    }
    if (hardcore) {
        ImGui::PopStyleColor();
    }
}

}  // namespace

void drawNewRunModal(Application& app) {
    if (!app.showNewRun()) {
        return;
    }
    const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(420.f, 0.f), ImVec2(FLT_MAX, FLT_MAX));
    if (!ImGui::Begin("NEW RUN", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse)) {
        ImGui::End();
        return;
    }
    NewRunDraft& draft = app.newRunDraft();
    drawGamePicker(app, draft.catalogUuid);
    const CatalogTitle* selected = catalogByUuid(draft.catalogUuid);
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
    const bool canStart = selected && app.romLibrary().ready(*selected);
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
