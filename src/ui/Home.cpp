#include "ui/Shell.hpp"

#include "application/Application.hpp"

#include <imgui.h>

namespace emulocke {

void drawHome(Application& app) {
    ImGui::BeginChild("expedition", ImVec2(0, 0), ImGuiChildFlags_Borders);
    if (ImFont* display = app.displayFont()) {
        ImGui::PushFont(display);
    }
    ImGui::TextUnformatted("EXPEDITION LOG");
    if (app.displayFont()) {
        ImGui::PopFont();
    }
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));
    if (ImGui::Button("NEW RUN")) {
        app.requestNewRun();
    }
    if (app.runStore().runs().empty()) {
        ImGui::Dummy(ImVec2(0, 16));
        ImGui::TextDisabled("No expeditions logged.");
        ImGui::Spacing();
        ImGui::TextWrapped("Put a Pokemon ROM in the roms folder, then start a New Run.");
        ImGui::Spacing();
        ImGui::TextDisabled("%s", app.romsHint().c_str());
    } else {
        const std::string id = drawGroupedRunList(app, "home", true);
        if (!id.empty()) {
            app.queueLoadRun(id);
        }
    }
    ImGui::EndChild();
}

}