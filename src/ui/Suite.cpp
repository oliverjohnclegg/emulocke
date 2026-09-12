#include "ui/Suite.hpp"

#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {
namespace {

void drawSuiteChip(ImFont* display) {
    const char* label = "SUITE";
    if (display) {
        ImGui::PushFont(display);
    }
    const ImVec2 pad(12.f, 6.f);
    const ImVec2 text = ImGui::CalcTextSize(label);
    const ImVec2 size(text.x + pad.x * 2.f, text.y + pad.y * 2.f);
    const ImVec2 p = ImGui::GetCursorScreenPos();
    ImGui::GetWindowDrawList()->AddRectFilled(
        p, ImVec2(p.x + size.x, p.y + size.y), ImGui::ColorConvertFloat4ToU32(kCream), 4.f);
    ImGui::SetCursorScreenPos(ImVec2(p.x + pad.x, p.y + pad.y));
    ImGui::PushStyleColor(ImGuiCol_Text, kOnCream);
    ImGui::TextUnformatted(label);
    ImGui::PopStyleColor();
    if (display) {
        ImGui::PopFont();
    }
    ImGui::SetCursorScreenPos(ImVec2(p.x, p.y + size.y));
    ImGui::Dummy(ImVec2(size.x, 0.f));
}

}  // namespace

void drawSuite(ImFont* display, ImFont* body, const std::string& status, const char* romName) {
    ImGui::BeginChild("suite", ImVec2(0, 0), ImGuiChildFlags_Borders);
    drawSuiteChip(display);
    ImGui::Dummy(ImVec2(0, 10.f));
    ImGui::Separator();
    if (body) {
        ImGui::PushFont(body);
    }
    ImGui::Dummy(ImVec2(0, 12));
    ImGui::PushStyleColor(ImGuiCol_Text, kDisabled);
    ImGui::TextUnformatted("Tools will live here.");
    ImGui::Spacing();
    ImGui::TextWrapped("Damage calc, tracker, and QoL sit in this pane later.");
    ImGui::PopStyleColor();
    if (!status.empty()) {
        ImGui::Dummy(ImVec2(0, 16));
        ImGui::TextUnformatted(status.c_str());
    }
    if (romName && *romName) {
        ImGui::TextDisabled("%s", romName);
    }
    if (body) {
        ImGui::PopFont();
    }
    ImGui::EndChild();
}

}
