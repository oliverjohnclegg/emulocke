#pragma once

#include "calc/Type.hpp"

#include <cstdint>

namespace emulocke {

enum class MoveKind : uint8_t {
    Standard = 0,
    Level = 1,
    DragonRage = 2,
    SonicBoom = 3,
    SuperFang = 4,
    Ohko = 5,
    Multi = 6,
    Double = 7,
    TripleKick = 8,
    Status = 9
};

enum class MoveCat : uint8_t { Physical, Special, Status };

struct Move {
    uint16_t id{};
    const char* name{"-"};
    Type type{Type::Normal};
    int bp{};
    int8_t priority{};
    MoveKind kind{MoveKind::Standard};
    int hits{1};
    bool contact{};
    bool crit{};
    int8_t split{-1};

    MoveCat category(uint8_t typeChart) const {
        if (kind == MoveKind::Status) {
            return MoveCat::Status;
        }
        if (typeChart > 3 && split >= 0) {
            return split == 1 ? MoveCat::Special : MoveCat::Physical;
        }
        return physicalType(type) ? MoveCat::Physical : MoveCat::Special;
    }
};

}
