#include "ui/PokemonGather.hpp"

#include "application/Application.hpp"
#include "poke/Dex.hpp"
#include "tracker/Log.hpp"

#include <algorithm>
#include <cstring>
namespace emulocke {
namespace {

bool present(const Mon& mon) {
    return mon.species != 0 && !mon.egg;
}

MonView viewOf(Application& app, const Mon& mon, bool gen3, bool grey) {
    MonView view;
    view.mon = &mon;
    view.ref = app.species(mon.species);
    view.gen3 = gen3;
    view.grey = grey;
    if (view.ref.national) {
        view.national = view.ref.national;
    } else if (!gen3) {
        view.national = mon.species;
    }
    view.ref.national = view.national;
    view.bst = speciesBst(view.national);
    return view;
}

void sortBst(std::vector<MonView>& mons) {
    std::stable_sort(mons.begin(), mons.end(), [](const MonView& a, const MonView& b) {
        return a.bst > b.bst;
    });
}

}  // namespace

void gatherPokemon(Application& app, const GameSnapshot& snap, const TrackerLog& log, bool gen3,
                   MonView party[6], std::vector<MonView>& boxed, std::vector<MonView>& grave,
                   std::vector<Mon>& graveOwned) {
    for (int i = 0; i < 6; ++i) {
        const Mon& mon = snap.party.mons[static_cast<std::size_t>(i)];
        if (!present(mon)) {
            continue;
        }
        if (log.markedDead(mon.personality)) {
            grave.push_back(viewOf(app, mon, gen3, true));
        } else {
            party[i] = viewOf(app, mon, gen3, false);
        }
    }
    for (const PcBox& box : snap.boxes.boxes) {
        for (const Mon& mon : box.mons) {
            if (!present(mon)) {
                continue;
            }
            if (log.markedDead(mon.personality)) {
                grave.push_back(viewOf(app, mon, gen3, true));
            } else {
                boxed.push_back(viewOf(app, mon, gen3, false));
            }
        }
    }
    graveOwned.reserve(log.caughtRows().size());
    for (const auto& [_, row] : log.caughtRows()) {
        if (row.status != EncounterStatus::Dead || (row.species == 0 && row.personality == 0)) {
            continue;
        }
        if (row.personality != 0 && log.markedDead(row.personality)) {
            bool seen = false;
            auto samePid = [&](const MonView& view) {
                return view.mon && view.mon->personality == row.personality;
            };
            for (const MonView& view : grave) {
                if (samePid(view)) {
                    seen = true;
                    break;
                }
            }
            if (seen) {
                continue;
            }
        }
        Mon stored{};
        stored.species = row.species;
        stored.personality = row.personality;
        if (!row.slug.empty()) {
            const std::size_t n = std::min(row.slug.size(), sizeof(stored.speciesName) - 1);
            std::memcpy(stored.speciesName, row.slug.data(), n);
            stored.speciesName[n] = 0;
        }
        graveOwned.push_back(stored);
        grave.push_back(viewOf(app, graveOwned.back(), gen3, true));
    }
    sortBst(boxed);
    sortBst(grave);
}

}