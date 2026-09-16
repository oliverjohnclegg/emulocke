#include "ui/Tracker.hpp"

#include "application/Application.hpp"
#include "tracker/Snap.hpp"
#include "ui/KitNav.hpp"

#include <imgui.h>

namespace emulocke {

void applyTrackerKit(Application& app, const TrackerAtlas& atlas, TrackerLog& log) {
    KitFocus& focus = app.kitFocus();
    const int n = static_cast<int>(atlas.stops.size());
    if (!kitNavSuite(app, KitTab::Tracker)) {
        kitMove(focus.trackerRow, n, false, false);
        return;
    }
    const KitFrame& kit = app.kit();
    const int was = focus.trackerRow;
    if (kit.snap) {
        GameSnapshot snap;
        const char* map = "";
        if (app.copySnapshot(snap) && snap.overworld.mapName[0]) {
            map = snap.overworld.mapName;
        }
        const int row = snapTrackerRow(atlas, log, map);
        if (row >= 0) {
            focus.trackerRow = row;
        }
    }
    kitMove(focus.trackerRow, n, kit.up || kit.left, kit.down || kit.right);
    if (kit.act && focus.trackerRow >= 0 && focus.trackerRow < n) {
        const TrackerStop& stop = atlas.stops[static_cast<std::size_t>(focus.trackerRow)];
        if (stop.kind == TrackerStopKind::Encounter) {
            log.setStatus(stop.id, nextEncounterStatus(log.caught(stop.id).status));
        } else {
            log.setDefeated(stop.id, !log.defeated(stop.id));
        }
    }
    if (focus.trackerRow != was) {
        ImGui::SetScrollY(static_cast<float>(focus.trackerRow) * kTrackerRowH);
    }
}

}
