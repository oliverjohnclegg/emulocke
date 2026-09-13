#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {

void drawLoadingRunModal(Application& app) {
    if (!app.showLoadingRun()) {
        return;
    }
    const ImGuiViewport* vp = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(vp->WorkPos);
    ImGui::SetNextWindowSize(vp->WorkSize);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(kChassis.x, kChassis.y, kChassis.z, 0.72f));
    ImGui::Begin("##loading-run-dim", nullptr,
                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings |
                     ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs |
                     ImGuiWindowFlags_NoBringToFrontOnFocus);
    ImGui::End();
    ImGui::PopStyleColor();
    ImGui::SetNextWindowPos(vp->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    if (!ImGui::Begin("LOADING RUN", nullptr,
                      ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse |
                          ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings)) {
        ImGui::End();
        return;
    }
    ImGui::Dummy(ImVec2(320.f, 0.f));
    ImGui::TextWrapped("Seating the cart and opening the dump.");
    ImGui::End();
}

}
