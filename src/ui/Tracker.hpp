#pragma once

#include "tracker/Atlas.hpp"
#include "tracker/Log.hpp"

struct ImVec2;

namespace emulocke {

class Application;
class BoxSprites;
struct SpeciesRef;

inline constexpr int kBoxSpriteW = 32;
inline constexpr int kBoxSpriteH = 24;
inline constexpr float kTrackerRowH = 28.f;
inline constexpr float kTrackerKind = 22.f;
inline constexpr float kTrackerKindH = 18.f;
inline constexpr float kTrackerStatus = 18.f;

void drawTracker(Application& app);
void applyTrackerKit(Application& app, const TrackerAtlas& atlas, TrackerLog& log);
void drawEncounterRow(const TrackerStop& stop, EncounterStatus status, const SpeciesRef& species,
                      BoxSprites& sprites, bool& cycleStatus, bool focus);
void drawBossRow(const TrackerStop& stop, const char* const* slugs, const char* const* tips, int n, bool defeated,
                 BoxSprites& sprites, bool& toggle, bool focus);

}