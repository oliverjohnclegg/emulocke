#include "ui/Pokemon.hpp"

#include "application/Application.hpp"
#include "poke/Dex.hpp"
#include "ui/BoxSprites.hpp"
#include "ui/KitNav.hpp"
#include "ui/PokemonDraw.hpp"
#include "ui/PokemonGather.hpp"

#include <imgui.h>
#include <vector>

namespace emulocke {

void drawPokemon(Application& app) {
    if (app.bodyFont()) {
        ImGui::PushFont(app.bodyFont());
    }
    ImGui::Dummy(ImVec2(0, 8));
    GameSnapshot snap;
    if (!app.copySnapshot(snap)) {
        ImGui::TextDisabled("No supported cart seated.");
        ImGui::Spacing();
        ImGui::TextWrapped("Party, box, and grave sprites list here once a supported cart is running.");
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
    MonView party[6]{};
    std::vector<MonView> boxed;
    std::vector<MonView> grave;
    gatherPokemon(app, snap, app.trackerLog(), gen3, party, boxed, grave);
    const int total = 6 + static_cast<int>(boxed.size()) + static_cast<int>(grave.size());
    KitFocus& focus = app.kitFocus();
    const bool nav = kitNavSuite(app, KitTab::Pokemon);
    if (nav) {
        const KitFrame& kit = app.kit();
        if (kit.snap) {
            focus.pokemonWell = 0;
        }
        kitMove(focus.pokemonWell, total, kit.up || kit.left, kit.down || kit.right);
    }
    const bool act = nav && app.kit().act;
    const int well = focus.pokemonWell;
    ImGui::TextUnformatted("PARTY");
    ImGui::Separator();
    drawPartyStrip(*sprites, party, 6, well, act);
    ImGui::Dummy(ImVec2(0, 12));
    const float each = (ImGui::GetContentRegionAvail().y - ImGui::GetStyle().ItemSpacing.y) * 0.5f;
    ImGui::BeginChild("box-roster", ImVec2(0.f, each), ImGuiChildFlags_None);
    drawRosterPane(*sprites, boxed.data(), static_cast<int>(boxed.size()), "BOX", "No boxed Pokemon.", 6, well,
        act);
    ImGui::EndChild();
    ImGui::BeginChild("grave-roster", ImVec2(0.f, each), ImGuiChildFlags_None);
    drawRosterPane(*sprites, grave.data(), static_cast<int>(grave.size()), "GRAVE", "No fallen Pokemon.",
        6 + static_cast<int>(boxed.size()), well, act);
    ImGui::EndChild();
    if (app.bodyFont()) {
        ImGui::PopFont();
    }
}

}
