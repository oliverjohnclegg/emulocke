#include "ui/PresetPicker.hpp"

#include "run/NuzlockeRules.hpp"

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

}  // namespace

void drawPresetCombo(NuzlockeRules& rules) {
    ImGui::AlignTextToFramePadding();
    ImGui::TextUnformatted("Preset");
    ImGui::SameLine();
    const float w = 160.f;
    const float row = ImGui::GetTextLineHeightWithSpacing();
    ImGui::SetNextItemWidth(w);
    ImGui::SetNextWindowSize(
        ImVec2(w, row * static_cast<float>(IM_COUNTOF(kRulesPresets)) + ImGui::GetStyle().WindowPadding.y * 2.f));
    const bool open = ImGui::BeginCombo("##preset", rulesPresetTitle(rules), ImGuiComboFlags_HeightSmall);
    const ImVec2 min = ImGui::GetItemRectMin();
    const ImVec2 max = ImGui::GetItemRectMax();
    if (!open) {
        return;
    }
    ImGui::SetWindowPos(ImVec2(min.x, max.y));
    static bool armed = false;
    if (ImGui::IsWindowAppearing()) {
        armed = false;
    }
    if (!ImGui::IsMouseDown(ImGuiMouseButton_Left) && !ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
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

}
