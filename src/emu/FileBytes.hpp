#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace emulocke {

std::string fopenMode(unsigned mode);
bool writeWholeFile(const std::string& path, const uint8_t* data, uint32_t length);
std::vector<uint8_t> readWholeFile(const std::string& path);

}