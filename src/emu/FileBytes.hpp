#pragma once

#include "emu/FileLimits.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace emulocke {

std::string fopenMode(unsigned mode);
bool writeWholeFile(const std::string& path, const uint8_t* data, std::size_t length);
std::vector<uint8_t> readWholeFile(const std::string& path, std::size_t maxBytes);

}
