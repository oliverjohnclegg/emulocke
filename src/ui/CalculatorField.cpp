#include "ui/CalculatorDraw.hpp"

#include "calc/Build.hpp"
#include "ui/Theme.hpp"

#include <imgui.h>

namespace emulocke {

void drawCalcField(Application&, CalcSession& session) {
    const GameSnapshot* snap = session.snap();
    const Field field = fieldFromSnap(snap);
    ImGui::Dummy(ImVec2(0, 6));
    bool any = false;
    if (field.weather == Weather::Sun) {
        calcStamp("SUN");
        any = true;
    } else if (field.weather == Weather::Rain) {
        calcStamp("RAIN");
        any = true;
    } else if (field.weather == Weather::Sand) {
        calcStamp("SAND");
        any = true;
    } else if (field.weather == Weather::Hail) {
        calcStamp("HAIL");
        any = true;
    }
    if (field.reflect) {
        calcStamp("REF");
        any = true;
    }
    if (field.lightScreen) {
        calcStamp("LS");
        any = true;
    }
    if (!any) {
        ImGui::Dummy(ImVec2(0, 1));
    }
}

}