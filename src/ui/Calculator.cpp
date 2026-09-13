#include "ui/Calculator.hpp"

#include "application/Application.hpp"
#include "calc/Session.hpp"
#include "run/Catalog.hpp"
#include "ui/CalculatorDraw.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>

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
    return run ? std::string_view(run->patchOption) : std::string_view{};
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
        ImGui::TextWrapped("Need every trainer battle plus that game's stat, type, ability, and move tables.");
        if (app.bodyFont()) {
            ImGui::PopFont();
        }
        return;
    }
    drawCalcSearch(app, session);
    if (session.trainer()) {
        drawCalcStrips(app, session);
        drawCalcMatchup(app, session);
    }
    if (app.bodyFont()) {
        ImGui::PopFont();
    }
}

}
