#include "ui/CalculatorDraw.hpp"
#include "ui/CalculatorWell.hpp"

#include "adapter/gen45/Names.hpp"
#include "application/Application.hpp"
#include "calc/Dex.hpp"
#include "poke/SpriteIndex.hpp"
#include "ui/KitMark.hpp"
#include "ui/KitNav.hpp"

#include <imgui.h>
#include <string>

namespace emulocke {

void drawCalcPartyRail(Application& app, CalcSession& session) {
    const GameSnapshot* snap = session.snap();
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    for (int i = 0; i < 6; ++i) {
        const Mon* mon = snap ? &snap->party.mons[static_cast<std::size_t>(i)] : nullptr;
        const std::string slug = mon && mon->species ? speciesSlug(mon->speciesName) : "";
        const bool dim = mon && mon->species && mon->hp == 0;
        const ImVec2 a(origin.x, origin.y + i * (kCalcWell + 4.f));
        ImGui::SetCursorScreenPos(a);
        ImGui::PushID(i + 20);
        if (ImGui::InvisibleButton("p", ImVec2(kCalcWell, kCalcWell))) {
            session.lockParty(i);
        }
        ImGui::PopID();
        const char* mark = "";
        if (snap && snap->battle.inBattle && i == snap->battle.player.partyIndex) {
            mark = calcStageMark(snap->battle.player.stages);
        }
        drawCalcWell(app, a, slug.c_str(), dim, i == session.partySlot(), false, 0, mark);
        kitStroke(a, ImVec2(a.x + kCalcWell, a.y + kCalcWell),
            kitNavSuite(app, KitTab::Calculator) && app.kitFocus().calcCol == 0 &&
                app.kitFocus().calcRow == i);
    }
    ImGui::SetCursorScreenPos(ImVec2(origin.x, origin.y + 6 * (kCalcWell + 4.f)));
    ImGui::Dummy(ImVec2(kCalcWell, 1));
}

void drawCalcFoeRail(Application& app, CalcSession& session) {
    const CalcPack* pack = session.pack();
    const PackTrainer* t = session.trainer();
    if (!pack || !t) {
        return;
    }
    const GameSnapshot* snap = session.snap();
    const int next = session.nextIn();
    int order[6];
    session.foeOrder(order);
    const ImVec2 origin = ImGui::GetCursorScreenPos();
    for (int vis = 0; vis < 6; ++vis) {
        const int i = order[vis];
        const PackMon* mon = i >= 0 ? trainerMon(*pack, *t, i) : nullptr;
        const char* slug = "";
        if (mon) {
            if (pack->dmgGen == 4 || pack->dmgGen == 5) {
                slug = nationalSpeciesRef(mon->species).slug;
            } else if (const SpeciesRow* row = speciesById(mon->species)) {
                slug = row->slug;
            }
        }
        const ImVec2 a(origin.x, origin.y + vis * (kCalcWell + 4.f));
        ImGui::SetCursorScreenPos(a);
        ImGui::PushID(i >= 0 ? i + 40 : vis + 40);
        if (mon && ImGui::InvisibleButton("f", ImVec2(kCalcWell, kCalcWell))) {
            session.lockFoe(i);
        }
        ImGui::PopID();
        const char* mark = "";
        if (snap && snap->battle.inBattle && i >= 0 && i == snap->battle.foe.partyIndex) {
            mark = calcStageMark(snap->battle.foe.stages);
        }
        drawCalcWell(app, a, slug, i >= 0 && session.fainted(i), i >= 0 && i == session.foeSlot(),
            i >= 0 && i == next, mon ? mon->level : 0, mark);
        kitStroke(a, ImVec2(a.x + kCalcWell, a.y + kCalcWell),
            kitNavSuite(app, KitTab::Calculator) && app.kitFocus().calcCol == 2 &&
                app.kitFocus().calcRow == vis);
    }
    ImGui::SetCursorScreenPos(ImVec2(origin.x, origin.y + 6 * (kCalcWell + 4.f)));
    ImGui::Dummy(ImVec2(56.f, 1));
}

}
