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

void stageTag(const char* stat, int8_t v) {
    if (!v) {
        return;
    }
    char b[8];
    std::snprintf(b, sizeof b, "%s%+d", stat, v);
    calcStamp(b);
}

}  // namespace

void drawCalcSideHead(const char* name, const Pokemon& mon) {
    ImGui::TextUnformatted(name);
    ImGui::Text("%d/%d", mon.hp, mon.maxHp);
    if (const char* tag = statusTag(mon.status)) {
        ImGui::SameLine();
        calcStamp(tag);
    }
    stageTag("ATK", mon.atkStage);
    stageTag("DEF", mon.defStage);
    stageTag("SPA", mon.spaStage);
    stageTag("SPD", mon.spdStage);
    stageTag("SPE", mon.speStage);
    if (const char* ab = abilityName(mon.ability)) {
        ImGui::NewLine();
        ImGui::TextDisabled("%s", ab);
    }
}

}