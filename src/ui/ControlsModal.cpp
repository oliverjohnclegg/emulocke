#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "emu/KeyMap.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <SDL3/SDL.h>

namespace emulocke {
namespace {

int listening = -1;
bool waitRelease = false;

bool plate(const char* id, const char* label, ImVec2 size, bool armed) {
    const ImVec2 p = ImGui::GetCursorScreenPos();
    ImGui::InvisibleButton(id, size);
    const bool hovered = ImGui::IsItemHovered();
    const bool clicked = ImGui::IsItemClicked();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImVec2 q(p.x + size.x, p.y + size.y);
    dl->AddRectFilled(p, q, ImGui::GetColorU32(armed ? kHeaderActive : hovered ? kHeaderHover : kButton));
    dl->AddRect(p, q, ImGui::GetColorU32(kBorder));
    const ImVec2 ts = ImGui::CalcTextSize(label);
    dl->AddText(ImVec2(p.x + (size.x - ts.x) * 0.5f, p.y + (size.y - ts.y) * 0.5f),
        ImGui::GetColorU32(kMetal), label);
    return clicked;
}

void captureListen(Application& app) {
    if (listening < 0) {
        return;
    }
    const bool* keys = SDL_GetKeyboardState(nullptr);
    bool down = false;
    SDL_Scancode pressed = SDL_SCANCODE_UNKNOWN;
    for (int i = 0; i < SDL_SCANCODE_COUNT; ++i) {
        if (!keys[i]) {
            continue;
        }
        down = true;
        if (pressed == SDL_SCANCODE_UNKNOWN) {
            pressed = static_cast<SDL_Scancode>(i);
        }
    }
    if (waitRelease) {
        waitRelease = down;
        return;
    }
    if (!down) {
        return;
    }
    if (pressed == SDL_SCANCODE_ESCAPE) {
        listening = -1;
        return;
    }
    KeyMap map = app.prefs().keys;
    if (bindKey(map, listening, pressed)) {
        app.setKeys(map);
        listening = -1;
    }
}

}  // namespace

bool controlsCapturing() {
    return listening >= 0;
}

void drawControlsModal(Application& app) {
    if (!ImGui::IsPopupOpen("Controls")) {
        listening = -1;
        waitRelease = false;
        return;
    }
    const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(14.f, 14.f));
    ImGui::PushStyleColor(ImGuiCol_PopupBg, kPanel);
    const ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNav;
    if (!ImGui::BeginPopupModal("Controls", nullptr, flags)) {
        ImGui::PopStyleColor();
        ImGui::PopStyleVar();
        return;
    }
    const float plateW = 320.f;
    ImGui::Dummy(ImVec2(plateW, 0));
    if (app.displayFont()) {
        ImGui::PushFont(app.displayFont());
    }
    ImGui::TextUnformatted("CONTROLS");
    if (app.displayFont()) {
        ImGui::PopFont();
    }
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 8));
    ImGui::TextDisabled("D-PAD");
    const KeyMap& keys = app.prefs().keys;
    for (int i = 0; i < kKeySlotCount; ++i) {
        if (i == static_cast<int>(KeySlot::B)) {
            ImGui::Dummy(ImVec2(0, 4));
        }
        ImGui::TextUnformatted(keySlotLabel(i));
        ImGui::SameLine(plateW - 108.f);
        ImGui::PushID(i);
        const bool armed = listening == i;
        if (plate("key", armed ? "PRESS" : scancodeLabel(keys.codes[i]), ImVec2(108.f, 24.f), armed)) {
            listening = armed ? -1 : i;
            waitRelease = !armed;
        }
        ImGui::PopID();
    }
    ImGui::Dummy(ImVec2(0, 8));
    ImGui::TextDisabled("Stylus          Mouse on bottom screen");
    ImGui::TextDisabled("Speed-up        %s", app.prefs().speedUpHold ? "Hold Tab" : "Tab");
    ImGui::TextDisabled("Pause           Esc");
    ImGui::TextDisabled("Right pane      ` / F8");
    ImGui::Dummy(ImVec2(0, 6));
    ImGui::TextDisabled("SUITE");
    ImGui::TextDisabled("Tabs            1 2 3 4 5");
    ImGui::TextDisabled("Move            R V D G");
    ImGui::TextDisabled("Act             F");
    ImGui::TextDisabled("Snap            E");
    ImGui::TextDisabled("Search          T");
    ImGui::TextDisabled("Delete          Backspace");
    ImGui::Dummy(ImVec2(0, 12));
    const ImVec2 btn((plateW - 5.f) * 0.5f, 28.f);
    if (plate("defaults", "RESTORE DEFAULTS", btn, false)) {
        app.setKeys(KeyMap{});
        listening = -1;
    }
    ImGui::SameLine(0.f, 5.f);
    if (plate("close", "CLOSE", btn, false) || app.kit().pause) {
        listening = -1;
        ImGui::CloseCurrentPopup();
    }
    captureListen(app);
    ImGui::EndPopup();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}

}
