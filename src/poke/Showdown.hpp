#pragma once

#include "adapter/Snapshot.hpp"
#include "adapter/Species.hpp"

#include <string>

namespace emulocke {

std::string exportSet(const Mon& mon, SpeciesRef ref, bool gen3);
void appendSet(std::string& team, const Mon& mon, SpeciesRef ref, bool gen3);

}
