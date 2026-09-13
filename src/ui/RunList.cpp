#include "ui/Shell.hpp"

#include "application/Application.hpp"
#include "ui/RunStrip.hpp"

#include <string>

namespace emulocke {

std::string drawRunList(Application& app) {
    std::string clicked;
    for (const Run* run : app.runStore().recentLineages()) {
        if (drawRunStrip(app, *run)) {
            clicked = run->id;
        }
    }
    return clicked;
}

}
