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

}  // namespace

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
            if (!loc->name[0]) {
                continue;
            }
            ImGui::PushID(loc);
            if (ImGui::Selectable(loc->name)) {
                session.pickLocation(loc);
            }
            ImGui::PopID();
        }
        ImGui::Dummy(ImVec2(0, 4));
    }
    if (!session.trainerHits().empty()) {
        ImGui::TextDisabled("TRAINERS");
        const auto& hits = session.trainerHits();
        const int shown = hits.size() > 10 ? 8 : static_cast<int>(hits.size());
        for (int i = 0; i < shown; ++i) {
            const PackTrainer* t = hits[static_cast<std::size_t>(i)];
            const int ordinal = captionOrdinal(hits, shown, i);
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
            if (ImGui::Selectable(line, session.trainer() == t)) {
                session.pickTrainer(t);
            }
            ImGui::PopID();
        }
    }
}

}
