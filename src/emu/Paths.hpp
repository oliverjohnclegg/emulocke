#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace emulocke {

std::string assetPath(const char* relative);
std::string localDataPath(const std::string& filename);
std::filesystem::path prefDir();
std::filesystem::path runsRoot();
std::filesystem::path exeRomsDir();
std::vector<std::filesystem::path> romsScanDirs();
void ensureRomsDir();

}