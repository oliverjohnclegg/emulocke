#include "ui/Suite.hpp"

#include "application/Application.hpp"
#include "emu/EmuSession.hpp"

#include <imgui.h>

namespace emulocke {

void drawSuite(Application& app, ImVec2 size) {
    ImGui::BeginChild("suite", size, ImGuiChildFlags_Borders);
    if (ImFont* body = app.bodyFont()) {
        ImGui::PushFont(body);
    }
    if (ImGui::BeginTabBar("suite-tabs", ImGuiTabBarFlags_DrawSelectedOverline)) {
        if (ImGui::BeginTabItem("Logs")) {
            ImGui::Dummy(ImVec2(0, 8));
            if (!app.status().empty()) {
                ImGui::TextUnformatted(app.status().c_str());
            }
            if (EmuSession* session = app.session()) {
                ImGui::TextDisabled("%s", session->romName().c_str());
            }
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    if (app.bodyFont()) {
        ImGui::PopFont();
    }
    ImGui::EndChild();
}

}
