#include "calc/Dex.hpp"
#include "calc/Session.hpp"
#include "tracker/Atlas.hpp"

#include <cctype>
#include <cstring>
#include <vector>

namespace emulocke {
namespace {

char fold(char c) {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
}

bool same(const char* a, const char* b) {
    if (!a || !b) {
        return false;
    }
    while (*a && *b) {
        if (fold(*a++) != fold(*b++)) {
            return false;
        }
    }
    return *a == 0 && *b == 0;
}

void stem(const char* s, char* out, int cap) {
    int n = 0;
    while (s && *s && *s != '-' && n + 1 < cap) {
        out[n++] = fold(*s++);
    }
    out[n] = 0;
}

bool slugHit(const char* want, const char* have) {
    if (same(want, have)) {
        return true;
    }
    char w[32];
    char h[32];
    stem(want, w, 32);
    stem(have, h, 32);
    return w[0] && same(w, h);
}

const char* monSlug(const CalcPack& pack, uint16_t species) {
    if (pack.dex && species < static_cast<uint16_t>(pack.dexCount) && pack.dex[species].slug) {
        return pack.dex[species].slug;
    }
    if (const SpeciesRow* nat = nationalDexRow(species)) {
        return nat->slug;
    }
    return "";
}

bool stopLocked(const TrackerStop& stop) {
    if (!stop.team) {
        return false;
    }
    for (uint8_t i = 0; i < stop.teamCount; ++i) {
        if (stop.team[i].starterLock) {
            return true;
        }
    }
    return false;
}

const TrackerStop* lockedStop(const TrackerAtlas& atlas, const PackTrainer& trainer) {
    for (const TrackerStop& stop : atlas.stops) {
        if (stop.kind != TrackerStopKind::Boss || !stopLocked(stop)) {
            continue;
        }
        if (!same(stop.name, trainer.name)) {
            continue;
        }
        if (trainer.location[0] && stop.locale[0] && !same(stop.locale, trainer.location)) {
            continue;
        }
        return &stop;
    }
    return nullptr;
}

bool partyHasWant(const CalcPack& pack, const PackTrainer& trainer, const TrackerStop& stop,
    uint16_t starter) {
    const char* want[6]{};
    const int n = bossTeamSlugs(stop, starter, want, 6);
    if (n <= 0) {
        return true;
    }
    const char* have[6]{};
    int h = 0;
    for (int i = 0; i < trainer.count && h < 6; ++i) {
        const PackMon* mon = trainerMon(pack, trainer, i);
        if (!mon) {
            continue;
        }
        have[h++] = monSlug(pack, mon->species);
    }
    for (int i = 0; i < n; ++i) {
        bool hit = false;
        for (int j = 0; j < h; ++j) {
            if (slugHit(want[i], have[j])) {
                hit = true;
                break;
            }
        }
        if (!hit) {
            return false;
        }
    }
    return true;
}

}  // namespace

void CalcSession::keepStarterHits() {
    if (!pack_ || !atlas_ || starter_ == 0 || trainers_.empty()) {
        return;
    }
    std::vector<const PackTrainer*> kept;
    kept.reserve(trainers_.size());
    for (const PackTrainer* t : trainers_) {
        if (!t) {
            continue;
        }
        const TrackerStop* stop = lockedStop(*atlas_, *t);
        if (!stop || partyHasWant(*pack_, *t, *stop, starter_)) {
            kept.push_back(t);
        }
    }
    trainers_.swap(kept);
}

}
