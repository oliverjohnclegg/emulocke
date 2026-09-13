#include "calc/Type.hpp"

namespace emulocke {
namespace {

#include "calc/data/TypeChart.inc"

const char* kNames[] = {"Normal", "Fighting", "Flying", "Poison", "Ground", "Rock", "Bug",
    "Ghost", "Steel", "???", "Fire", "Water", "Grass", "Electric", "Psychic", "Ice", "Dragon",
    "Dark", "Fairy"};

}  // namespace

int typeMul(uint8_t chart, Type atk, Type def) {
    const int a = static_cast<int>(atk);
    const int d = static_cast<int>(def);
    if (a < 0 || a > 18 || d < 0 || d > 18) {
        return 10;
    }
    if (chart >= 6) {
        return kChartXy[a][d];
    }
    if (a == 18 || d == 18) {
        return 10;
    }
    return kChartAdv[a][d];
}

int typeEff(uint8_t chart, Type atk, Type t1, Type t2, bool foresight) {
    auto one = [&](Type t) {
        if (t == Type::None) {
            return 10;
        }
        const int m = typeMul(chart, atk, t);
        if (foresight && m == 0 && t == Type::Ghost &&
            (atk == Type::Normal || atk == Type::Fighting)) {
            return 10;
        }
        return m;
    };
    const int a = one(t1);
    if (t2 == Type::None || t2 == t1) {
        return a;
    }
    return a * one(t2) / 10;
}

bool physicalType(Type type) {
    return static_cast<uint8_t>(type) <= static_cast<uint8_t>(Type::Steel);
}

const char* typeName(Type type) {
    const int i = static_cast<int>(type);
    if (i < 0 || i > 18) {
        return "???";
    }
    return kNames[i];
}

}
