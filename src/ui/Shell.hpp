#pragma once

#include <string>

namespace emulocke {

class Application;

void drawShell(Application& app);
void drawHome(Application& app);
void drawMenuBar(Application& app);
void drawNewRunModal(Application& app);
void drawLoadRunModal(Application& app);
std::string drawGroupedRunList(Application& app, const char* idPrefix, bool showNewAttempt);
void drawHelpPopups(Application& app);
void drawNewRunModal(Application& app);
void drawLoadRunModal(Application& app);
std::string drawGroupedRunList(Application& app, const char* idPrefix, bool showNewAttempt);

}