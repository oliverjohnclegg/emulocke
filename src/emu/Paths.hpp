#pragma once

#include <filesystem>
#include <string>
#include <string_view>

namespace emulocke {

std::string assetPath(const char* relative);
std::filesystem::path assetsDir();
std::filesystem::path prefDir();
std::filesystem::path pathFromUtf8(std::string_view utf8);
std::string localDataPath(const std::string& filename);
std::filesystem::path runsRoot();
std::filesystem::path romsRoot();

}