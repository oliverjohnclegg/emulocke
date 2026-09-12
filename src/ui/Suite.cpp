#include "ui/Suite.hpp"

#include "application/Application.hpp"
#include "ui/FieldLog.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {

void drawSuite(Application& app, ImVec2 size) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, kScreenWell);
    ImGui::BeginChild("suite", size, ImGuiChildFlags_Borders);
    ImGui::PopStyleColor();
    if (ImFont* display = app.displayFont()) {
        ImGui::PushFont(display);
    }
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(ImGui::GetStyle().ItemSpacing.x, 0.f));
    if (ImGui::BeginTabBar("suite-tabs", ImGuiTabBarFlags_DrawSelectedOverline | ImGuiTabBarFlags_NoTooltip)) {
        if (ImGui::BeginTabItem("Logs")) {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, kPanel);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.f, 10.f));
            ImGui::BeginChild("logs", ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_AlwaysUseWindowPadding);
            drawFieldLog(app);
            ImGui::EndChild();
            ImGui::PopStyleVar();
            ImGui::PopStyleColor();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::PopStyleVar();
    if (app.displayFont()) {
        ImGui::PopFont();
    }
    ImGui::EndChild();
}

}
