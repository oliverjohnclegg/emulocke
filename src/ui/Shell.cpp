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

void drawConsoleScreens(Application& app, EmuSession& session, ImVec2 pane) {
    const bool nds = session.kind() == ConsoleKind::Nds;
    const bool partyLcd = !nds && app.prefs().bottomScreen;
    const int nativeW = session.screenWidth(0);
    const int nativeH = session.screenHeight(0);
    const int screens = (nds || partyLcd) ? 2 : 1;
    const ImVec2 win = ImGui::GetWindowSize();
    const LcdLayout lcd = layoutLcds(app.screenScale(), nativeW, nativeH, screens, std::max(pane.x, win.x),
        std::max(pane.y, win.y));
    const ImVec2 screen(lcd.screenW, lcd.screenH);
    ImGui::SetCursorPos(ImVec2(lcd.x, lcd.y));
    drawScreen("top", app.screen(0), screen, app.paused(), false, app);
    if (nds || partyLcd) {
        ImGui::SetCursorPos(ImVec2(lcd.x, lcd.y + lcd.screenH + lcd.gap));
        if (nds) {
            drawScreen("bottom", app.screen(1), screen, app.paused(), true, app);
        } else {
            drawGbaPartyLcd(app, screen);
        }
    }
}

}  // namespace

void drawShell(Application& app) {
    const ImVec2 avail = ImGui::GetContentRegionAvail();
    const float insetX = kConsolePad - ImGui::GetStyle().WindowPadding.x;
    const float insetY = kConsolePad - ImGui::GetStyle().WindowPadding.y;
    const bool showRight = app.prefs().rightPane;
    const float rightSpan = showRight ? kRightPaneSpan : 0.f;
    ImVec2 left(consoleLeftWidth(avail.x, ImGui::GetStyle().WindowPadding.x, rightSpan),
        consoleLeftHeight(avail.y, ImGui::GetStyle().WindowPadding.y));
    EmuSession* session = app.session();
    if (session && (session->kind() == ConsoleKind::Nds || app.prefs().bottomScreen)) {
        left.y += kScreenGap;
    }
    const ImVec2 cursor = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(cursor.x + insetX, cursor.y + insetY));
    if (session) {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, kChassis);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    }
    ImGui::BeginChild("left", left, ImGuiChildFlags_None, ImGuiWindowFlags_NoScrollbar);
    if (session) {
        drawConsoleScreens(app, *session, left);
    } else {
        drawHome(app);
    }
    ImGui::EndChild();
    if (session) {
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
    }
    if (showRight) {
        ImGui::SameLine(0.f, kConsolePad);
        drawRightSuite(app, insetX, insetY);
    }
}

}
