#include "ui/FieldLog.hpp"

#include "adapter/Snapshot.hpp"
#include "application/Application.hpp"

#include <bit>
#include <imgui.h>
#include <cstdio>

namespace emulocke {
namespace {

void logLine(const char* key, const char* value) {
    ImGui::TextDisabled("%-5s", key);
    ImGui::SameLine();
    ImGui::TextUnformatted(value);
}

void drawParty(const GameSnapshot& snap) {
    ImGui::Dummy(ImVec2(0, 10));
    ImGui::TextUnformatted("PARTY");
    ImGui::Separator();
    for (int i = 0; i < 6; ++i) {
        const Mon& mon = snap.party.mons[static_cast<std::size_t>(i)];
        if (mon.species == 0) {
            ImGui::TextDisabled("  %d  --", i + 1);
            continue;
        }
        const char* name = mon.speciesName[0] ? mon.speciesName : "--";
        ImGui::Text("  %d  %-11s  Lv%02u  %03u/%03u", i + 1, name, mon.level, mon.hp, mon.maxHp);
    }
}

}  // namespace

void drawFieldLog(Application& app) {
    if (app.bodyFont()) {
        ImGui::PushFont(app.bodyFont());
    }
    ImGui::Dummy(ImVec2(0, 8));
    GameSnapshot snap;
    if (app.copySnapshot(snap)) {
        char cart[32];
        std::snprintf(cart, sizeof(cart), "%s", snap.adapterId.data());
        logLine("CART", cart);
        char ot[48];
        const char* otName = (snap.trainer.name[0] && snap.trainer.name[0] != ' ') ? snap.trainer.name : "--";
        std::snprintf(ot, sizeof(ot), "%s  %05u", otName, static_cast<unsigned>(snap.trainer.trainerId & 0xFFFFu));
        logLine("OT", ot);
        logLine("MAP", snap.overworld.mapName[0] ? snap.overworld.mapName : "--");
        if (snap.gyms.slots) {
            char badges[16];
            std::snprintf(badges, sizeof badges, "%u/%u", std::popcount(snap.gyms.earned), snap.gyms.slots);
            logLine("BADGES", badges);
        }
        drawParty(snap);
    } else {
        ImGui::TextDisabled("%s", app.status().empty() ? "No supported cart seated." : app.status().c_str());
        ImGui::Spacing();
        ImGui::TextWrapped("Supported carts write trainer, party, and boxes here.");
    }
    if (app.bodyFont()) {
        ImGui::PopFont();
    }
}

}
