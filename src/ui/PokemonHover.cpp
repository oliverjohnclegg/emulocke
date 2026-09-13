#include "ui/PokemonDraw.hpp"

#include "poke/Dex.hpp"

#include <cstring>
#include <imgui.h>

namespace emulocke {

void drawMonHover(const MonView& view) {
    if (!view.mon) {
        return;
    }
    const Mon& mon = *view.mon;
    const char* species = view.ref.name && view.ref.name[0] ? view.ref.name : mon.speciesName;
    if (mon.nickname[0] && species && std::strcmp(mon.nickname, species) != 0 &&
        std::strcmp(mon.nickname, mon.speciesName) != 0) {
        ImGui::TextUnformatted(mon.nickname);
        ImGui::TextDisabled("%s", species);
    } else if (species && species[0]) {
        ImGui::TextUnformatted(species);
    }
    const uint8_t level = monLevel(mon, view.national);
    ImGui::TextDisabled("LV");
    ImGui::SameLine();
    ImGui::Text("%u", level);
    if (mon.shiny) {
        ImGui::SameLine(0.f, 12.f);
        ImGui::TextUnformatted("SHINY");
    }
    const char* item = itemName(mon.heldItem, view.gen3);
    ImGui::TextDisabled("ITEM");
    ImGui::SameLine();
    ImGui::TextUnformatted(item && item[0] ? item : "--");
    const char* ability = monAbility(mon, view.national, view.gen3);
    ImGui::TextDisabled("ABL");
    ImGui::SameLine();
    ImGui::TextUnformatted(ability && ability[0] ? ability : "--");
    const char* nature = natureName(mon.nature);
    ImGui::TextDisabled("NAT");
    ImGui::SameLine();
    ImGui::TextUnformatted(nature && nature[0] ? nature : "--");
    ImGui::TextDisabled("EV");
    ImGui::SameLine();
    ImGui::Text("%u/%u/%u/%u/%u/%u", mon.evHp, mon.evAtk, mon.evDef, mon.evSpa, mon.evSpd, mon.evSpe);
    ImGui::TextDisabled("IV");
    ImGui::SameLine();
    ImGui::Text("%u/%u/%u/%u/%u/%u", mon.ivHp, mon.ivAtk, mon.ivDef, mon.ivSpa, mon.ivSpd, mon.ivSpe);
    for (int i = 0; i < 4; ++i) {
        const char* move = moveName(mon.moves[i]);
        ImGui::TextDisabled("M%d", i + 1);
        ImGui::SameLine();
        ImGui::TextUnformatted(move && move[0] ? move : "--");
    }
}

}  // namespace emulocke
