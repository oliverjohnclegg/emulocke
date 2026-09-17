#include "ui/Cheats.hpp"

#include "application/Application.hpp"
#include "cheats/Book.hpp"
#include "ui/IconAction.hpp"
#include "ui/KitMark.hpp"
#include "ui/KitNav.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>
#include <string>

namespace emulocke {
namespace {

constexpr float kCheatRowH = 26.f;
constexpr float kCheatAddH = 28.f;

void drawCheatRow(Application& app, const Cheat& row, std::string& doomed, bool focus) {
    ImGui::PushID(row.id.c_str());
    const float w = ImGui::GetContentRegionAvail().x;
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->AddRectFilled(origin, ImVec2(origin.x + w, origin.y + kCheatRowH), ImGui::GetColorU32(kFrame));
    dl->AddRect(origin, ImVec2(origin.x + w, origin.y + kCheatRowH), ImGui::GetColorU32(kBorder));
    kitStroke(origin, ImVec2(origin.x + w, origin.y + kCheatRowH), focus);
    const float hit = 18.f;
    const float hitY = origin.y + (kCheatRowH - hit) * 0.5f;
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2.f, (hit - ImGui::GetFontSize()) * 0.5f));
    ImGui::SetCursorScreenPos(ImVec2(origin.x + 6.f, hitY));
    bool on = row.enabled;
    if (ImGui::Checkbox("##on", &on) && on != row.enabled) {
        app.setCheatEnabled(row.id, on);
    }
    ImGui::PopStyleVar();
    const float textY = origin.y + (kCheatRowH - ImGui::GetTextLineHeight()) * 0.5f;
    ImGui::SetCursorScreenPos(ImVec2(origin.x + 30.f, textY));
    ImGui::TextUnformatted(row.name.c_str());
    const ImVec2 del(origin.x + w - 24.f, hitY);
    ImGui::SetCursorScreenPos(del);
    if (iconAction("del", "Delete", ImVec2(18.f, 18.f))) {
        doomed = row.id;
    }
    iconX(del, ImVec2(18.f, 18.f));
    ImGui::SetCursorScreenPos(ImVec2(origin.x, origin.y + kCheatRowH + 4.f));
    ImGui::Dummy(ImVec2(w, 0.f));
    ImGui::PopID();
}

bool drawCheatAddStamp(bool focus) {
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    const float w = ImGui::GetContentRegionAvail().x;
    ImGui::InvisibleButton("add-cheat", ImVec2(w, kCheatAddH));
    const bool hovered = ImGui::IsItemHovered();
    const bool clicked = ImGui::IsItemClicked();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    dl->AddRectFilled(origin, ImVec2(origin.x + w, origin.y + kCheatAddH), kitPlate(hovered || focus));
    dl->AddRect(origin, ImVec2(origin.x + w, origin.y + kCheatAddH), ImGui::GetColorU32(kBorder));
    kitStroke(origin, ImVec2(origin.x + w, origin.y + kCheatAddH), focus);
    const ImVec2 plus(origin.x + 6.f, origin.y + (kCheatAddH - 18.f) * 0.5f);
    iconPlus(plus, ImVec2(18.f, 18.f));
    const char* label = "ADD";
    const ImVec2 ts = ImGui::CalcTextSize(label);
    dl->AddText(ImVec2(plus.x + 22.f, origin.y + (kCheatAddH - ts.y) * 0.5f), ImGui::GetColorU32(kMetal),
        label);
    return clicked;
}

}  // namespace

void drawCheats(Application& app) {
    if (app.bodyFont()) {
        ImGui::PushFont(app.bodyFont());
    }
    const auto& items = app.cheats().items();
    const int n = static_cast<int>(items.size());
    KitFocus& focus = app.kitFocus();
    std::string doomed;
    if (kitNavSuite(app, KitTab::Cheats)) {
        const KitFrame& kit = app.kit();
        kitMove(focus.cheatsRow, n + 1, kit.up || kit.left, kit.down || kit.right);
        if (kit.act && focus.cheatsRow == n) {
            focus.openCheatAdd = true;
        } else if (kit.act && focus.cheatsRow >= 0 && focus.cheatsRow < n) {
            const Cheat& row = items[static_cast<std::size_t>(focus.cheatsRow)];
            app.setCheatEnabled(row.id, !row.enabled);
        }
        if (kit.backspace && focus.cheatsRow >= 0 && focus.cheatsRow < n) {
            doomed = items[static_cast<std::size_t>(focus.cheatsRow)].id;
        }
    }
    const float gap = 8.f;
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(ImGui::GetStyle().ItemSpacing.x, 0.f));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, kScreenWell);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.f, 8.f));
    const float wellH = ImGui::GetContentRegionAvail().y - kCheatAddH - gap;
    ImGui::BeginChild("cheats-well", ImVec2(0, wellH),
        ImGuiChildFlags_Borders | ImGuiChildFlags_AlwaysUseWindowPadding);
    int i = 0;
    for (const Cheat& row : items) {
        drawCheatRow(app, row, doomed, i == focus.cheatsRow);
        ++i;
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    ImGui::Dummy(ImVec2(0, gap));
    if (!doomed.empty()) {
        app.removeCheat(doomed);
    }
    const bool add = drawCheatAddStamp(focus.cheatsRow == n);
    ImGui::PopStyleVar();
    if (add || focus.openCheatAdd) {
        focus.openCheatAdd = false;
        ImGui::OpenPopup("ADD");
    }
    drawCheatsAdd(app);
    if (app.bodyFont()) {
        ImGui::PopFont();
    }
}

}
