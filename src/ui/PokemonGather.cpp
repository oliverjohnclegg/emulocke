#include "ui/PokemonGather.hpp"

#include "application/Application.hpp"
#include "poke/Dex.hpp"
#include "poke/SpriteIndex.hpp"
#include "tracker/Log.hpp"

#include <algorithm>

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
    } else if (const auto id = pokemonId(speciesSlug(mon.speciesName))) {
        view.national = *id;
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
                   MonView party[6], std::vector<MonView>& boxed, std::vector<MonView>& grave) {
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
    sortBst(boxed);
    sortBst(grave);
}

}