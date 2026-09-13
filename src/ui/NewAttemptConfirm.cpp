#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {

void drawNewAttemptConfirm(Application& app) {
    if (!app.showNewAttemptConfirm()) {
        return;
    }
    if (!ImGui::IsPopupOpen("START NEW ATTEMPT")) {
        ImGui::OpenPopup("START NEW ATTEMPT");
    }
    const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(420.f, 0.f), ImGuiCond_Appearing);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(16.f, 14.f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.f);
    ImGui::PushStyleColor(ImGuiCol_PopupBg, kPanel);
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(kMetal.x, kMetal.y, kMetal.z, 0.45f));
    bool open = true;
    const ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove;
    if (!ImGui::BeginPopupModal("START NEW ATTEMPT", &open, flags)) {
        ImGui::PopStyleColor(2);
        ImGui::PopStyleVar(2);
        if (!open) {
            app.dismissNewAttempt();
        }
        return;
    }
    ImGui::Dummy(ImVec2(380.f, 0));
    ImGui::PushStyleColor(ImGuiCol_Text, ImGui::ColorConvertU32ToFloat4(kPaused));
    ImGui::TextWrapped("This ends the current attempt and deletes its save. There is no undo.");
    ImGui::PopStyleColor();
    ImGui::Dummy(ImVec2(0, 12));
    ImGui::PushStyleColor(ImGuiCol_Text, ImGui::ColorConvertU32ToFloat4(kPaused));
    if (ImGui::Button("START NEW ATTEMPT", ImVec2(220.f, 0))) {
        app.confirmNewAttempt();
        ImGui::CloseCurrentPopup();
    }
    ImGui::PopStyleColor();
    ImGui::SameLine();
    if (ImGui::Button("CANCEL", ImVec2(140.f, 0))) {
        app.dismissNewAttempt();
        ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar(2);
    if (!open) {
        app.dismissNewAttempt();
    }
}

}
