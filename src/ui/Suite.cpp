#include "ui/Suite.hpp"

#include "application/Application.hpp"
#include "ui/FieldLog.hpp"

#include <imgui.h>

namespace emulocke {

void drawSuite(Application& app, ImVec2 size) {
    ImGui::BeginChild("suite", size, ImGuiChildFlags_Borders);
    if (ImGui::BeginTabBar("suite-tabs", ImGuiTabBarFlags_DrawSelectedOverline)) {
        if (ImGui::BeginTabItem("Logs")) {
            drawFieldLog(app);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    ImGui::EndChild();
}

}
