#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "run/Catalog.hpp"
#include "ui/GamePicker.hpp"
#include "ui/NewRunOptions.hpp"

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

}  // namespace

void drawNewRunModal(Application& app) {
    if (!app.showNewRun()) {
        return;
    }
    const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSizeConstraints(ImVec2(520.f, 0.f), ImVec2(FLT_MAX, FLT_MAX));
    if (!ImGui::Begin("NEW RUN", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse)) {
        ImGui::End();
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
    const bool canStart = selected && app.romLibrary().ready(*selected);
    if (!canStart) {
        ImGui::BeginDisabled();
    }
    if (ImGui::Button("START RUN")) {
        app.confirmNewRun();
    }
    if (!canStart) {
        ImGui::EndDisabled();
    }
    ImGui::SameLine();
    if (ImGui::Button("CANCEL")) {
        app.dismissNewRun();
    }
    drawImportSavButton(app, canStart);
    ImGui::End();
}

}
