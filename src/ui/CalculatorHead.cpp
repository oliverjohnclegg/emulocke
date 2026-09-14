#include "ui/CalculatorDraw.hpp"

#include "calc/HpBar.hpp"
#include "calc/Labels.hpp"

#include <imgui.h>
#include <cstdio>

namespace emulocke {

void drawCalcSideHead(const char* name, const Pokemon& mon, bool right, bool* crit) {
    if (right) {
        calcAlignRight(ImGui::CalcTextSize(name).x);
    }
    ImGui::TextUnformatted(name);

    char hp[24];
    std::snprintf(hp, sizeof hp, "%d/%d (%d%%)", mon.hp, mon.maxHp, hpExactPct(mon.hp, mon.maxHp));
    char stages[5][8];
    int n = 0;
    auto addStage = [&](const char* stat, int8_t v) {
        if (!v || n >= 5) {
            return;
        }
        std::snprintf(stages[n], sizeof stages[0], "%s%+d", stat, v);
        ++n;
    };
    addStage("ATK", mon.atkStage);
    addStage("DEF", mon.defStage);
    addStage("SPA", mon.spaStage);
    addStage("SPD", mon.spdStage);
    addStage("SPE", mon.speStage);
    const char* status = statusAbbrev(mon.status);
    const int stamps = (status ? 1 : 0) + n;
    if (right) {
        float row = calcFoeHpWidth(mon.hp, mon.maxHp);
        if (stamps) {
            row += ImGui::GetStyle().ItemSpacing.x;
            if (status) {
                row += ImGui::CalcTextSize(status).x + 16.f;
            }
            for (int i = 0; i < n; ++i) {
                row += ImGui::CalcTextSize(stages[i]).x + 16.f;
            }
            row -= 8.f;
        }
        calcAlignRight(row);
        if (status) {
            calcStamp(status);
        }
        for (int i = 0; i < n; ++i) {
            calcStamp(stages[i]);
        }
        calcFoeHp(mon.hp, mon.maxHp);
    } else {
        ImGui::TextUnformatted(hp);
        if (stamps) {
            ImGui::SameLine();
            if (status) {
                calcStamp(status);
            }
            for (int i = 0; i < n; ++i) {
                calcStamp(stages[i]);
            }
            ImGui::NewLine();
        }
    }
    ImGui::PushID(right ? "fh" : "oh");
    if (const char* ab = abilityName(mon.ability)) {
        char line[40];
        std::snprintf(line, sizeof line, "AB  %s", ab);
        if (right) {
            calcAlignRight(ImGui::CalcTextSize(line).x);
        }
        ImGui::TextDisabled("%s", line);
        if (crit) {
            if (right) {
                const ImVec2 ab = ImGui::GetItemRectMin();
                const ImVec2 next = ImGui::GetCursorScreenPos();
                const float cr = ImGui::CalcTextSize("CR").x + 4.f;
                ImGui::SetCursorScreenPos(ImVec2(ab.x - 4.f - cr, ab.y));
                if (calcCritMark(*crit)) {
                    *crit = !*crit;
                }
                ImGui::SetCursorScreenPos(next);
            } else {
                ImGui::SameLine(0.f, 4.f);
                if (calcCritMark(*crit)) {
                    *crit = !*crit;
                }
            }
        }
    }
    ImGui::PopID();
}

}
