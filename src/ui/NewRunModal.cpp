#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "run/Catalog.hpp"
#include "ui/GamePicker.hpp"
#include "ui/NewRunOptions.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {
namespace {

void drawImportSavButton(Application& app, bool canStart) {
    const char* label = "Import from Existing .sav";
    const float width = ImGui::CalcTextSize(label).x + ImGui::GetStyle().FramePadding.x * 2.f;
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetWindowWidth() - ImGui::GetStyle().WindowPadding.x - width);
    if (!canStart) {
        ImGui::BeginDisabled();
    }
    if (ImGui::Button(label)) {
        app.requestImportSav();
    }
    if (!canStart) {
        ImGui::EndDisabled();
    }
}

void drawStartGate(const CatalogTitle* selected, bool canStart) {
    if (canStart || !selected) {
        return;
    }
    if (selected->kind == TitleKind::Hack) {
        const CatalogTitle* prereq = catalogByUuid(selected->prerequisiteUuid);
        ImGui::TextDisabled("Import %s first.", prereq ? prereq->fullName : "the baseline");
    } else {
        ImGui::TextDisabled("Import this dump to start.");
    }
}

}  // namespace

void drawNewRunModal(Application& app) {
    if (!app.showNewRun()) {
        return;
    }
    if (!ImGui::IsPopupOpen("NEW RUN")) {
        ImGui::OpenPopup("NEW RUN");
    }
    const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(520.f, 0.f), ImVec2(FLT_MAX, FLT_MAX));
    ImGui::PushStyleColor(ImGuiCol_PopupBg, kPanel);
    bool open = true;
    const ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoMove;
    if (!ImGui::BeginPopupModal("NEW RUN", &open, flags)) {
        ImGui::PopStyleColor();
        if (!open) {
            app.dismissNewRun();
        }
        return;
    }
    NewRunDraft& draft = app.newRunDraft();
    drawGamePicker(app, draft.catalogUuid);
    const CatalogTitle* selected = catalogByUuid(draft.catalogUuid);
    if (selected) {
        bindNewRunTitle(draft, *selected);
    }
    if (ImGui::BeginTabBar("new-run-tabs", ImGuiTabBarFlags_DrawSelectedOverline | ImGuiTabBarFlags_NoTooltip)) {
        if (ImGui::BeginTabItem("Game Config")) {
            if (selected) {
                drawGameConfig(draft, *selected);
            }
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Nuzlocke Settings")) {
            drawNuzlockeSettings(draft.rules);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    if (!app.status().empty() && app.status() != "No cart." && app.status() != "Cart seated.") {
        ImGui::TextWrapped("%s", app.status().c_str());
    }
    const bool canStart = selected && app.romLibrary().ready(*selected);
    drawStartGate(selected, canStart);
    if (!canStart) {
        ImGui::BeginDisabled();
    }
    if (ImGui::Button("START RUN")) {
        app.confirmNewRun();
        ImGui::CloseCurrentPopup();
    }
    if (!canStart) {
        ImGui::EndDisabled();
    }
    ImGui::SameLine();
    if (ImGui::Button("CANCEL")) {
        app.dismissNewRun();
        ImGui::CloseCurrentPopup();
    }
    drawImportSavButton(app, canStart);
    ImGui::EndPopup();
    ImGui::PopStyleColor();
    if (!open) {
        app.dismissNewRun();
    }
}

}