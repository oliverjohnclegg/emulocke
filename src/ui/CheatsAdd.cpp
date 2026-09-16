#include "ui/Cheats.hpp"

#include "application/Application.hpp"
#include "ui/KitMark.hpp"
#include "ui/KitNav.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {
namespace {

bool plate(const char* id, const char* label, ImVec2 size, bool focus) {
    const ImVec2 p = ImGui::GetCursorScreenPos();
    ImGui::InvisibleButton(id, size);
    const bool hovered = ImGui::IsItemHovered();
    const bool clicked = ImGui::IsItemClicked();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImVec2 q(p.x + size.x, p.y + size.y);
    dl->AddRectFilled(p, q, kitPlate(hovered || focus));
    dl->AddRect(p, q, ImGui::GetColorU32(kBorder));
    kitStroke(p, q, focus);
    const ImVec2 ts = ImGui::CalcTextSize(label);
    dl->AddText(ImVec2(p.x + (size.x - ts.x) * 0.5f, p.y + (size.y - ts.y) * 0.5f),
        ImGui::GetColorU32(kMetal), label);
    return clicked;
}

}  // namespace

void drawCheatsAdd(Application& app) {
    const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(14.f, 14.f));
    ImGui::PushStyleColor(ImGuiCol_PopupBg, kPanel);
    const ImGuiWindowFlags flags =
        ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar;
    if (!ImGui::BeginPopupModal("ADD", nullptr, flags)) {
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        return;
    }
    const float plateW = 320.f;
    ImGui::Dummy(ImVec2(plateW, 0));
    if (app.displayFont()) {
        ImGui::PushFont(app.displayFont());
    }
    ImGui::TextUnformatted("ADD");
    if (app.displayFont()) {
        ImGui::PopFont();
    }
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, kScreenWell);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12.f, 12.f));
    ImGui::BeginChild("cheat-draft", ImVec2(plateW, 0),
        ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_AlwaysUseWindowPadding);
    drawCheatDraft(app);
    ImGui::EndChild();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    ImGui::Dummy(ImVec2(0, 12));
    KitFocus& focus = app.kitFocus();
    const bool hold = kitModalHold() || ImGui::GetIO().WantTextInput;
    if (kitModalHold()) {
        focus.modalIndex = 1;
    }
    if (!hold) {
        kitMove(focus.modalIndex, 2, app.kit().left, app.kit().right);
        if (app.kit().pause) {
            ImGui::CloseCurrentPopup();
        }
    }
    const float gap = 5.f;
    const ImVec2 btn((plateW - gap) * 0.5f, 28.f);
    if ((plate("ok", "ADD", btn, focus.modalIndex == 0) ||
            (!hold && app.kit().act && focus.modalIndex == 0)) &&
        takeCheatDraft(app)) {
        ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine(0.f, gap);
    if (plate("cancel", "CANCEL", btn, focus.modalIndex == 1) ||
        (!hold && app.kit().act && focus.modalIndex == 1)) {
        ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}

}
