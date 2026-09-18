#include "ui/CalculatorDraw.hpp"

#include "calc/HpBar.hpp"
#include "calc/Labels.hpp"

#include <imgui.h>
#include <cstdio>

namespace emulocke {
namespace {

int collectStages(const Pokemon& mon, char stages[][8]) {
    int n = 0;
    auto add = [&](const char* stat, int8_t v) {
        if (!v || n >= 7) {
            return;
        }
        std::snprintf(stages[n], 8, "%s%+d", stat, v);
        ++n;
    };
    add("ATK", mon.atkStage);
    add("DEF", mon.defStage);
    add("SPA", mon.spaStage);
    add("SPD", mon.spdStage);
    add("SPE", mon.speStage);
    add("ACC", mon.accStage);
    add("EVA", mon.evaStage);
    return n;
}

float stampRowWidth(const char* status, char stages[][8], int n) {
    float w = 0.f;
    if (status) {
        w += ImGui::CalcTextSize(status).x + 16.f;
    }
    for (int i = 0; i < n; ++i) {
        w += ImGui::CalcTextSize(stages[i]).x + 16.f;
    }
    return w > 0.f ? w - 8.f : 0.f;
}

void drawStamps(const char* status, char stages[][8], int n) {
    if (status) {
        calcStamp(status);
    }
    for (int i = 0; i < n; ++i) {
        calcStamp(stages[i]);
    }
}

}  // namespace

void drawCalcSideHead(const char* name, const Pokemon& mon, bool right) {
    if (right) {
        calcAlignRight(ImGui::CalcTextSize(name).x);
    }
    ImGui::TextUnformatted(name);

    char hp[24];
    std::snprintf(hp, sizeof hp, "%d/%d (%d%%)", mon.hp, mon.maxHp, hpExactPct(mon.hp, mon.maxHp));
    char stages[7][8];
    const int n = collectStages(mon, stages);
    const char* status = statusAbbrev(mon.status);
    if (right) {
        if (status || n) {
            calcAlignRight(stampRowWidth(status, stages, n));
            drawStamps(status, stages, n);
        }
        calcAlignRight(calcFoeHpWidth(mon.hp, mon.maxHp));
        calcFoeHp(mon.hp, mon.maxHp);
    } else {
        ImGui::TextUnformatted(hp);
        if (status || n) {
            drawStamps(status, stages, n);
            ImGui::NewLine();
        }
    }
    if (const char* ab = abilityName(mon.ability)) {
        char line[40];
        std::snprintf(line, sizeof line, "AB  %s", ab);
        if (right) {
            calcAlignRight(ImGui::CalcTextSize(line).x);
        }
        ImGui::TextDisabled("%s", line);
    }
}

}
