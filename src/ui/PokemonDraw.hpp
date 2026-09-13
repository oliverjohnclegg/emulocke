#pragma once

#include "adapter/Snapshot.hpp"
#include "adapter/Species.hpp"

#include <imgui.h>

namespace emulocke {

class BoxSprites;

struct MonView {
    const Mon* mon{};
    SpeciesRef ref{};
    uint16_t national{};
    uint16_t bst{};
    bool gen3{};
};

void drawPartyStrip(BoxSprites& sprites, const MonView* party, int n);
void drawBoxGrid(BoxSprites& sprites, const MonView* mons, int n);
void drawMonWell(BoxSprites& sprites, const MonView& view, ImVec2 size, bool hpBar);
void drawMonHover(const MonView& view);
const char* pokeCopyNotice();

}
