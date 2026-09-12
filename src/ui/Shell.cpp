#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "emu/EmuSession.hpp"

#include <imgui.h>
#include <algorithm>
#include <string>

namespace emulocke {

namespace {

void drawScreen(const char* id, ScreenTexture& tex, ImVec2 avail, bool paused, bool touch, Application& app) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.043f, 0.047f, 0.039f, 1.f));
    ImGui::BeginChild(id, avail, ImGuiChildFlags_Borders);
    if (tex.texture()) {
        const float maxW = ImGui::GetContentRegionAvail().x;
        const float maxH = ImGui::GetContentRegionAvail().y;
        const int scale = std::max(1, std::min(static_cast<int>(maxW / tex.width()), static_cast<int>(maxH / tex.height())));
        const ImVec2 size(static_cast<float>(tex.width() * scale), static_cast<float>(tex.height() * scale));
        ImGui::SetCursorPosX((maxW - size.x) * 0.5f);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (maxH - size.y) * 0.5f);
        ImGui::Image(tex.texture(), size);
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
        ImGui::GetWindowDrawList()->AddText(ImVec2(origin.x + 12.f, origin.y + 12.f), IM_COL32(196, 43, 43, 255), "PAUSED");
    }
    ImGui::EndChild();
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
    const float left = ImGui::GetContentRegionAvail().x * 0.52f;
    ImGui::BeginChild("left", ImVec2(left, 0), ImGuiChildFlags_None);
    const float paneH = nds ? (ImGui::GetContentRegionAvail().y - 8.f) * 0.5f : ImGui::GetContentRegionAvail().y;
    drawScreen("top", app.screen(0), ImVec2(0, paneH), app.paused(), false, app);
    if (nds) {
        ImGui::Dummy(ImVec2(0, 8));
        drawScreen("bottom", app.screen(1), ImVec2(0, 0), app.paused(), true, app);
    }
    ImGui::EndChild();
    ImGui::SameLine();
    const char* romName = session ? session->romName().c_str() : "";
    drawSuite(app.displayFont(), app.bodyFont(), app.status(), romName);
}

}