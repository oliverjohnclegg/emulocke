#pragma once

namespace emulocke {

struct TrackerAtlas;
class TrackerLog;

int snapTrackerRow(const TrackerAtlas& atlas, const TrackerLog& log, const char* mapName);

}
