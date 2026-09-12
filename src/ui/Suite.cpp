#include "ui/Suite.hpp"

#include "application/Application.hpp"
#include "emu/EmuSession.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {

void drawSuite(Application& app, ImVec2 size) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, kScreenWell);
    ImGui::BeginChild("suite", size, ImGuiChildFlags_Borders);
    ImGui::PopStyleColor();
    if (ImFont* body = app.bodyFont()) {
        ImGui::PushFont(body);
    }
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.f, 5.f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(ImGui::GetStyle().ItemSpacing.x, 0.f));
    const bool tabs = ImGui::BeginTabBar("suite-tabs", ImGuiTabBarFlags_DrawSelectedOverline);
    ImGui::PopStyleVar(2);
    if (tabs) {
        if (ImGui::BeginTabItem("Logs")) {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, kPanel);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.f, 10.f));
            ImGui::BeginChild("logs", ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_AlwaysUseWindowPadding);
            if (!app.status().empty()) {
                ImGui::TextUnformatted(app.status().c_str());
            }
            if (EmuSession* session = app.session()) {
                ImGui::TextDisabled("%s", session->romName().c_str());
            }
            ImGui::EndChild();
            ImGui::PopStyleVar();
            ImGui::PopStyleColor();
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
