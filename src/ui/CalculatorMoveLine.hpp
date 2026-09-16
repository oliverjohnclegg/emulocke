#pragma once

#include "calc/Field.hpp"
#include "calc/Pokemon.hpp"
#include "calc/Result.hpp"

namespace emulocke {

class CalcSession;

struct CalcMoveLine {
    const char* name;
    bool blank;
    bool ohko;
    int slot;
    int use;
    int pmin;
    int pmax;
};

int collectCalcMoves(uint8_t dmgGen, uint8_t chart, const Pokemon& atk, const Pokemon& def,
    const uint16_t* moves, const Field& field, const int* pct, bool crit, CalcMoveLine* out);
void sortCalcMoves(CalcMoveLine* lines, int n, bool byUse);
void drawCalcMoveRow(const CalcMoveLine& line, bool right, CalcSession& session, bool focus, bool act);

}
