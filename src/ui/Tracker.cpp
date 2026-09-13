#include "ui/Tracker.hpp"

#include "adapter/Species.hpp"
#include "application/Application.hpp"
#include "poke/SpriteIndex.hpp"
#include "tracker/Log.hpp"
#include "ui/BoxSprites.hpp"

#include <imgui.h>

namespace emulocke {

void drawTracker(Application& app) {
    if (app.bodyFont()) {
        ImGui::PushFont(app.bodyFont());
    }
    GameSnapshot snap;
    uint16_t starter = 0;
    TrackerLog& log = app.trackerLog();
    if (app.copySnapshot(snap)) {
        app.syncTracker(snap);
        starter = snap.progress.starterSpecies;
    } else if (app.previewTracker()) {
        starter = log.caught("starter").species;
    }
    if (starter == 0) {
        starter = log.caught("starter").species;
    }
    const TrackerAtlas* atlas = app.trackerAtlas();
    if (!atlas || atlas->stops.empty()) {
        ImGui::Dummy(ImVec2(0, 8));
        if (app.activeRunId().empty()) {
            ImGui::TextDisabled("No cart seated.");
            ImGui::Spacing();
            ImGui::TextWrapped("Encounter routes and bosses list here once a represented title is running.");
        } else {
            ImGui::TextDisabled("No tracker plate for this title.");
            ImGui::Spacing();
            ImGui::TextWrapped(
                "A title is represented when its route order, catch keys, and boss teams are documented.");
        }
        if (app.bodyFont()) {
            ImGui::PopFont();
        }
        return;
    }
    BoxSprites* sprites = app.boxSprites();
    if (!sprites) {
        if (app.bodyFont()) {
            ImGui::PopFont();
        }
        return;
    }
    sprites->beginFrame();
    ImGuiListClipper clipper;
    clipper.Begin(static_cast<int>(atlas->stops.size()), kTrackerRowH);
    while (clipper.Step()) {
        for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i) {
            const TrackerStop& stop = atlas->stops[static_cast<std::size_t>(i)];
            ImGui::PushID(i);
            if (stop.kind == TrackerStopKind::Encounter) {
                const Caught row = log.caught(stop.id);
                SpeciesRef ref;
                if (row.species != 0) {
                    ref = app.species(row.species);
                }
                bool cycle = false;
                drawEncounterRow(stop, row.status, ref, *sprites, cycle);
                if (cycle) {
                    log.setStatus(stop.id, nextEncounterStatus(row.status));
                }
            } else {
                const char* slugs[6]{};
                const char* tips[6]{};
                const int n = bossTeamSlugs(stop, starter, slugs, 6);
                for (int s = 0; s < n; ++s) {
                    tips[s] = slugs[s] ? slugs[s] : "";
                    if (const auto id = pokemonId(slugs[s] ? slugs[s] : "")) {
                        const SpeciesRef named = app.species(*id);
                        if (named.name && named.name[0]) {
                            tips[s] = named.name;
                        }
                    }
                }
                bool toggle = false;
                drawBossRow(stop, slugs, tips, n, log.defeated(stop.id), *sprites, toggle);
                if (toggle) {
                    log.setDefeated(stop.id, !log.defeated(stop.id));
                }
            }
            ImGui::PopID();
        }
    }
    if (log.dirty()) {
        app.persistTracker();
    }
    if (app.bodyFont()) {
        ImGui::PopFont();
    }
}

}