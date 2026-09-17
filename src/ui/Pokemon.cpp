#include "ui/Pokemon.hpp"

#include "application/Application.hpp"
#include "poke/Dex.hpp"
#include "ui/BoxSprites.hpp"
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
    if (!app.trackerAtlas()) {
        ImGui::TextDisabled("Not represented.");
        ImGui::Spacing();
        ImGui::TextWrapped(
            "A title is represented when live party and PC, the tracker atlas, and the calc pack all exist.");
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
    std::vector<Mon> graveOwned;
    gatherPokemon(app, snap, app.trackerLog(), gen3, party, boxed, grave, graveOwned);
    if (const char* notice = pokeCopyNotice()) {
        ImGui::TextDisabled("%s", notice);
    }
    ImGui::TextUnformatted("PARTY");
    ImGui::Separator();
    drawPartyStrip(*sprites, party, 6);
    ImGui::Dummy(ImVec2(0, 12));
    const float each = (ImGui::GetContentRegionAvail().y - ImGui::GetStyle().ItemSpacing.y) * 0.5f;
    ImGui::BeginChild("box-roster", ImVec2(0.f, each), ImGuiChildFlags_None);
    drawRosterPane(*sprites, boxed.data(), static_cast<int>(boxed.size()), "BOX", "No boxed Pokemon.", 1000);
    ImGui::EndChild();
    ImGui::BeginChild("grave-roster", ImVec2(0.f, each), ImGuiChildFlags_None);
    drawRosterPane(*sprites, grave.data(), static_cast<int>(grave.size()), "GRAVE", "No fallen Pokemon.", 2000);
    ImGui::EndChild();
    if (app.bodyFont()) {
        ImGui::PopFont();
    }
}

}