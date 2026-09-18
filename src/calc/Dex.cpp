#include "calc/Dex.hpp"

#include "calc/Pack.hpp"

#include <cctype>
#include <cstring>

namespace emulocke {
namespace {

constexpr SpeciesRow kSpecies[] = {
#include "calc/data/Species.inc"
};

constexpr SpeciesRow kNat[] = {
#include "calc/data/SpeciesNat.inc"
};

constexpr MoveRow kMoves[] = {
#include "calc/data/Moves.inc"
#include "calc/data/MovesNat.inc"
};

constexpr uint8_t kSplit[] = {
#include "calc/data/MovesSplit.inc"
};

bool sameToken(const char* a, const char* b) {
    if (!a || !b) {
        return false;
    }
    while (*a && *b) {
        char ca = *a;
        char cb = *b;
        if (ca == '_' || ca == '-' || ca == ' ' || ca == '.') {
            ++a;
            continue;
        }
        if (cb == '_' || cb == '-' || cb == ' ' || cb == '.') {
            ++b;
            continue;
        }
        ca = static_cast<char>(std::tolower(static_cast<unsigned char>(ca)));
        cb = static_cast<char>(std::tolower(static_cast<unsigned char>(cb)));
        if (ca != cb) {
            return false;
        }
        ++a;
        ++b;
    }
    return *a == 0 && *b == 0;
}

const SpeciesRow* lookup(const SpeciesRow* rows, int n, uint16_t id) {
    if (id >= static_cast<uint16_t>(n)) {
        return nullptr;
    }
    const SpeciesRow& row = rows[id];
    if (!row.slug) {
        return nullptr;
    }
    return &row;
}

}  // namespace

const SpeciesRow* speciesById(uint16_t id) {
    if (const SpeciesRow* row = lookup(kSpecies, static_cast<int>(sizeof(kSpecies) / sizeof(kSpecies[0])), id)) {
        return row;
    }
    return lookup(kNat, static_cast<int>(sizeof(kNat) / sizeof(kNat[0])), id);
}

const SpeciesRow* nationalDexRow(uint16_t id) {
    return lookup(kNat, static_cast<int>(sizeof(kNat) / sizeof(kNat[0])), id);
}

const SpeciesRow* speciesByName(const char* name) {
    if (!name || !name[0]) {
        return nullptr;
    }
    const int natN = static_cast<int>(sizeof(kNat) / sizeof(kNat[0]));
    for (int i = 1; i < natN; ++i) {
        if (kNat[i].slug && sameToken(kNat[i].slug, name)) {
            return &kNat[i];
        }
    }
    const int n = static_cast<int>(sizeof(kSpecies) / sizeof(kSpecies[0]));
    for (int i = 1; i < n; ++i) {
        if (kSpecies[i].slug && sameToken(kSpecies[i].slug, name)) {
            return &kSpecies[i];
        }
    }
    return nullptr;
}

const SpeciesRow* nationalDex() {
    return kNat;
}

int nationalDexCount() {
    return static_cast<int>(sizeof(kNat) / sizeof(kNat[0]));
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
    m.kind = static_cast<MoveKind>(row.kind);
    m.hits = row.hits < 1 ? 1 : row.hits;
    m.contact = row.contact != 0;
    m.bp = row.bp;
    m.priority = row.priority;
    if (row.split != 255) {
        m.split = static_cast<int8_t>(row.split);
    } else if (row.id < sizeof(kSplit) / sizeof(kSplit[0]) && kSplit[row.id] != 255) {
        m.split = static_cast<int8_t>(kSplit[row.id]);
    }
    if (row.bp == 0 && row.kind == 0) {
        m.kind = MoveKind::Status;
    }
    return m;
}

Move packedMove(const CalcPack* pack, uint16_t id) {
    const MoveRow* row = moveById(id);
    if (!row) {
        return {};
    }
    Move m = moveFromRow(*row);
    if (!pack) {
        return m;
    }
    for (int i = 0; i < pack->moveFixCount; ++i) {
        const MoveFix& fix = pack->moveFixes[i];
        if (fix.id != id) {
            continue;
        }
        m.bp = fix.bp;
        if (fix.type != 255) {
            m.type = static_cast<Type>(fix.type);
        }
        break;
    }
    return m;
}

}
