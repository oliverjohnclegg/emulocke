#pragma once

#include "tracker/Log.hpp"

#include <cstdint>

namespace emulocke {

bool drawEncounterStatus(EncounterStatus status);
bool drawBossStatus(bool defeated, uint8_t cap);

}
