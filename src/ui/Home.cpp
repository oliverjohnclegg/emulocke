#include "ui/Shell.hpp"

#include "application/Application.hpp"

#include <imgui.h>
#include <string>

namespace emulocke {
namespace {

void drawStartRun(Application& app, ImVec2 pad) {
    ImFont* display = app.displayFont();
    if (display) {
        ImGui::PushFont(display);
    }
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, pad);
    if (ImGui::Button("START RUN")) {
        app.requestNewRun();
    }
    ImGui::PopStyleVar();
    if (display) {
        ImGui::PopFont();
    }
}

void drawEmptyHome(Application& app) {
    const char* msg = "No save files found";
    ImFont* display = app.displayFont();
    if (display) {
        ImGui::PushFont(display);
    }
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(28.f, 16.f));
    const ImVec2 msgSize = ImGui::CalcTextSize(msg);
    const ImVec2 btnLabel = ImGui::CalcTextSize("START RUN");
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
    if (display) {
        ImGui::PopFont();
    }
    ImGui::SetCursorPos(ImVec2(origin.x + (avail.x - btnSize.x) * 0.5f,
        origin.y + (avail.y - blockH) * 0.5f + msgSize.y + gap));
    drawStartRun(app, ImVec2(28.f, 16.f));
}

}  // namespace

void drawHome(Application& app) {
    ImGui::BeginChild("home", ImVec2(0, 0), ImGuiChildFlags_Borders);
    if (app.runStore().runs().empty()) {
        drawEmptyHome(app);
    } else {
        drawStartRun(app, ImVec2(12.f, 6.f));
        ImGui::Dummy(ImVec2(0.f, 8.f));
        const std::string id = drawRunList(app);
        if (!id.empty()) {
            app.queueLoadRun(id);
        }
    }
    ImGui::EndChild();
}

}
