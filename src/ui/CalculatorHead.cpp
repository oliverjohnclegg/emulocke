#include "ui/CalculatorDraw.hpp"

#include "calc/Ability.hpp"
#include "calc/Labels.hpp"

#include <imgui.h>
#include <cstdio>

namespace emulocke {
namespace {

const char* statusTag(uint32_t s) {
    if (s & 7) {
        return "SLP";
    }
    if (s & kStFrz) {
        return "FRZ";
    }
    if (s & kStPar) {
        return "PAR";
    }
    if (s & kStBurn) {
        return "BRN";
    }
    if (s & kStToxic) {
        return "TOX";
    }
    if (s & kStPsn) {
        return "PSN";
    }
    return nullptr;
}

}  // namespace

void drawCalcSideHead(const char* name, const Pokemon& mon, bool right) {
    if (right) {
        calcAlignRight(ImGui::CalcTextSize(name).x);
    }
    ImGui::TextUnformatted(name);

    char hp[16];
    std::snprintf(hp, sizeof hp, "%d/%d", mon.hp, mon.maxHp);
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
    const char* status = statusTag(mon.status);
    const int stamps = (status ? 1 : 0) + n;
    if (right) {
        float row = 48.f;
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
        calcPixelBar(mon.hp, mon.maxHp);
        ImGui::NewLine();
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