#pragma once

#include "calc/Session.hpp"

struct ImVec2;

namespace emulocke {

class Application;

void drawCalcSearch(Application& app, CalcSession& session);
void drawCalcStrips(Application& app, CalcSession& session);
void drawCalcMatchup(Application& app, CalcSession& session);

}
