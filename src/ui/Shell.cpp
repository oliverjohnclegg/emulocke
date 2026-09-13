#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "emu/EmuSession.hpp"
#include "ui/GbaPartyScreen.hpp"
#include "ui/Layout.hpp"
#include "ui/Suite.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <algorithm>

namespace emulocke {

namespace {

void drawScreen(const char* id, ScreenTexture& tex, ImVec2 size, bool paused, bool touch, Application& app) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, kScreenWell);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    ImGui::BeginChild(id, size, ImGuiChildFlags_Borders, ImGuiWindowFlags_NoScrollbar);
    if (tex.texture()) {
        ImDrawList* dl = ImGui::GetWindowDrawList();
        ImGuiPlatformIO& pio = ImGui::GetPlatformIO();
        if (pio.DrawCallback_SetSamplerNearest) {
            dl->AddCallback(pio.DrawCallback_SetSamplerNearest, nullptr);
        }
        ImGui::Image(tex.texture(), ImGui::GetContentRegionAvail());
        if (pio.DrawCallback_SetSamplerLinear) {
            dl->AddCallback(pio.DrawCallback_SetSamplerLinear, nullptr);
        }
        if (touch) {
            const ImVec2 rmin = ImGui::GetItemRectMin();
            const ImVec2 rsize = ImGui::GetItemRectSize();
            if (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
                const ImVec2 mouse = ImGui::GetMousePos();
                const uint16_t x = static_cast<uint16_t>(std::clamp((mouse.x - rmin.x) / rsize.x, 0.f, 1.f) * 255.f);
                const uint16_t y = static_cast<uint16_t>(std::clamp((mouse.y - rmin.y) / rsize.y, 0.f, 1.f) * 191.f);
                app.setTouch(true, x, y);
            } else {
                app.setTouch(false, 0, 0);
            }
        }
    }
    if (paused) {
        if (ImFont* display = app.displayFont()) {
            ImGui::PushFont(display);
        }
        const ImVec2 origin = ImGui::GetWindowPos();
        ImGui::GetWindowDrawList()->AddText(ImVec2(origin.x + 8.f, origin.y + 8.f), kPaused, "PAUSED");
        if (app.displayFont()) {
            ImGui::PopFont();
        }
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}

void drawRightSuite(Application& app, float insetX, float insetY) {
    const ImVec2 suiteAvail = ImGui::GetContentRegionAvail();
    drawSuite(app, ImVec2(suiteAvail.x - insetX, suiteAvail.y - insetY));
}

}  // namespace

void drawShell(Application& app) {
    EmuSession* session = app.session();
    const ImVec2 avail = ImGui::GetContentRegionAvail();
    const float insetX = kConsolePad - ImGui::GetStyle().WindowPadding.x;
    const float insetY = kConsolePad - ImGui::GetStyle().WindowPadding.y;
    if (!session) {
        const ImVec2 cursor = ImGui::GetCursorPos();
        ImGui::SetCursorPos(ImVec2(cursor.x + insetX, cursor.y + insetY));
        const float leftW = avail.x - insetX - kSuiteWidth - kConsolePad - insetX;
        ImGui::BeginChild("left-home", ImVec2(leftW, avail.y - insetY - insetY), ImGuiChildFlags_None,
            ImGuiWindowFlags_NoScrollbar);
        drawHome(app);
        ImGui::EndChild();
        ImGui::SameLine(0.f, kConsolePad);
        drawRightSuite(app, insetX, insetY);
        return;
    }
    const bool nds = session->kind() == ConsoleKind::Nds;
    const int nativeW = session->screenWidth(0);
    const int nativeH = session->screenHeight(0);
    const int screens = 2;
    const float gap = kScreenGap;
    const float consoleAvailW = avail.x - insetX - kSuiteWidth - kConsolePad - insetX;
    const int fit = std::max(1, std::min(static_cast<int>(consoleAvailW / static_cast<float>(nativeW)),
        static_cast<int>((avail.y - insetY - gap) / static_cast<float>(nativeH * screens))));
    const int wanted = app.screenScale();
    const int scale = wanted <= 0 ? fit : std::max(1, std::min(wanted, fit));
    const ImVec2 screen(static_cast<float>(nativeW * scale), static_cast<float>(nativeH * scale));
    const float paneH = screen.y * static_cast<float>(screens) + gap;
    const ImVec2 cursor = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(cursor.x + insetX, cursor.y + insetY));
    const bool partyOn = nds || app.prefs().bottomScreen;
    if (!partyOn) {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, kChassis);
    }
    ImGui::BeginChild("left", ImVec2(screen.x, paneH), ImGuiChildFlags_None, ImGuiWindowFlags_NoScrollbar);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(kScreenGap, kScreenGap));
    if (!partyOn) {
        ImGui::SetCursorPosY((paneH - screen.y) * 0.5f);
    }
    drawScreen("top", app.screen(0), screen, app.paused(), false, app);
    if (nds) {
        drawScreen("bottom", app.screen(1), screen, app.paused(), true, app);
    } else if (app.prefs().bottomScreen) {
        drawGbaPartyLcd(app, screen);
    }
    ImGui::PopStyleVar();
    ImGui::EndChild();
    if (!partyOn) {
        ImGui::PopStyleColor();
    }
    ImGui::SameLine(0.f, kConsolePad);
    drawRightSuite(app, insetX, insetY);
}

}