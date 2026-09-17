#include "ui/Tracker.hpp"

#include "adapter/Species.hpp"
#include "adapter/gen45/Names.hpp"
#include "application/Application.hpp"
#include "poke/SlugLabel.hpp"
#include "poke/SpriteIndex.hpp"
#include "tracker/Log.hpp"
#include "ui/BoxSprites.hpp"

#include <imgui.h>
#include <string>

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
        starter = log.caught("starter").species;
        if (starter == 0) {
            starter = snap.progress.starterSpecies;
        }
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
            ImGui::TextDisabled("Not represented.");
            ImGui::Spacing();
            ImGui::TextWrapped(
                "A title is represented when live party and PC, the tracker atlas, and the calc pack all exist.");
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
    applyTrackerKit(app, *atlas, log);
    const int focusRow = app.kitFocus().trackerRow;
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
                drawEncounterRow(stop, row.status, ref, *sprites, cycle, i == focusRow);
                if (cycle) {
                    log.setStatus(stop.id, nextEncounterStatus(row.status));
                }
            } else {
                const char* slugs[6]{};
                const char* tips[6]{};
                std::string names[6];
                const int raw = bossTeamSlugs(stop, starter, slugs, 6);
                int n = 0;
                for (int s = 0; s < raw; ++s) {
                    const char* slug = slugs[s] ? slugs[s] : "";
                    if (!knownPokemonSlug(slug)) {
                        continue;
                    }
                    slugs[n] = slugs[s];
                    tips[n] = slug;
                    if (const auto id = pokemonId(slug)) {
                        const SpeciesRef named = nationalSpeciesRef(*id);
                        if (named.name && named.name[0] && named.slug &&
                            normalizeSlug(slug) == named.slug) {
                            tips[n] = named.name;
                            ++n;
                            continue;
                        }
                    }
                    names[n] = slugDisplayName(slug);
                    tips[n] = names[n].c_str();
                    ++n;
                }
                bool toggle = false;
                drawBossRow(stop, slugs, tips, n, log.defeated(stop.id), *sprites, toggle, i == focusRow);
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