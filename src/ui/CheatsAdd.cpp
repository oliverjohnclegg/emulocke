#include "ui/Cheats.hpp"

#include "application/Application.hpp"
#include "cheats/Limits.hpp"

#include <imgui.h>
#include <string>

namespace emulocke {
namespace {

char nameBuf[kMaxCheatName + 1];
char codeBuf[kMaxCheatCode + 1];
std::string seatedId;

void resetDraft(const std::string& id) {
    if (seatedId == id) {
        return;
    }
    seatedId = id;
    nameBuf[0] = 0;
    codeBuf[0] = 0;
}

}  // namespace

void drawCheatsAdd(Application& app) {
    resetDraft(app.activeRunId());
    ImGui::TextUnformatted("NAME");
    ImGui::SetNextItemWidth(-1.f);
    ImGui::InputTextWithHint("##cheat-name", "Walk Through Walls", nameBuf, sizeof nameBuf);
    ImGui::TextUnformatted("CODE");
    ImGui::SetNextItemWidth(-1.f);
    ImGui::InputTextMultiline("##cheat-code", codeBuf, sizeof codeBuf, ImVec2(-1.f, 72.f));
    if (ImGui::Button("Add", ImVec2(-1.f, 0.f))) {
        if (app.addCheat(nameBuf, codeBuf) && app.cheatError().empty()) {
            nameBuf[0] = 0;
            codeBuf[0] = 0;
        }
    }
    if (!app.cheatError().empty()) {
        ImGui::TextDisabled("%s", app.cheatError().c_str());
    }
}

}
