#include "ui/Shell.hpp"

#include "application/Application.hpp"

#include <imgui.h>

namespace emulocke {

void drawLoadRunModal(Application& app) {
    if (app.showLoadRun() && !ImGui::IsPopupOpen("LOAD RUN")) {
        ImGui::OpenPopup("LOAD RUN", ImGuiPopupFlags_NoOpenOverExistingPopup);
    }
    if (ImGui::IsPopupOpen("LOAD RUN")) {
        ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowSize(ImVec2(480.f, 360.f), ImGuiCond_Appearing);
    }
    if (!ImGui::BeginPopupModal("LOAD RUN", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        return;
    }
    const std::string id = drawGroupedRunList(app, "load", false);
    if (!id.empty()) {
        app.queueLoadRun(id);
        ImGui::CloseCurrentPopup();
    }
    ImGui::Dummy(ImVec2(0, 8));
    if (ImGui::Button("CANCEL")) {
        app.dismissLoadRun();
        ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
}

}