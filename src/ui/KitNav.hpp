#pragma once

#include "ui/KitFocus.hpp"

namespace emulocke {

class Application;

bool kitPopupOpen();
bool kitModalHold();
bool kitNavHome(Application& app);
bool kitNavSuite(Application& app, KitTab tab);
void handleKitHost(Application& app);

}
