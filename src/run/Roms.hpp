#pragma once

#include "run/GameId.hpp"
#include "run/Run.hpp"

#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace emulocke {

struct DetectedGame {
    GameId gameId{GameId::Ruby};
    std::string romPath;
};

std::optional<GameId> detectGameId(const uint8_t* data, size_t size, std::string_view ext);
std::optional<DetectedGame> detectRomFile(const std::filesystem::path& path);
std::vector<DetectedGame> scanRomsDirs(const std::vector<std::filesystem::path>& dirs);
std::optional<std::string> resolveRomPath(const Run& run, const std::vector<DetectedGame>& detected);

}
