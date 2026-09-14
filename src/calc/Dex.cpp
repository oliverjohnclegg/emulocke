#include "calc/Dex.hpp"

namespace emulocke {
namespace {

constexpr SpeciesRow kSpecies[] = {
#include "calc/data/Species.inc"
};

constexpr MoveRow kMoves[] = {
#include "calc/data/Moves.inc"
};

}  // namespace

const SpeciesRow* speciesById(uint16_t id) {
    if (id >= sizeof(kSpecies) / sizeof(kSpecies[0])) {
        return nullptr;
    }
    const SpeciesRow& row = kSpecies[id];
    if (!row.slug) {
        return nullptr;
    }
    return &row;
}

const MoveRow* moveById(uint16_t id) {
    if (id >= sizeof(kMoves) / sizeof(kMoves[0])) {
        return nullptr;
    }
    const MoveRow& row = kMoves[id];
    if (!row.name) {
        return nullptr;
    }
    return &row;
}

Move moveFromRow(const MoveRow& row) {
    Move m;
    m.id = row.id;
    m.name = row.name;
    m.type = static_cast<Type>(row.type);
    m.bp = row.bp;
    m.priority = row.priority;
    m.kind = static_cast<MoveKind>(row.kind);
    m.hits = row.hits < 1 ? 1 : row.hits;
    m.contact = row.contact != 0;
    if (row.bp == 0 && row.kind == 0) {
        m.kind = MoveKind::Status;
    }
    return m;
}

}
