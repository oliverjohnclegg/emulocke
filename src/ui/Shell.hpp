#pragma once

#include <string>

namespace emulocke {

class Application;

void drawShell(Application& app);
void drawHome(Application& app);
void drawMenuBar(Application& app);
void drawNewRunModal(Application& app);
void drawLoadingRunModal(Application& app);
void drawNewAttemptConfirm(Application& app);
void drawDeleteRunConfirm(Application& app);
std::string drawRunList(Application& app);
void drawHelpPopups(Application& app);
void drawControlsModal(Application& app);
bool controlsCapturing();

}
