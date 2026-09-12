#pragma once

#include <cstdint>
#include <filesystem>
#include <string_view>
#include <vector>

namespace emulocke {

bool writeLetterboxedPng(const std::vector<uint8_t>& png, const std::filesystem::path& out);
bool writeTitlePlate(std::string_view title, const std::filesystem::path& out);

}
