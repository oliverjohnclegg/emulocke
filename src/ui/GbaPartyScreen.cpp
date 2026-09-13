#include "ui/GbaPartyScreen.hpp"

#include "application/Application.hpp"
#include "ui/GbaPartySlot.hpp"
#include "ui/Theme.hpp"

#include <algorithm>
#include <cmath>

namespace emulocke {
namespace {

ImU32 metalA(int a) {
    return IM_COL32(215, 205, 189, a);
}

void glass(ImDrawList* dl, ImVec2 a, ImVec2 b) {
    const ImVec2 ia(a.x + 4.f, a.y + 4.f);
    const ImVec2 ib(b.x - 4.f, b.y - 4.f);
    dl->AddRect(ia, ib, metalA(28));
    dl->AddLine(ia, ImVec2(ib.x, ia.y), metalA(40));
    dl->AddLine(ia, ImVec2(ia.x, ib.y), metalA(22));
    constexpr float step = 16.f;
    for (float x = ia.x + step; x < ib.x; x += step) {
        dl->AddLine(ImVec2(x, ia.y), ImVec2(x, ib.y), metalA(14));
    }
    for (float y = ia.y + step; y < ib.y; y += step) {
        dl->AddLine(ImVec2(ia.x, y), ImVec2(ib.x, y), metalA(14));
    }
    const float tick = 9.f;
    const ImU32 tickC = metalA(90);
    auto corner = [&](ImVec2 o, float sx, float sy) {
        dl->AddLine(o, ImVec2(o.x + sx * tick, o.y), tickC);
        dl->AddLine(o, ImVec2(o.x, o.y + sy * tick), tickC);
    };
    corner(ia, 1.f, 1.f);
    corner(ImVec2(ib.x, ia.y), -1.f, 1.f);
    corner(ImVec2(ia.x, ib.y), 1.f, -1.f);
    corner(ib, -1.f, -1.f);
}

}  // namespace

void drawGbaPartyLcd(Application& app, ImVec2 size) {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, kScreenWell);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    ImGui::BeginChild("gba-party", size, ImGuiChildFlags_Borders, ImGuiWindowFlags_NoScrollbar);
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImVec2 a = ImGui::GetWindowPos();
    const ImVec2 b(a.x + size.x, a.y + size.y);
    glass(dl, a, b);
    GameSnapshot snap;
    app.copySnapshot(snap);
    const float pad = std::max(8.f, size.x * 0.045f);
    const float gapX = std::max(6.f, size.x * 0.03f);
    const float gapY = std::max(8.f, size.y * 0.06f);
    const float trackH = std::max(3.f, std::floor(size.y * 0.028f));
    const float trackGap = 3.f;
    const float cellW = (size.x - pad * 2.f - gapX * 2.f) / 3.f;
    const float cellH = (size.y - pad * 2.f - gapY) / 2.f;
    const float wellH = cellH - trackGap - trackH;
    for (int i = 0; i < 6; ++i) {
        const ImVec2 wa(std::floor(a.x + pad + (i % 3) * (cellW + gapX)),
            std::floor(a.y + pad + (i / 3) * (cellH + gapY)));
        const ImVec2 wb(std::floor(wa.x + cellW), std::floor(wa.y + wellH));
        drawPartySlot(app, snap.party.mons[static_cast<std::size_t>(i)], i, wa, wb,
            ImVec2(wa.x, wb.y + trackGap), ImVec2(wb.x, wb.y + trackGap + trackH));
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}

}
