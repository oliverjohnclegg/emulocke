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
    ImGui::PushStyleColor(ImGuiCol_PopupBg, kChassis);
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
    ImGui::Dummy(ImVec2(0, 6));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 10));
    const char* warn = "This ends the current attempt and deletes its save. There is no undo.";
    const float wellPad = 10.f;
    const float wrapW = plateW - wellPad * 2.f;
    const ImVec2 warnSize = ImGui::CalcTextSize(warn, nullptr, false, wrapW);
    const float wellH = warnSize.y + wellPad * 2.f;
    const ImVec2 well = ImGui::GetCursorScreenPos();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->AddRectFilled(well, ImVec2(well.x + plateW, well.y + wellH), ImGui::GetColorU32(kScreenWell));
    dl->AddRect(well, ImVec2(well.x + plateW, well.y + wellH), ImGui::GetColorU32(kBorder));
    dl->AddRectFilled(well, ImVec2(well.x + plateW, well.y + 2.f), kPaused);
    ImGui::SetCursorScreenPos(ImVec2(well.x + wellPad, well.y + wellPad));
    ImGui::PushTextWrapPos(well.x + plateW - wellPad);
    ImGui::TextUnformatted(warn);
    ImGui::PopTextWrapPos();
    ImGui::SetCursorScreenPos(ImVec2(well.x, well.y + wellH + 14.f));
    const float gap = 5.f;
    const float btnW = (plateW - gap) * 0.5f;
    const ImVec2 btn(btnW, 28.f);
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
