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
    bool grey{};
};

void drawPartyStrip(BoxSprites& sprites, const MonView* party, int n, int focus, bool act);
void drawBoxGrid(BoxSprites& sprites, const MonView* mons, int n, int indexBase, int focus, bool act);
void drawRosterPane(BoxSprites& sprites, const MonView* mons, int n, const char* title, const char* empty,
                    int indexBase, int focus, bool act);
void drawMonWell(BoxSprites& sprites, const MonView& view, ImVec2 size, bool hpBar, bool focused, bool act);
void drawMonHover(const MonView& view);

}