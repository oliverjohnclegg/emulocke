#pragma once

#include "calc/Field.hpp"
#include "calc/KoBand.hpp"
#include "calc/Move.hpp"
#include "calc/Pack.hpp"
#include "calc/Pokemon.hpp"
#include "calc/Result.hpp"

#include <imgui.h>

namespace emulocke {

class CalcSession;

struct CalcMoveLine {
    const char* name;
    bool blank;
    KoBand band;
    int slot;
    int use;
    int pmin;
    int pmax;
};

struct CalcHit {
    DamageResult dmg;
    KoBand band;
};

CalcHit evalCalcHit(uint8_t dmgGen, uint8_t chart, const Pokemon& atk, const Pokemon& def, Move mv,
    const Field& field, bool crit);
int collectCalcMoves(uint8_t dmgGen, uint8_t chart, const CalcPack* pack, const Pokemon& atk,
    const Pokemon& def, const uint16_t* moves, const Field& field, const int* pct, bool crit,
    CalcMoveLine* out);
void sortCalcMoves(CalcMoveLine* lines, int n, bool byUse);
ImU32 calcKoInk(KoBand band);
void drawCalcMoveRow(const CalcMoveLine& line, bool right, CalcSession& session, bool focus, bool act);

}
