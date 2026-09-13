#include "ui/RunStrip.hpp"

#include "application/Application.hpp"
#include "run/Catalog.hpp"
#include "run/NuzlockeRules.hpp"
#include "run/SavePeek.hpp"
#include "ui/IconAction.hpp"
#include "ui/RunStripDraw.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <cstdio>
#include <string>

namespace emulocke {

bool drawRunStrip(Application& app, const Run& run, const char* idPrefix, bool showNewAttempt) {
    const CatalogTitle* title = catalogByUuid(run.catalogUuid);
    const GameSnapshot& snap = app.savePeek().get(app.runStore(), run);
    ImGui::PushID((std::string(idPrefix) + run.id).c_str());
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
        ImGui::GetColorU32(hover ? kHeaderHover : kButton));
    dl->AddRect(origin, ImVec2(origin.x + w, origin.y + kRunStripH), ImGui::GetColorU32(kBorder));
    drawRunArt(app, title, ImVec2(origin.x + kRunPad, origin.y + kRunPad));
    ImGui::SetCursorScreenPos(ImVec2(origin.x + kRunPad * 2.f + kRunArtW, origin.y + kRunPad));
    if (ImFont* display = app.displayFont()) {
        ImGui::PushFont(display);
    }
    ImGui::TextUnformatted(title ? title->title : "POKEMON");
    if (app.displayFont()) {
        ImGui::PopFont();
    }
    ImGui::SameLine(0.f, 12.f);
    ImGui::TextDisabled("%s", rulesLabel(run.rules));
    ImGui::SameLine(0.f, 10.f);
    ImGui::TextDisabled("ATTEMPT %d", run.attempt);
    ImVec2 pipPos{};
    bool pips = false;
    if (snap.ok) {
        char clock[12];
        std::snprintf(clock, sizeof clock, "%03u:%02u", snap.trainer.playHours, snap.trainer.playMinutes);
        ImGui::SameLine(0.f, 10.f);
        ImGui::TextDisabled("%s", clock);
        if (snap.gyms.slots) {
            ImGui::SameLine(0.f, 10.f);
            pipPos = ImGui::GetCursorScreenPos();
            pipPos.y += 6.f;
            drawRunBadges(snap.gyms, pipPos);
            pips = true;
        }
    }
    drawRunParty(app, snap.party, ImVec2(origin.x + kRunPad * 2.f + kRunArtW, origin.y + kRunPad + 40.f));
    if (showNewAttempt) {
        const ImVec2 plus(origin.x + w - kRunPad - kRunPlus, origin.y + kRunPad);
        ImGui::SetCursorScreenPos(plus);
        if (iconAction("new", "NEW ATTEMPT", ImVec2(kRunPlus, kRunPlus))) {
            app.queueNewAttempt(run.id);
            load = false;
        }
        iconPlus(plus, ImVec2(kRunPlus, kRunPlus));
    }
    if (pips) {
        hitRunBadges(snap.gyms, pipPos);
    }
    ImGui::SetCursorScreenPos(ImVec2(origin.x, origin.y + kRunStripH + 6.f));
    ImGui::Dummy(ImVec2(w, 0.f));
    ImGui::PopID();
    return load;
}

}
