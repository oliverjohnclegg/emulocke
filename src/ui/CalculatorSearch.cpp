#include "ui/CalculatorDraw.hpp"

#include "application/Application.hpp"

#include <imgui.h>
#include <cstdio>
#include <cstring>
#include <vector>

namespace emulocke {
namespace {

bool sameTrainerCaption(const PackTrainer& a, const PackTrainer& b) {
    return std::strcmp(a.cls, b.cls) == 0 && std::strcmp(a.name, b.name) == 0 &&
           std::strcmp(a.location, b.location) == 0;
}

int captionOrdinal(const std::vector<const PackTrainer*>& hits, int shown, int i) {
    const PackTrainer& t = *hits[static_cast<std::size_t>(i)];
    int same = 0;
    int ordinal = 0;
    for (int j = 0; j < shown; ++j) {
        if (!sameTrainerCaption(t, *hits[static_cast<std::size_t>(j)])) {
            continue;
        }
        ++same;
        if (j <= i) {
            ++ordinal;
        }
    }
    return same > 1 ? ordinal : 0;
}

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
            ImGui::PushID(loc);
            if (ImGui::Selectable(loc->name, hit == app.kitFocus().searchHit)) {
                session.pickLocation(loc);
            }
            ImGui::PopID();
        }
        ImGui::Dummy(ImVec2(0, 4));
    }
    if (!session.trainerHits().empty()) {
        ImGui::TextDisabled("TRAINERS");
        const auto& hits = session.trainerHits();
        const int n = trainerCap(session);
        for (int i = 0; i < n; ++i, ++hit) {
            const PackTrainer* t = hits[static_cast<std::size_t>(i)];
            const int ordinal = captionOrdinal(hits, n, i);
            char line[112];
            if (t->location[0] && ordinal > 0) {
                std::snprintf(line, sizeof line, "%s %s (%s) #%d", t->cls, t->name, t->location, ordinal);
            } else if (t->location[0]) {
                std::snprintf(line, sizeof line, "%s %s (%s)", t->cls, t->name, t->location);
            } else if (ordinal > 0) {
                std::snprintf(line, sizeof line, "%s %s #%d", t->cls, t->name, ordinal);
            } else {
                std::snprintf(line, sizeof line, "%s %s", t->cls, t->name);
            }
            ImGui::PushID(t);
            if (ImGui::Selectable(line, t == session.trainer() || hit == app.kitFocus().searchHit)) {
                session.pickTrainer(t);
            }
            ImGui::PopID();
        }
    }
}

}
