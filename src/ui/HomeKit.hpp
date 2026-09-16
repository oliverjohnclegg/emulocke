#pragma once

#include <vector>

namespace emulocke {

class Application;
struct Run;

void applyHomeKit(Application& app, const std::vector<const Run*>& plates);
void drawEmptyHome(Application& app);
void drawStartRunRail(Application& app, bool focus);

}
