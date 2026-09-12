#pragma once

#include <string>

struct ImFont;

namespace emulocke {

void drawSuite(ImFont* display, ImFont* body, const std::string& status, const char* romName);

}
