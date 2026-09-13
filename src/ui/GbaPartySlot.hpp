#pragma once

#include "adapter/Snapshot.hpp"

#include <imgui.h>

namespace emulocke {

class Application;

void drawPartySlot(Application& app, const Mon& mon, int slot, ImVec2 wellA, ImVec2 wellB, ImVec2 trackA,
    ImVec2 trackB);

}
