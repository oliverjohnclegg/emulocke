#include "ui/HomeKit.hpp"

#include "application/Application.hpp"
#include "ui/IconAction.hpp"
#include "ui/KitMark.hpp"
#include "ui/KitNav.hpp"
#include "ui/RunStripDraw.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {
namespace {

void drawStartRunHero(Application& app, bool focus) {
    ImFont* display = app.displayFont();
    if (display) {
        ImGui::PushFont(display);
    }
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(28.f, 16.f));
    if (ImGui::Button("START RUN") || (focus && kitNavHome(app) && app.kit().act)) {
        app.requestNewRun();
    }
    kitStroke(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), focus);
    ImGui::PopStyleVar();
    if (display) {
        ImGui::PopFont();
    }
}

}  // namespace

void applyHomeKit(Application& app, const std::vector<const Run*>& plates) {
    if (!kitNavHome(app)) {
        return;
    }
    KitFocus& focus = app.kitFocus();
    const KitFrame& kit = app.kit();
    const int n = 1 + static_cast<int>(plates.size());
    if (kit.snap) {
        focus.homeIndex = 0;
    }
    kitMove(focus.homeIndex, n, kit.up || kit.left, kit.right);
    if (kit.act && focus.homeIndex == 0) {
        app.requestNewRun();
    } else if (kit.act && focus.homeIndex > 0) {
        app.queueLoadRun(plates[static_cast<std::size_t>(focus.homeIndex - 1)]->id);
    }
    if (focus.homeIndex > 0) {
        const Run* run = plates[static_cast<std::size_t>(focus.homeIndex - 1)];
        if (kit.down) {
            app.requestNewAttempt(run->id);
        }
        if (kit.backspace) {
            app.requestDeleteRun(run->id);
        }
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
    if (kitNavHome(app) && app.kit().snap) {
        app.kitFocus().homeIndex = 0;
    }
    drawStartRunHero(app, true);
}

void drawStartRunRail(Application& app, bool focus) {
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    const float w = ImGui::GetContentRegionAvail().x;
    const float h = kRunPlus + 6.f;
    if (ImGui::InvisibleButton("start-run", ImVec2(w, h))) {
        app.requestNewRun();
    }
    const bool hovered = ImGui::IsItemHovered();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->AddRectFilled(origin, ImVec2(origin.x + w, origin.y + h), kitPlate(hovered || focus));
    dl->AddRect(origin, ImVec2(origin.x + w, origin.y + h), ImGui::GetColorU32(kBorder));
    kitStroke(origin, ImVec2(origin.x + w, origin.y + h), focus);
    const ImVec2 plus(origin.x + kRunPad, origin.y + 3.f);
    iconPlus(plus, ImVec2(kRunPlus, kRunPlus));
    const char* label = "START RUN";
    const ImVec2 labelSize = ImGui::CalcTextSize(label);
    dl->AddText(ImVec2(plus.x + kRunPlus + 6.f, origin.y + (h - labelSize.y) * 0.5f),
        ImGui::GetColorU32(kMetal), label);
    ImGui::SetCursorScreenPos(ImVec2(origin.x, origin.y + h + 6.f));
    ImGui::Dummy(ImVec2(w, 0.f));
}

}
