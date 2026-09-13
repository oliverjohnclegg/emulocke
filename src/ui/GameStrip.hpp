#pragma once

#include "run/Catalog.hpp"

#include <imgui.h>
#include <string>

namespace emulocke {

class Application;

constexpr float kTitleArtW = 64.f;
constexpr float kTitleArtH = 48.f;
constexpr float kTitleStripH = 56.f;

void drawTitleStrip(Application& app, const CatalogTitle& title, ImVec2 min, ImVec2 max, bool ready);
bool drawTitleStripRow(Application& app, const CatalogTitle& title, std::string& catalogUuid);

}
