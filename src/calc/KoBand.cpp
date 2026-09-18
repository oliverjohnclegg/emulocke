#include "calc/KoBand.hpp"

namespace emulocke {

KoBand koBand(const DamageResult& dmg, const DamageResult* crit, int hp) {
    if (dmg.immune || dmg.max <= 0 || hp <= 0) {
        return KoBand::None;
    }
    if (dmg.min >= hp) {
        return KoBand::Ohko;
    }
    if (dmg.max >= hp) {
        return KoBand::RollOhko;
    }
    if (crit && !crit->immune && crit->max >= hp) {
        return KoBand::CritOhko;
    }
    if (2 * dmg.min >= hp) {
        return KoBand::TwoHko;
    }
    if (2 * dmg.max >= hp) {
        return KoBand::RollTwoHko;
    }
    return KoBand::None;
}

}
