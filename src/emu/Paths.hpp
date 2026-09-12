#pragma once

#include <string>

namespace emulocke {

std::string assetPath(const char* relative);
std::string savePathBesideRom(const std::string& romPath);
std::string localDataPath(const std::string& filename);

}