#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {

void drawLoadingRunModal(Application& app) {
    if (app.showLoadingRun() && !ImGui::IsPopupOpen("LOADING RUN")) {
        ImGui::OpenPopup("LOADING RUN");
    }
    if (!ImGui::IsPopupOpen("LOADING RUN")) {
        return;
    }
    const ImGuiViewport* vp = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(vp->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_PopupBg, kPanel);
    const ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
    if (!ImGui::BeginPopupModal("LOADING RUN", nullptr, flags)) {
        ImGui::PopStyleColor();
        return;
    }
    ImGui::Dummy(ImVec2(320.f, 0.f));
    ImGui::TextWrapped("Seating the cart and opening the dump.");
    if (!app.showLoadingRun()) {
        ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
    ImGui::PopStyleColor();
}

}