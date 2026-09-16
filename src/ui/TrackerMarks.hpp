#pragma once

#include "tracker/Atlas.hpp"

struct SDL_Texture;

namespace emulocke {

void paintTrackerRow(float w, bool focus = false);
void drawKindMark(const TrackerStop& stop);
void drawStruckLabel(const char* text, bool struck);
void drawBoxSprite(SDL_Texture* tex, const char* tip, bool grey);

}
