#pragma once

#include "calc/Result.hpp"

#include <cstdint>

namespace emulocke {

enum class KoBand : uint8_t {
    None,
    RollTwoHko,
    TwoHko,
    CritOhko,
    RollOhko,
    Ohko,
};

KoBand koBand(const DamageResult& dmg, const DamageResult* crit, int hp);

}
