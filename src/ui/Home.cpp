#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "ui/IconAction.hpp"
#include "ui/RunStripDraw.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <string>

namespace emulocke {
namespace {

void drawStartRunHero(Application& app) {
    ImFont* display = app.displayFont();
    if (display) {
        ImGui::PushFont(display);
    }
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(28.f, 16.f));
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
    drawStartRunHero(app);
}

void drawStartRunRail(Application& app) {
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    const float w = ImGui::GetContentRegionAvail().x;
    const float h = kRunPlus + 6.f;
    if (ImGui::InvisibleButton("start-run", ImVec2(w, h))) {
        app.requestNewRun();
    }
    const bool hovered = ImGui::IsItemHovered();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->AddRectFilled(origin, ImVec2(origin.x + w, origin.y + h),
        ImGui::GetColorU32(hovered ? kHeaderHover : kButton));
    dl->AddRect(origin, ImVec2(origin.x + w, origin.y + h), ImGui::GetColorU32(kBorder));
    const ImVec2 plus(origin.x + kRunPad, origin.y + 3.f);
    iconPlus(plus, ImVec2(kRunPlus, kRunPlus));
    const char* label = "START RUN";
    const ImVec2 labelSize = ImGui::CalcTextSize(label);
    dl->AddText(ImVec2(plus.x + kRunPlus + 6.f, origin.y + (h - labelSize.y) * 0.5f),
        ImGui::GetColorU32(kMetal), label);
    ImGui::SetCursorScreenPos(ImVec2(origin.x, origin.y + h + 6.f));
    ImGui::Dummy(ImVec2(w, 0.f));
}

}  // namespace

void drawHome(Application& app) {
    ImGui::BeginChild("home", ImVec2(0, 0), ImGuiChildFlags_Borders);
    if (!app.status().empty()) {
        ImGui::TextWrapped("%s", app.status().c_str());
        ImGui::Dummy(ImVec2(0, 8));
    }
    if (app.runStore().runs().empty()) {
        drawEmptyHome(app);
    } else {
        drawStartRunRail(app);
        const std::string id = drawRunList(app);
        if (!id.empty()) {
            app.queueLoadRun(id);
        }
    }
    ImGui::EndChild();
}

}
