#pragma once

#include "calc/Field.hpp"
#include "calc/Pokemon.hpp"
#include "calc/Session.hpp"

namespace emulocke {

class Application;

void calcStampBlock(const char* const* labels, int n, bool right);
bool calcChip(const char* label, bool on, float width = 0.f);
float calcChipWidth(const char* label);
bool calcCritMark(bool on);
float calcCritMarkWidth();
void calcAlignRight(float width);
void calcAlignCenter(float width);
void calcPixelBar(int hp, int maxHp);
float calcFoeHpWidth(int hp, int maxHp);
void calcFoeHp(int hp, int maxHp);
void drawCalcSearch(Application& app, CalcSession& session);
void drawCalcPartyRail(Application& app, CalcSession& session);
void drawCalcFoeRail(Application& app, CalcSession& session);
void drawCalcSideHead(const char* name, const Pokemon& mon, bool right);
void drawCalcCrits(bool& ours, bool& theirs, float spineX, float abY, int focus, bool act);
void drawCalcMatchup(Application& app, CalcSession& session);
void drawCalcField(Application& app, CalcSession& session);
void drawCalcMoveCol(uint8_t dmgGen, uint8_t chart, const Pokemon& atk, const Pokemon& def,
    const uint16_t* moves, const Field& field, const int* pct, bool crit, bool right,
    CalcSession& session, int focusRow, bool act);
void drawCalcKo(CalcSession& session, uint8_t dmgGen, uint8_t chart, const Pokemon& player,
    const Pokemon& foe, const uint16_t* ours, const uint16_t* theirs, const Field& intoFoe,
    const Field& intoUs);

}
