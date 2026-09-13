#pragma once

#include "tracker/Atlas.hpp"

struct ImVec2;

namespace emulocke {

class Application;
class BoxSprites;
class TrackerLog;
struct SpeciesRef;

inline constexpr float kTrackerRowH = 28.f;

void drawTracker(Application& app);
void drawEncounterRow(const TrackerStop& stop, const SpeciesRef& species, BoxSprites& sprites, bool editing,
                       bool grabFocus, char* edit, int editCap, bool& commit, bool& startEdit);
void drawBossRow(const TrackerStop& stop, uint16_t starter, bool defeated, BoxSprites& sprites, bool& toggle);

}