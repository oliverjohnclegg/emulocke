#include "ui/Shell.hpp"

#include "application/Application.hpp"

#include <imgui.h>

namespace emulocke {
namespace {

void controlRow(const char* action, const char* binding) {
    ImGui::TextUnformatted(action);
    ImGui::SameLine(168.f);
    ImGui::TextDisabled("%s", binding);
}

}  // namespace

void drawHelpPopups(Application& app) {
    const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    const ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar;
    if (ImGui::IsPopupOpen("Controls")) {
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    }
    if (ImGui::BeginPopupModal("Controls", nullptr, flags)) {
        if (app.displayFont()) {
            ImGui::PushFont(app.displayFont());
        }
        ImGui::TextUnformatted("CONTROLS");
        if (app.displayFont()) {
            ImGui::PopFont();
        }
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0, 8));
        controlRow("D-pad", "Arrow keys");
        controlRow("A / B", "X / Z");
        controlRow("L / R", "A / S");
        controlRow("Start", "Enter");
        controlRow("Select", "Shift");
        controlRow("Stylus", "Mouse on bottom screen");
        controlRow("Speed-up", app.prefs().speedUpHold ? "Hold Tab" : "Tab");
        controlRow("Right pane", "F8");
        ImGui::Dummy(ImVec2(0, 10));
        ImGui::TextDisabled("Gamepad uses the standard SDL map.");
        ImGui::Dummy(ImVec2(0, 12));
        if (ImGui::Button("Close", ImVec2(140, 0))) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    if (ImGui::IsPopupOpen("About")) {
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImVec2(420, 0), ImGuiCond_Appearing);
    }
    if (ImGui::BeginPopupModal("About", nullptr, flags)) {
        if (app.displayFont()) {
            ImGui::PushFont(app.displayFont());
        }
        ImGui::TextUnformatted("EMULOCKE");
        if (app.displayFont()) {
            ImGui::PopFont();
        }
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0, 8));
        ImGui::TextUnformatted("Pokemon nuzlocking suite");
        ImGui::Dummy(ImVec2(0, 8));
        ImGui::TextWrapped(
            "One field kit for the game and the expedition tools. GBA and DS carts are just games here.");
        ImGui::Spacing();
        ImGui::TextWrapped("No save states, disassemblers, or memory tools. Frame skip comes later.");
        ImGui::Dummy(ImVec2(0, 12));
        if (ImGui::Button("Close", ImVec2(140, 0))) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

}
