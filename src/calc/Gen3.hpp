#pragma once

#include "calc/Field.hpp"
#include "calc/Move.hpp"
#include "calc/Pokemon.hpp"

namespace emulocke {

struct AdvCtx {
    const Pokemon* atk{};
    const Pokemon* def{};
    const Move* move{};
    const Field* field{};
    uint8_t chart{};
    bool crit{};
    bool physical{};
    uint8_t dmgGen{3};
};

int advBasePower(const AdvCtx& ctx, int hit);
int advAttack(const AdvCtx& ctx);
int advDefense(const AdvCtx& ctx);
int advFinal(int base, const AdvCtx& ctx);
bool advSpread(uint16_t id);
bool advImmune(const Pokemon& def, const Move& move, int typeEff);
int fixedDamage(const Pokemon& atk, const Pokemon& def, const Move& move);

}
