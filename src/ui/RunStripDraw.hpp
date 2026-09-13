#pragma once

#include "adapter/Snapshot.hpp"
#include "run/Catalog.hpp"

#include <imgui.h>

namespace emulocke {

class Application;

inline constexpr float kRunArtW = 128.f;
inline constexpr float kRunArtH = 96.f;
inline constexpr float kRunPad = 8.f;
inline constexpr float kRunPlus = 22.f;
inline constexpr float kRunStripH = kRunArtH + kRunPad * 2.f;

void drawRunArt(Application& app, const CatalogTitle* title, ImVec2 p);
void drawRunParty(Application& app, const Party& party, ImVec2 p);

}
