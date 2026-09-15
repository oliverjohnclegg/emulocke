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

inline SuiteTabs suiteTabs(std::string_view activeRunId, bool previewTracker, bool previewCalc) {
    const bool runOn = !activeRunId.empty();
    return SuiteTabs{
        runOn || previewTracker,
        runOn,
        true,
        runOn || previewCalc,
        runOn,
    };
}

void drawSuite(Application& app, ImVec2 size);

}
