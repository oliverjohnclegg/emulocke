#pragma once

#include <filesystem>
#include <string>

namespace emulocke {

std::string assetPath(const char* relative);
std::filesystem::path assetsDir();
std::filesystem::path prefDir();
std::string localDataPath(const std::string& filename);
std::filesystem::path runsRoot();
std::filesystem::path romsRoot();

}