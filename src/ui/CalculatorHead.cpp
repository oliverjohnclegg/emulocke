#include "ui/CalculatorDraw.hpp"

#include "calc/HpBar.hpp"
#include "calc/Labels.hpp"
#include "poke/Dex.hpp"

#include <imgui.h>
#include <cstdio>

namespace emulocke {
namespace {

int collectStages(const Pokemon& mon, char stages[][8], const char* labels[8], const char* status) {
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
    int m = 0;
    if (status) {
        labels[m++] = status;
    }
    for (int i = 0; i < n; ++i) {
        labels[m++] = stages[i];
    }
    return m;
}

}  // namespace

void drawCalcSideHead(const char* name, const Pokemon& mon, bool right, bool hold) {
    if (right) {
        calcAlignRight(ImGui::CalcTextSize(name).x);
    }
    ImGui::TextUnformatted(name);

    char hp[24];
    std::snprintf(hp, sizeof hp, "%d/%d (%d%%)", mon.hp, mon.maxHp, hpExactPct(mon.hp, mon.maxHp));
    char stages[7][8];
    const char* labels[8];
    const int m = collectStages(mon, stages, labels, statusAbbrev(mon.status));
    if (right) {
        if (m || hold) {
            calcStampBlock(labels, m, true, hold);
        }
        calcAlignRight(calcFoeHpWidth(mon.hp, mon.maxHp));
        calcFoeHp(mon.hp, mon.maxHp);
    } else {
        ImGui::TextUnformatted(hp);
        if (m || hold) {
            calcStampBlock(labels, m, false, hold);
        }
    }
    const char* ab = abilityName(static_cast<uint16_t>(mon.ability));
    if (ab && ab[0]) {
        char line[40];
        std::snprintf(line, sizeof line, "AB  %s", ab);
        if (right) {
            calcAlignRight(ImGui::CalcTextSize(line).x);
        }
        ImGui::TextDisabled("%s", line);
    }
}

}
