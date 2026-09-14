#include "ui/CalculatorDraw.hpp"

#include "application/Application.hpp"

#include <imgui.h>
#include <cstdio>

namespace emulocke {

void drawCalcSearch(Application&, CalcSession& session) {
    ImGui::SetNextItemWidth(-1.f);
    if (ImGui::InputTextWithHint("##calc-q", "Trainer or location", session.query(), 48)) {
        session.search(session.query());
    }
    if (!session.browsing()) {
        return;
    }
    ImGui::Dummy(ImVec2(0, 6));
    if (!session.locationHits().empty() && session.query()[0]) {
        ImGui::TextDisabled("LOCATIONS");
        const int n = session.locationHits().size() > 8 ? 8 : static_cast<int>(session.locationHits().size());
        for (int i = 0; i < n; ++i) {
            const PackLocation* loc = session.locationHits()[static_cast<std::size_t>(i)];
            if (ImGui::Selectable(loc->name)) {
                session.pickLocation(loc);
            }
        }
        ImGui::Dummy(ImVec2(0, 4));
    }
    if (!session.trainerHits().empty()) {
        ImGui::TextDisabled("TRAINERS");
        const int n = session.trainerHits().size() > 10 ? 8 : static_cast<int>(session.trainerHits().size());
        for (int i = 0; i < n; ++i) {
            const PackTrainer* t = session.trainerHits()[static_cast<std::size_t>(i)];
            char line[96];
            std::snprintf(line, sizeof line, "%s %s", t->cls, t->name);
            const bool sel = session.trainer() == t;
            if (ImGui::Selectable(line, sel)) {
                session.pickTrainer(t);
            }
            ImGui::SameLine();
            ImGui::TextDisabled("%s", t->location);
        }
    }
}

}
