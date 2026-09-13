#pragma once

#include <string>

namespace emulocke {

class Application;

void drawShell(Application& app);
void drawHome(Application& app);
void drawMenuBar(Application& app);
void drawNewRunModal(Application& app);
void drawLoadingRunModal(Application& app);
std::string drawRunList(Application& app);
void drawHelpPopups(Application& app);

}
