#pragma once

#include "run/Run.hpp"

#include <filesystem>
#include <optional>
#include <string>

namespace emulocke {

std::string isoTimestamp();
std::optional<Run> readRunMeta(const std::filesystem::path& dir);
bool writeRunMeta(const std::filesystem::path& dir, const Run& run);

}