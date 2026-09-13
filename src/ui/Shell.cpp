#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "emu/EmuSession.hpp"
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

void drawConsoleScreens(Application& app, EmuSession& session) {
    const bool nds = session.kind() == ConsoleKind::Nds;
    const int nativeW = session.screenWidth(0);
    const int nativeH = session.screenHeight(0);
    const int screens = nds ? 2 : 1;
    const ImVec2 pane = ImGui::GetContentRegionAvail();
    const int scale = resolveScreenScale(app.screenScale(), nativeW, nativeH, screens, pane.x, pane.y);
    const ImVec2 screen(static_cast<float>(nativeW * scale), static_cast<float>(nativeH * scale));
    const float gap = screenStackGap(nds, pane.y, screen.y * static_cast<float>(screens));
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (pane.x - screen.x) * 0.5f);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(kScreenGap, gap));
    drawScreen("top", app.screen(0), screen, app.paused(), false, app);
    if (nds) {
        drawScreen("bottom", app.screen(1), screen, app.paused(), true, app);
    }
    ImGui::PopStyleVar();
}

}  // namespace

void drawShell(Application& app) {
    const ImVec2 avail = ImGui::GetContentRegionAvail();
    const float insetX = kConsolePad - ImGui::GetStyle().WindowPadding.x;
    const float insetY = kConsolePad - ImGui::GetStyle().WindowPadding.y;
    const bool showRight = app.prefs().rightPane;
    const float rightSpan = showRight ? kRightPaneSpan : 0.f;
    const ImVec2 left(consoleLeftWidth(avail.x, ImGui::GetStyle().WindowPadding.x, rightSpan),
        consoleLeftHeight(avail.y, ImGui::GetStyle().WindowPadding.y));
    const ImVec2 cursor = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(cursor.x + insetX, cursor.y + insetY));
    EmuSession* session = app.session();
    if (session) {
        ImGui::PushStyleColor(ImGuiCol_ChildBg, kChassis);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    }
    ImGui::BeginChild("left", left, ImGuiChildFlags_None, ImGuiWindowFlags_NoScrollbar);
    if (session) {
        ImGui::PopStyleVar();
        ImGui::PopStyleColor();
        drawConsoleScreens(app, *session);
    } else {
        drawHome(app);
    }
    ImGui::EndChild();
    if (showRight) {
        ImGui::SameLine(0.f, kConsolePad);
        drawRightSuite(app, insetX, insetY);
    }
}

}
