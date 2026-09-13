#pragma once

#include "tracker/Atlas.hpp"

struct ImVec2;

namespace emulocke {

class Application;
class BoxSprites;
class TrackerLog;
struct SpeciesRef;

inline constexpr int kBoxSpriteW = 64;
inline constexpr int kBoxSpriteH = 48;
inline constexpr float kTrackerRowH = 56.f;

void drawTracker(Application& app);
void drawEncounterRow(const TrackerStop& stop, const SpeciesRef& species, BoxSprites& sprites, bool editing,
                       bool grabFocus, char* edit, int editCap, bool& commit, bool& startEdit);
void drawBossRow(const TrackerStop& stop, uint16_t starter, bool defeated, BoxSprites& sprites, bool& toggle);

}