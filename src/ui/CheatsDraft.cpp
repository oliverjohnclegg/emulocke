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

bool takeCheatDraft(Application& app) {
    resetDraft(app.activeRunId());
    if (!app.addCheat(nameBuf, codeBuf) || !app.cheatError().empty()) {
        return false;
    }
    nameBuf[0] = 0;
    codeBuf[0] = 0;
    return true;
}

void drawCheatDraft(Application& app) {
    resetDraft(app.activeRunId());
    if (ImGui::IsWindowAppearing()) {
        ImGui::SetKeyboardFocusHere();
    }
    ImGui::TextUnformatted("NAME");
    ImGui::SetNextItemWidth(-1.f);
    ImGui::InputTextWithHint("##cheat-name", "Walk Through Walls", nameBuf, sizeof nameBuf);
    ImGui::Dummy(ImVec2(0, 6));
    ImGui::TextUnformatted("CODE");
    ImGui::SetNextItemWidth(-1.f);
    ImGui::InputTextMultiline("##cheat-code", codeBuf, sizeof codeBuf, ImVec2(-1.f, 96.f));
    if (!app.cheatError().empty()) {
        ImGui::Dummy(ImVec2(0, 6));
        ImGui::TextDisabled("%s", app.cheatError().c_str());
    }
}

}
