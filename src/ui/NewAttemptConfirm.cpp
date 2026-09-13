#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {
namespace {

bool namedPlate(const char* id, const char* label, ImVec2 size, bool danger) {
    const ImVec2 p = ImGui::GetCursorScreenPos();
    ImGui::InvisibleButton(id, size);
    const bool hovered = ImGui::IsItemHovered();
    const bool clicked = ImGui::IsItemClicked();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImVec2 q(p.x + size.x, p.y + size.y);
    dl->AddRectFilled(p, q, ImGui::GetColorU32(hovered ? kHeaderHover : kButton));
    dl->AddRect(p, q, ImGui::GetColorU32(kBorder));
    if (danger) {
        dl->AddRectFilled(p, ImVec2(q.x, p.y + 2.f), kPaused);
    }
    const ImVec2 ts = ImGui::CalcTextSize(label);
    dl->AddText(ImVec2(p.x + (size.x - ts.x) * 0.5f, p.y + (size.y - ts.y) * 0.5f),
        ImGui::GetColorU32(kMetal), label);
    return clicked;
}

}  // namespace

void drawNewAttemptConfirm(Application& app) {
    if (!app.showNewAttemptConfirm()) {
        return;
    }
    if (!ImGui::IsPopupOpen("START NEW ATTEMPT")) {
        ImGui::OpenPopup("START NEW ATTEMPT");
    }
    const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(14.f, 14.f));
    ImGui::PushStyleColor(ImGuiCol_PopupBg, kPanel);
    bool open = true;
    const ImGuiWindowFlags flags =
        ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar;
    if (!ImGui::BeginPopupModal("START NEW ATTEMPT", &open, flags)) {
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        if (!open) {
            app.dismissNewAttempt();
        }
        return;
    }
    const float plateW = 372.f;
    ImGui::Dummy(ImVec2(plateW, 0));
    if (app.displayFont()) {
        ImGui::PushFont(app.displayFont());
    }
    ImGui::TextUnformatted("START NEW ATTEMPT");
    if (app.displayFont()) {
        ImGui::PopFont();
    }
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, kScreenWell);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12.f, 12.f));
    ImGui::BeginChild("warn", ImVec2(plateW, 0),
        ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysUseWindowPadding);
    ImGui::TextUnformatted("This ends the current attempt and deletes its save.");
    ImGui::TextUnformatted("There is no undo.");
    ImGui::EndChild();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    ImGui::Dummy(ImVec2(0, 12));
    const float gap = 5.f;
    const ImVec2 btn((plateW - gap) * 0.5f, 28.f);
    if (namedPlate("end", "START NEW ATTEMPT", btn, true)) {
        app.confirmNewAttempt();
        ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine(0.f, gap);
    if (namedPlate("hold", "CANCEL", btn, false)) {
        app.dismissNewAttempt();
        ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    if (!open) {
        app.dismissNewAttempt();
    }
}

}
