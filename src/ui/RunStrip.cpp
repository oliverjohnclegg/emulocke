#include "ui/RunStrip.hpp"

#include "application/Application.hpp"
#include "run/Catalog.hpp"
#include "run/NuzlockeRules.hpp"
#include "run/RunLabel.hpp"
#include "run/SavePeek.hpp"
#include "ui/IconAction.hpp"
#include "ui/RunStripDraw.hpp"
#include "ui/KitMark.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <bit>
#include <cstdio>
#include <string>

namespace emulocke {

bool drawRunStrip(Application& app, const Run& run, bool focus) {
    const CatalogTitle* title = catalogByUuid(run.catalogUuid);
    const GameSnapshot& snap = app.savePeek().get(app.runStore(), run);
    ImGui::PushID(run.id.c_str());
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    const float w = ImGui::GetContentRegionAvail().x;
    ImGui::SetNextItemAllowOverlap();
    ImGui::InvisibleButton("load", ImVec2(w, kRunStripH));
    bool load = ImGui::IsItemClicked();
    const ImVec2 mouse = ImGui::GetMousePos();
    const bool hover = ImGui::IsWindowHovered() && mouse.x >= origin.x && mouse.x < origin.x + w &&
        mouse.y >= origin.y && mouse.y < origin.y + kRunStripH;
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->AddRectFilled(origin, ImVec2(origin.x + w, origin.y + kRunStripH),
        kitPlate(hover || focus));
    dl->AddRect(origin, ImVec2(origin.x + w, origin.y + kRunStripH), ImGui::GetColorU32(kBorder));
    kitStroke(origin, ImVec2(origin.x + w, origin.y + kRunStripH), focus);
    drawRunArt(app, title, ImVec2(origin.x + kRunPad, origin.y + kRunPad));
    const ImVec2 text(origin.x + kRunPad * 2.f + kRunArtW, origin.y + kRunPad);
    char heading[48];
    std::snprintf(heading, sizeof heading, "%s - %s", title ? title->title : "POKEMON",
        rulesPresetTitle(run.rules));
    ImGui::SetCursorScreenPos(text);
    if (ImFont* display = app.displayFont()) {
        ImGui::PushFont(display);
    }
    ImGui::TextUnformatted(heading);
    if (app.displayFont()) {
        ImGui::PopFont();
    }
    const std::string clock = formatPlayClock(run.playMs);
    char meta[96];
    if (snap.ok && snap.gyms.slots) {
        std::snprintf(meta, sizeof meta, "%s • Attempt #%d • Deaths: 0 • Badges: %u/%u",
            clock.c_str(), run.attempt, std::popcount(snap.gyms.earned), snap.gyms.slots);
    } else {
        std::snprintf(meta, sizeof meta, "%s • Attempt #%d • Deaths: 0", clock.c_str(), run.attempt);
    }
    ImGui::SetCursorScreenPos(ImVec2(text.x, origin.y + kRunPad + 22.f));
    ImGui::TextDisabled("%s", meta);
    drawRunParty(app, snap.party, ImVec2(text.x, origin.y + kRunPad + 46.f));
    const ImVec2 retry(origin.x + w - kRunPad - kRunPlus, origin.y + kRunPad);
    const ImVec2 trash(retry.x - 4.f - kRunPlus, origin.y + kRunPad);
    ImGui::SetCursorScreenPos(trash);
    ImGui::SetNextItemAllowOverlap();
    if (iconAction("del", "DELETE RUN", ImVec2(kRunPlus, kRunPlus))) {
        app.requestDeleteRun(run.id);
        load = false;
    }
    iconTrash(trash, ImVec2(kRunPlus, kRunPlus));
    ImGui::SetCursorScreenPos(retry);
    if (iconAction("new", "NEW ATTEMPT", ImVec2(kRunPlus, kRunPlus))) {
        app.requestNewAttempt(run.id);
        load = false;
    }
    iconRetry(retry, ImVec2(kRunPlus, kRunPlus));
    ImGui::SetCursorScreenPos(ImVec2(origin.x, origin.y + kRunStripH + 6.f));
    ImGui::Dummy(ImVec2(w, 0.f));
    ImGui::PopID();
    return load;
}

}
