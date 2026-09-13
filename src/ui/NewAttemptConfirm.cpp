#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {

void drawNewAttemptConfirm(Application& app) {
    if (!app.showNewAttemptConfirm()) {
        return;
    }
    if (!ImGui::IsPopupOpen("Start New Attempt")) {
        ImGui::OpenPopup("Start New Attempt");
    }
    const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(420.f, 0.f), ImGuiCond_Appearing);
    const ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar;
    bool open = true;
    if (!ImGui::BeginPopupModal("Start New Attempt", &open, flags)) {
        if (!open) {
            app.dismissNewAttempt();
        }
        return;
    }
    if (app.displayFont()) {
        ImGui::PushFont(app.displayFont());
    }
    ImGui::TextUnformatted("START NEW ATTEMPT");
    if (app.displayFont()) {
        ImGui::PopFont();
    }
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));
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
    if (!open) {
        app.dismissNewAttempt();
    }
}

}
