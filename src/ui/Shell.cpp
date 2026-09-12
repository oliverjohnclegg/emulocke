#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "emu/EmuSession.hpp"
#include "ui/Suite.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <algorithm>

namespace emulocke {

namespace {

constexpr float kHinge = 12.f;

void drawScreen(const char* id, ScreenTexture& tex, ImVec2 avail, bool paused, bool touch, Application& app) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, kScreenWell);
    ImGui::BeginChild(id, avail, ImGuiChildFlags_Borders);
    if (tex.texture()) {
        const float maxW = ImGui::GetContentRegionAvail().x;
        const float maxH = ImGui::GetContentRegionAvail().y;
        const int scale = std::max(1, std::min(static_cast<int>(maxW / tex.width()), static_cast<int>(maxH / tex.height())));
        const ImVec2 size(static_cast<float>(tex.width() * scale), static_cast<float>(tex.height() * scale));
        ImGui::SetCursorPosX((maxW - size.x) * 0.5f);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (maxH - size.y) * 0.5f);
        ImDrawList* dl = ImGui::GetWindowDrawList();
        ImGuiPlatformIO& pio = ImGui::GetPlatformIO();
        if (pio.DrawCallback_SetSamplerNearest) {
            dl->AddCallback(pio.DrawCallback_SetSamplerNearest, nullptr);
        }
        ImGui::Image(tex.texture(), size);
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
        const ImVec2 origin = ImGui::GetWindowPos();
        ImGui::GetWindowDrawList()->AddText(ImVec2(origin.x + 12.f, origin.y + 12.f), kPaused, "PAUSED");
    }
    ImGui::EndChild();
    ImGui::PopStyleColor();
}

}  // namespace

void drawShell(Application& app) {
    EmuSession* session = app.session();
    const bool nds = session && session->kind() == ConsoleKind::Nds;
    const float left = ImGui::GetContentRegionAvail().x * 0.52f;
    ImGui::BeginChild("left", ImVec2(left, 0), ImGuiChildFlags_None);
    const float paneH = nds ? (ImGui::GetContentRegionAvail().y - kHinge) * 0.5f : ImGui::GetContentRegionAvail().y;
    drawScreen("top", app.screen(0), ImVec2(0, paneH), app.paused(), false, app);
    if (nds) {
        ImGui::Dummy(ImVec2(0, kHinge));
        drawScreen("bottom", app.screen(1), ImVec2(0, 0), app.paused(), true, app);
    }
    ImGui::EndChild();
    ImGui::SameLine();
    const char* romName = session ? session->romName().c_str() : "";
    drawSuite(app.displayFont(), app.bodyFont(), app.status(), romName);
}

}
