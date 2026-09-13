#pragma once

#include "calc/Field.hpp"
#include "calc/Pokemon.hpp"

namespace emulocke {

struct CalcMoveLine {
    const char* name;
    bool blank;
    bool ohko;
    bool crit;
    bool canCrit;
    int slot;
    int use;
    int pmin;
    int pmax;
};

int collectCalcMoves(uint8_t dmgGen, uint8_t chart, const Pokemon& atk, const Pokemon& def,
    const uint16_t* moves, const Field& field, const int* pct, const bool* crits, bool intoUs,
    CalcMoveLine* out);
void sortCalcMoves(CalcMoveLine* lines, int n, bool byUse);
void drawCalcMoveDmg(const CalcMoveLine& line, bool hugRight);
void drawCalcMoveName(const CalcMoveLine& line, bool right);

}