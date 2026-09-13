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

void drawComboChrome(const ImVec2& min, const ImVec2& max, const char* preview, bool hovered, bool open) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImGuiStyle& style = ImGui::GetStyle();
    const float h = max.y - min.y;
    const float mid = max.x - h;
    dl->AddRectFilled(min, ImVec2(mid, max.y), ImGui::GetColorU32(hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg));
    dl->AddRectFilled(
        ImVec2(mid, min.y),
        max,
        ImGui::GetColorU32((open || hovered) ? ImGuiCol_ButtonHovered : ImGuiCol_Button));
    dl->AddRect(min, max, ImGui::GetColorU32(ImGuiCol_Border));
    dl->AddTriangleFilled(
        ImVec2(mid + h * 0.32f, min.y + h * 0.38f),
        ImVec2(mid + h * 0.68f, min.y + h * 0.38f),
        ImVec2(mid + h * 0.50f, min.y + h * 0.64f),
        ImGui::GetColorU32(ImGuiCol_Text));
    dl->PushClipRect(min, ImVec2(mid, max.y), true);
    dl->AddText(
        ImVec2(min.x + style.FramePadding.x, min.y + style.FramePadding.y),
        ImGui::GetColorU32(ImGuiCol_Text),
        preview);
    dl->PopClipRect();
}

}  // namespace

void drawPresetCombo(NuzlockeRules& rules) {
    ImGui::AlignTextToFramePadding();
    ImGui::TextUnformatted("Preset");
    ImGui::SameLine();
    const float w = 160.f;
    const float h = ImGui::GetFrameHeight();
    static bool openLast = false;
    const bool wasOpen = openLast;
    if (ImGui::InvisibleButton("##preset", ImVec2(w, h)) && !wasOpen) {
        ImGui::OpenPopup("##preset_menu");
    }
    const ImVec2 min = ImGui::GetItemRectMin();
    const ImVec2 max = ImGui::GetItemRectMax();
    const bool open = ImGui::IsPopupOpen("##preset_menu");
    drawComboChrome(min, max, rulesPresetTitle(rules), ImGui::IsItemHovered(), open);
    if (open) {
        const float row = ImGui::GetTextLineHeightWithSpacing();
        ImGui::SetNextWindowPos(ImVec2(min.x, max.y));
        ImGui::SetNextWindowSize(
            ImVec2(w, row * static_cast<float>(IM_COUNTOF(kRulesPresets)) + ImGui::GetStyle().WindowPadding.y * 2.f));
    }
    if (ImGui::BeginPopup("##preset_menu")) {
        for (const RulesPreset& preset : kRulesPresets) {
            const NuzlockeRules baked = preset.make();
            if (ImGui::Selectable(preset.title, rules == baked)) {
                rules = baked;
            }
        }
        ImGui::EndPopup();
    }
    openLast = ImGui::IsPopupOpen("##preset_menu");
}

}
