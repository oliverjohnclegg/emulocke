#pragma once

#include "emu/FileLimits.hpp"

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace emulocke {

std::string fopenMode(unsigned mode);
bool writeWholeFile(const std::filesystem::path& path, const uint8_t* data, std::size_t length);
std::vector<uint8_t> readWholeFile(const std::filesystem::path& path, std::size_t maxBytes);

}
