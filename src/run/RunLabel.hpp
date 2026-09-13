#pragma once

#include "run/Run.hpp"

#include <cstdint>
#include <string>

namespace emulocke {

std::string runHeadline(const Run& run);
std::string formatPlayClock(uint64_t ms);

}
