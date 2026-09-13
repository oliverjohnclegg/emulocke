#include "ui/Tracker.hpp"

#include "adapter/GameAdapter.hpp"
#include "adapter/Species.hpp"
#include "application/Application.hpp"
#include "tracker/Log.hpp"
#include "ui/BoxSprites.hpp"

#include <imgui.h>
#include <cstdio>
#include <cstring>

namespace emulocke {
namespace {

int gEdit = -1;
int gFocus = -1;
char gEditBuf[24];

}  // namespace

void drawTracker(Application& app) {
    if (app.bodyFont()) {
        ImGui::PushFont(app.bodyFont());
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
    GameSnapshot snap;
    uint16_t starter = 0;
    TrackerLog& log = app.trackerLog();
    if (app.copySnapshot(snap)) {
        app.syncTracker(snap);
        starter = snap.progress.starterSpecies;
    } else if (app.previewTracker()) {
        starter = log.caught("starter").species;
    }
    if (gEdit >= static_cast<int>(atlas->stops.size())) {
        gEdit = -1;
        gFocus = -1;
    }
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
                bool commit = false;
                bool startEdit = false;
                const bool editing = gEdit == i;
                drawEncounterRow(stop, ref, *sprites, editing, gFocus == i, gEditBuf,
                                 static_cast<int>(sizeof(gEditBuf)), commit, startEdit);
                if (gFocus == i) {
                    gFocus = -1;
                }
                if (startEdit) {
                    gEdit = i;
                    gFocus = i;
                    gEditBuf[0] = 0;
                    if (ref.name) {
                        std::snprintf(gEditBuf, sizeof(gEditBuf), "%s", ref.name);
                    }
                }
                if (commit) {
                    if (const GameAdapter* adapter = app.adapter()) {
                        const uint16_t id = matchSpeciesName(*adapter, gEditBuf);
                        if (id != 0) {
                            log.setCaught(stop.id, id, 0);
                        }
                    }
                    gEdit = -1;
                    gFocus = -1;
                    gEditBuf[0] = 0;
                }
            } else {
                bool toggle = false;
                drawBossRow(stop, starter, log.defeated(stop.id), *sprites, toggle);
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
