#include "ui/Shell.hpp"

#include "application/Application.hpp"

#include <imgui.h>
#include <string>

namespace emulocke {
namespace {

void drawEmptyHome(Application& app) {
    const char* msg = "No save files found";
    const char* start = "Start Run";
    ImFont* display = app.displayFont();
    if (display) {
        ImGui::PushFont(display);
    }
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(28.f, 16.f));
    const ImVec2 msgSize = ImGui::CalcTextSize(msg);
    const ImVec2 btnLabel = ImGui::CalcTextSize(start);
    const ImVec2 btnSize(btnLabel.x + 56.f, btnLabel.y + 32.f);
    ImGui::PopStyleVar();
    if (display) {
        ImGui::PopFont();
    }
    const ImVec2 origin = ImGui::GetCursorPos();
    const ImVec2 avail = ImGui::GetContentRegionAvail();
    const float gap = 22.f;
    const float blockH = msgSize.y + gap + btnSize.y;
    ImGui::SetCursorPos(ImVec2(origin.x + (avail.x - msgSize.x) * 0.5f,
        origin.y + (avail.y - blockH) * 0.5f));
    if (display) {
        ImGui::PushFont(display);
    }
    ImGui::TextUnformatted(msg);
    ImGui::SetCursorPos(ImVec2(origin.x + (avail.x - btnSize.x) * 0.5f,
        origin.y + (avail.y - blockH) * 0.5f + msgSize.y + gap));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(28.f, 16.f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.77f, 0.17f, 0.17f, 0.85f));
    if (ImGui::Button(start, btnSize)) {
        app.requestNewRun();
    }
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    if (display) {
        ImGui::PopFont();
    }
}

}  // namespace

void drawHome(Application& app) {
    ImGui::BeginChild("home", ImVec2(0, 0), ImGuiChildFlags_Borders);
    if (app.runStore().runs().empty()) {
        drawEmptyHome(app);
    } else {
        const std::string id = drawGroupedRunList(app, "home", true);
        if (!id.empty()) {
            app.queueLoadRun(id);
        }
    }
    ImGui::EndChild();
}

}