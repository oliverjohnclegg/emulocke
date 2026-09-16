#include "ui/CalculatorDraw.hpp"

#include "application/Application.hpp"

#include <imgui.h>
#include <cstdio>

namespace emulocke {
namespace {

int locCap(const CalcSession& session) {
    const int n = static_cast<int>(session.locationHits().size());
    return n > 8 ? 8 : n;
}

int trainerCap(const CalcSession& session) {
    const int n = static_cast<int>(session.trainerHits().size());
    return n > 10 ? 8 : n;
}

void pickHit(CalcSession& session, int hit) {
    const int loc = locCap(session);
    if (hit < loc) {
        session.pickLocation(session.locationHits()[static_cast<std::size_t>(hit)]);
    } else if (hit - loc < trainerCap(session)) {
        session.pickTrainer(session.trainerHits()[static_cast<std::size_t>(hit - loc)]);
    }
}

}  // namespace

void drawCalcSearch(Application& app, CalcSession& session) {
    if (app.kitFocus().focusSearch) {
        ImGui::SetKeyboardFocusHere();
        app.kitFocus().focusSearch = false;
    }
    ImGui::SetNextItemWidth(-1.f);
    const bool enter = ImGui::InputTextWithHint("##calc-q", "Trainer or location", session.query(), 48,
        ImGuiInputTextFlags_EnterReturnsTrue);
    if (ImGui::IsItemEdited() || enter) {
        session.search(session.query());
    }
    if (enter && session.browsing()) {
        pickHit(session, app.kitFocus().searchHit);
    }
    if (!session.browsing()) {
        return;
    }
    ImGui::Dummy(ImVec2(0, 6));
    int hit = 0;
    if (!session.locationHits().empty() && session.query()[0]) {
        ImGui::TextDisabled("LOCATIONS");
        const int n = locCap(session);
        for (int i = 0; i < n; ++i, ++hit) {
            const PackLocation* loc = session.locationHits()[static_cast<std::size_t>(i)];
            if (ImGui::Selectable(loc->name, hit == app.kitFocus().searchHit)) {
                session.pickLocation(loc);
            }
        }
        ImGui::Dummy(ImVec2(0, 4));
    }
    if (!session.trainerHits().empty()) {
        ImGui::TextDisabled("TRAINERS");
        const int n = trainerCap(session);
        for (int i = 0; i < n; ++i, ++hit) {
            const PackTrainer* t = session.trainerHits()[static_cast<std::size_t>(i)];
            char line[96];
            std::snprintf(line, sizeof line, "%s %s", t->cls, t->name);
            if (ImGui::Selectable(line, t == session.trainer() || hit == app.kitFocus().searchHit)) {
                session.pickTrainer(t);
            }
            ImGui::SameLine();
            ImGui::TextDisabled("%s", t->location);
        }
    }
}

}
