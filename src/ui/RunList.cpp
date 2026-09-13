#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "ui/RunStrip.hpp"

#include <imgui.h>
#include <string>

namespace emulocke {

std::string drawRunList(Application& app, const char* idPrefix, bool showNewAttempt) {
    std::string clicked;
    for (const Run* run : app.runStore().recentLineages()) {
        if (drawRunStrip(app, *run, idPrefix, showNewAttempt)) {
            clicked = run->id;
        }
    }
    return clicked;
}

}
