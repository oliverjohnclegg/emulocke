#include "ui/NewRunOptions.hpp"

#include "tracker/Difficulty.hpp"
#include "ui/PresetPicker.hpp"

#include <imgui.h>
#include <cstddef>
#include <string>

namespace emulocke {
namespace {

void drawOptionalPatches(NewRunDraft& draft, const CatalogTitle& title) {
    if (title.optionCount == 0 || !title.options) {
        return;
    }
    ImGui::Text("Optional Patches");
    for (uint8_t i = 0; i < title.optionCount; ++i) {
        const PatchOption& option = title.options[i];
        if (i > 0) {
            ImGui::SameLine();
        }
        if (ImGui::RadioButton(option.label, draft.patchOption == option.id)) {
            draft.patchOption = option.id;
        }
    }
}

}  // namespace

void selectNewRunTitle(NewRunDraft& draft, const CatalogTitle& title) {
    draft.catalogUuid = title.uuid;
    draft.patchOption = std::string(catalogOptionId(title, {}));
    draft.difficulty = titleDefaultDifficulty(title.slug);
}

void bindNewRunTitle(NewRunDraft& draft, const CatalogTitle& title) {
    draft.patchOption = std::string(catalogOptionId(title, draft.patchOption));
    bindTitleDifficulty(draft.difficulty, title.slug);
}

void drawGameConfig(NewRunDraft& draft, const CatalogTitle& title) {
    const auto difficulties = titleDifficultyChoices(title.slug);
    const bool patches = title.optionCount > 0 && title.options;
    if (difficulties.empty() && !patches) {
        ImGui::TextDisabled("None for this title.");
        return;
    }
    if (!difficulties.empty()) {
        ImGui::Text("Difficulty");
        ImGui::PushID("difficulty");
        for (std::size_t i = 0; i < difficulties.size(); ++i) {
            const DifficultyChoice& choice = difficulties[i];
            if (i > 0) {
                ImGui::SameLine();
            }
            if (ImGui::RadioButton(choice.label, draft.difficulty == choice.id)) {
                draft.difficulty = choice.id;
            }
        }
        ImGui::PopID();
    }
    if (patches) {
        drawOptionalPatches(draft, title);
    }
}

void drawNuzlockeSettings(NuzlockeRules& rules) {
    drawPresetCombo(rules);
    if (ImGui::BeginTable("rules", 2, ImGuiTableFlags_SizingStretchProp)) {
        ImGui::TableNextColumn();
        ImGui::Checkbox("First encounter", &rules.firstEncounter);
        ImGui::Checkbox("Nicknames", &rules.nicknames);
        ImGui::Checkbox("Faint is death", &rules.faintIsDeath);
        ImGui::Checkbox("Dupes clause", &rules.dupesClause);
        ImGui::TableNextColumn();
        ImGui::Checkbox("Set mode", &rules.setMode);
        ImGui::Checkbox("No items in battle", &rules.noItemsInBattle);
        ImGui::Checkbox("Level cap", &rules.levelCap);
        ImGui::Checkbox("Shiny clause", &rules.shinyClause);
        ImGui::EndTable();
    }
}

}
