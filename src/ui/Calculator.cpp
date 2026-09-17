#include "ui/Calculator.hpp"

#include "application/Application.hpp"
#include "calc/Session.hpp"
#include "run/Catalog.hpp"
#include "ui/CalculatorDraw.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <string_view>

namespace emulocke {
namespace {

const char* seatedUuid(Application& app) {
    if (app.previewCalc()) {
        return kFireRedUs10Uuid;
    }
    const Run* run = app.runStore().find(app.activeRunId());
    return run ? run->catalogUuid.c_str() : "";
}

std::string_view seatedVariant(Application& app) {
    if (app.previewCalc()) {
        return {};
    }
    const Run* run = app.runStore().find(app.activeRunId());
    return run ? std::string_view(run->difficulty) : std::string_view{};
}

}  // namespace

void drawCalculator(Application& app) {
    if (app.bodyFont()) {
        ImGui::PushFont(app.bodyFont());
    }
    GameSnapshot snap;
    const GameSnapshot* live = app.copySnapshot(snap) ? &snap : nullptr;
    app.calc().sync(seatedUuid(app), seatedVariant(app), live);
    CalcSession& session = app.calc();
    ImGui::Dummy(ImVec2(0, 8));
    if (!session.pack()) {
        ImGui::TextDisabled("Not represented.");
        ImGui::Spacing();
        ImGui::TextWrapped(
            "A title is represented when live party and PC, the tracker atlas, and the calc pack all exist.");
        if (app.bodyFont()) {
            ImGui::PopFont();
        }
        return;
    }
    applyCalculatorKit(app, session);
    drawCalcSearch(app, session);
    if (session.trainer() && !session.browsing()) {
        const PackTrainer* t = session.trainer();
        ImGui::Dummy(ImVec2(0, 6));
        ImGui::TextUnformatted(t->name);
        ImGui::SameLine();
        ImGui::TextDisabled("%s  %s", t->cls, t->location);
        ImGui::Dummy(ImVec2(0, 6));
        if (ImGui::BeginTable("calc-board", 3, ImGuiTableFlags_NoPadInnerX)) {
            ImGui::TableSetupColumn("p", ImGuiTableColumnFlags_WidthFixed, 40.f);
            ImGui::TableSetupColumn("m", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("f", ImGuiTableColumnFlags_WidthFixed, 56.f);
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            drawCalcPartyRail(app, session);
            ImGui::TableSetColumnIndex(1);
            drawCalcMatchup(app, session);
            ImGui::TableSetColumnIndex(2);
            drawCalcFoeRail(app, session);
            ImGui::EndTable();
        }
        ImGui::Separator();
        drawCalcField(app, session);
    }
    if (app.bodyFont()) {
        ImGui::PopFont();
    }
}

}