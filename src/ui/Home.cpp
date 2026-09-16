#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "ui/HomeKit.hpp"
#include "ui/RunStrip.hpp"

#include <imgui.h>
#include <vector>

namespace emulocke {

void drawHome(Application& app) {
    ImGui::BeginChild("home", ImVec2(0, 0), ImGuiChildFlags_Borders);
    if (app.runStore().runs().empty()) {
        drawEmptyHome(app);
    } else {
        const std::vector<const Run*> plates = app.runStore().recentLineages();
        applyHomeKit(app, plates);
        drawStartRunRail(app, app.kitFocus().homeIndex == 0);
        int i = 1;
        for (const Run* run : plates) {
            if (drawRunStrip(app, *run, app.kitFocus().homeIndex == i)) {
                app.queueLoadRun(run->id);
            }
            ++i;
        }
    }
    ImGui::EndChild();
}

}
