#pragma once

#include "ui/PokemonDraw.hpp"

#include <vector>

namespace emulocke {

class Application;
class TrackerLog;
struct GameSnapshot;

void gatherPokemon(Application& app, const GameSnapshot& snap, const TrackerLog& log, bool gen3,
                   MonView party[6], std::vector<MonView>& boxed, std::vector<MonView>& grave,
                   std::vector<Mon>& graveOwned);

}