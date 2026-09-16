#pragma once

#include <string_view>

struct ImVec2;

namespace emulocke {

class Application;

struct SuiteTabs {
    bool tracker;
    bool pokemon;
    bool logs;
    bool calculator;
    bool cheats;
};

inline SuiteTabs suiteTabs(std::string_view activeRunId, bool previewTracker, bool previewCalc,
    bool allowCheats = true) {
    const bool runOn = !activeRunId.empty();
    return SuiteTabs{
        runOn || previewTracker,
        runOn || previewTracker,
        true,
        runOn || previewCalc,
        runOn && allowCheats,
    };
}

void drawSuite(Application& app, ImVec2 size);

}
