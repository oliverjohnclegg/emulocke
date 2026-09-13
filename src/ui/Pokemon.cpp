#include "ui/Pokemon.hpp"

#include "application/Application.hpp"
#include "poke/Dex.hpp"
#include "poke/SpriteIndex.hpp"
#include "tracker/Log.hpp"
#include "ui/BoxSprites.hpp"
#include "ui/PokemonDraw.hpp"

#include <algorithm>
#include <imgui.h>
#include <vector>

namespace emulocke {
namespace {

bool living(const Mon& mon, const TrackerLog& log) {
    return mon.species != 0 && !mon.egg && !log.markedDead(mon.personality);
}

MonView viewOf(Application& app, const Mon& mon, bool gen3) {
    MonView view;
    view.mon = &mon;
    view.ref = app.species(mon.species);
    view.gen3 = gen3;
    if (view.ref.national) {
        view.national = view.ref.national;
    } else if (!gen3) {
        view.national = mon.species;
    } else if (const auto id = pokemonId(speciesSlug(mon.speciesName))) {
        view.national = *id;
    }
    view.ref.national = view.national;
    view.bst = speciesBst(view.national);
    return view;
}

}  // namespace

void drawPokemon(Application& app) {
    if (app.bodyFont()) {
        ImGui::PushFont(app.bodyFont());
    }
    ImGui::Dummy(ImVec2(0, 8));
    GameSnapshot snap;
    if (!app.copySnapshot(snap)) {
        ImGui::TextDisabled("No supported cart seated.");
        ImGui::Spacing();
        ImGui::TextWrapped("Party and box sprites list here once a supported cart is running.");
        if (app.bodyFont()) {
            ImGui::PopFont();
        }
        return;
    }
    app.syncTracker(snap);
    BoxSprites* sprites = app.boxSprites();
    if (!sprites) {
        if (app.bodyFont()) {
            ImGui::PopFont();
        }
        return;
    }
    sprites->beginFrame();
    const bool gen3 = gen3Adapter(snap.adapterId);
    TrackerLog& log = app.trackerLog();
    MonView party[6]{};
    for (int i = 0; i < 6; ++i) {
        const Mon& mon = snap.party.mons[static_cast<std::size_t>(i)];
        if (living(mon, log)) {
            party[i] = viewOf(app, mon, gen3);
        }
    }
    std::vector<MonView> boxed;
    for (const PcBox& box : snap.boxes.boxes) {
        for (const Mon& mon : box.mons) {
            if (living(mon, log)) {
                boxed.push_back(viewOf(app, mon, gen3));
            }
        }
    }
    std::stable_sort(boxed.begin(), boxed.end(), [](const MonView& a, const MonView& b) {
        return a.bst > b.bst;
    });
    if (const char* notice = pokeCopyNotice()) {
        ImGui::TextDisabled("%s", notice);
    }
    ImGui::TextUnformatted("PARTY");
    ImGui::Separator();
    drawPartyStrip(*sprites, party, 6);
    ImGui::Dummy(ImVec2(0, 12));
    ImGui::TextUnformatted("BOX");
    ImGui::Separator();
    if (boxed.empty()) {
        ImGui::TextDisabled("No boxed Pokemon.");
    } else {
        drawBoxGrid(*sprites, boxed.data(), static_cast<int>(boxed.size()));
    }
    if (app.bodyFont()) {
        ImGui::PopFont();
    }
}

}  // namespace emulocke
