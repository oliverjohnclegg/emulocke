#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "run/Catalog.hpp"
#include "run/NuzlockeRules.hpp"
#include "ui/GamePicker.hpp"

#include <imgui.h>

namespace emulocke {
namespace {

struct RulesPreset {
    const char* title;
    NuzlockeRules (*make)();
};

const RulesPreset kRulesPresets[] = {
    {"Regular", regularRules},
    {"Hardcore", hardcoreRules},
};

void drawPresetCombo(NuzlockeRules& rules) {
    ImGui::AlignTextToFramePadding();
    ImGui::TextUnformatted("Preset");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(160.f);
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    const float row = ImGui::GetTextLineHeightWithSpacing();
    ImGui::SetNextWindowPos(ImVec2(origin.x, origin.y + ImGui::GetFrameHeight()));
    ImGui::SetNextWindowSizeConstraints(
        ImVec2(160.f, row * static_cast<float>(IM_COUNTOF(kRulesPresets))),
        ImVec2(FLT_MAX, FLT_MAX));
    if (!ImGui::BeginCombo("##preset", rulesPresetTitle(rules), ImGuiComboFlags_HeightSmall)) {
        return;
    }
    static bool armed = false;
    if (ImGui::IsWindowAppearing()) {
        armed = false;
    }
    if (!armed && !ImGui::IsMouseDown(ImGuiMouseButton_Left) && !ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
        armed = true;
    }
    const ImGuiSelectableFlags flags = armed ? 0 : ImGuiSelectableFlags_NoAutoClosePopups;
    for (const RulesPreset& preset : kRulesPresets) {
        const NuzlockeRules baked = preset.make();
        if (ImGui::Selectable(preset.title, rules == baked, flags) && armed) {
            rules = baked;
        }
    }
    ImGui::EndCombo();
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
