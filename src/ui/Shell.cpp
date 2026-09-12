#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "emu/EmuSession.hpp"
#include "ui/Layout.hpp"

#include <imgui.h>
#include <algorithm>
#include <string>

namespace emulocke {

namespace {

void drawScreen(const char* id, ScreenTexture& tex, ImVec2 size, bool paused, bool touch, Application& app) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.043f, 0.047f, 0.039f, 1.f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    ImGui::BeginChild(id, size, ImGuiChildFlags_Borders, ImGuiWindowFlags_NoScrollbar);
    if (tex.texture()) {
        ImGui::Image(tex.texture(), ImGui::GetContentRegionAvail());
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
        const ImVec2 origin = ImGui::GetWindowPos();
        ImGui::GetWindowDrawList()->AddText(ImVec2(origin.x + 8.f, origin.y + 8.f), IM_COL32(196, 43, 43, 255), "PAUSED");
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}

void drawSuite(ImFont* display, ImFont* body, const std::string& status, const char* romName) {
    ImGui::BeginChild("suite", ImVec2(0, 0), ImGuiChildFlags_Borders);
    if (display) ImGui::PushFont(display);
    ImGui::TextUnformatted("FIELD LOG");
    if (display) ImGui::PopFont();
    ImGui::Separator();
    if (body) ImGui::PushFont(body);
    ImGui::Dummy(ImVec2(0, 12));
    ImGui::TextDisabled("Nuzlocke suite comes later.");
    ImGui::Spacing();
    ImGui::TextWrapped("Damage calc, progression tracker, and QoL tools will live here. This pane stays empty until then.");
    if (!status.empty()) {
        ImGui::Dummy(ImVec2(0, 16));
        ImGui::TextUnformatted(status.c_str());
    }
    if (romName && *romName) {
        ImGui::TextDisabled("%s", romName);
    }
    if (body) ImGui::PopFont();
    ImGui::EndChild();
}

}  // namespace

void drawShell(Application& app) {
    EmuSession* session = app.session();
    const bool nds = session && session->kind() == ConsoleKind::Nds;
    const int nativeW = session ? session->screenWidth(0) : kNativeW;
    const int nativeH = session ? session->screenHeight(0) : kNativeH;
    const int screens = nds ? 2 : 1;
    const ImVec2 avail = ImGui::GetContentRegionAvail();
    const float gap = nds ? kScreenGap : 0.f;
    const float insetX = kConsolePad - ImGui::GetStyle().WindowPadding.x;
    const float insetY = kConsolePad - ImGui::GetStyle().WindowPadding.y;
    const float consoleAvailW = avail.x - insetX - kSuiteWidth - kConsolePad;
    const int scale = std::max(1, std::min(static_cast<int>(consoleAvailW / static_cast<float>(nativeW)),
        static_cast<int>((avail.y - insetY - gap) / static_cast<float>(nativeH * screens))));
    const ImVec2 screen(static_cast<float>(nativeW * scale), static_cast<float>(nativeH * scale));
    const ImVec2 cursor = ImGui::GetCursorPos();
    ImGui::SetCursorPos(ImVec2(cursor.x + insetX, cursor.y + insetY));
    ImGui::BeginChild("left", ImVec2(screen.x, screen.y * static_cast<float>(screens) + gap), ImGuiChildFlags_None,
        ImGuiWindowFlags_NoScrollbar);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(kScreenGap, kScreenGap));
    drawScreen("top", app.screen(0), screen, app.paused(), false, app);
    if (nds) {
        drawScreen("bottom", app.screen(1), screen, app.paused(), true, app);
    }
    ImGui::PopStyleVar();
    ImGui::EndChild();
    ImGui::SameLine(0.f, kConsolePad);
    const char* romName = session ? session->romName().c_str() : "";
    drawSuite(app.displayFont(), app.bodyFont(), app.status(), romName);
}

}
