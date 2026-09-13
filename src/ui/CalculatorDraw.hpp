#pragma once

#include "calc/Field.hpp"
#include "calc/Pokemon.hpp"
#include "calc/Session.hpp"

namespace emulocke {

class Application;

void calcStamp(const char* label);
void calcAlignRight(float width);
void drawCalcSearch(Application& app, CalcSession& session);
void drawCalcPartyRail(Application& app, CalcSession& session);
void drawCalcFoeRail(Application& app, CalcSession& session);
void drawCalcSideHead(const char* name, const Pokemon& mon, bool right);
void drawCalcMatchup(Application& app, CalcSession& session);
void drawCalcField(Application& app, CalcSession& session);
void drawCalcMoveCol(uint8_t dmgGen, uint8_t chart, const Pokemon& atk, const Pokemon& def,
    const uint16_t* moves, const Field& field, const int* pct, bool right);

}
