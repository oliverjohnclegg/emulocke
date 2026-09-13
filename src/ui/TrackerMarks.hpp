#pragma once

#include "tracker/Atlas.hpp"

struct SDL_Texture;

namespace emulocke {

void paintTrackerRow(float w);
void drawKindMark(TrackerStopKind kind);
void drawStruckLabel(const char* text, bool struck);
void drawBoxSprite(SDL_Texture* tex, const char* tip, bool grey);

}
