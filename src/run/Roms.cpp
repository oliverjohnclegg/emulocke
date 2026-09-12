#include "run/Roms.hpp"

#include <cctype>
#include <fstream>
#include <map>

namespace emulocke {
namespace {

std::string lowerExt(const std::filesystem::path& path) {
    std::string ext = path.extension().string();
    for (char& c : ext) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return ext;
}

std::string upperCode(const uint8_t* data) {
    std::string code(4, '\0');
    for (int i = 0; i < 4; ++i) {
        code[static_cast<size_t>(i)] = static_cast<char>(std::toupper(static_cast<unsigned char>(data[i])));
    }
    return code;
}

}  // namespace

std::optional<GameId> detectGameId(const uint8_t* data, size_t size, std::string_view ext) {
    const size_t off = ext == ".nds" ? 0x0C : ext == ".gba" ? 0xAC : size;
    if (!data || size < off + 4) {
        return std::nullopt;
    }
    return gameIdFromCode(upperCode(data + off));
}

std::optional<DetectedGame> detectRomFile(const std::filesystem::path& path) {
    const std::string ext = lowerExt(path);
    if (ext != ".gba" && ext != ".nds") {
        return std::nullopt;
    }
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        return std::nullopt;
    }
    uint8_t buf[256]{};
    in.read(reinterpret_cast<char*>(buf), sizeof buf);
    const auto n = static_cast<size_t>(in.gcount());
    const auto id = detectGameId(buf, n, ext);
    if (!id) {
        return std::nullopt;
    }
    return DetectedGame{*id, path.string()};
}

std::vector<DetectedGame> scanRomsDirs(const std::vector<std::filesystem::path>& dirs) {
    struct Best {
        DetectedGame game;
        std::filesystem::file_time_type mtime;
    };
    std::map<GameId, Best> best;
    std::error_code ec;
    for (const auto& dir : dirs) {
        if (!std::filesystem::is_directory(dir, ec)) {
            continue;
        }
        for (const auto& entry : std::filesystem::directory_iterator(dir, ec)) {
            if (!entry.is_regular_file(ec)) {
                continue;
            }
            auto detected = detectRomFile(entry.path());
            if (!detected) {
                continue;
            }
            const auto mtime = entry.last_write_time(ec);
            const auto it = best.find(detected->gameId);
            if (it == best.end() || mtime >= it->second.mtime) {
                best[detected->gameId] = Best{std::move(*detected), mtime};
            }
        }
    }
    std::vector<DetectedGame> out;
    for (int i = 0; i < kGameCount; ++i) {
        const auto it = best.find(gameIdAt(i));
        if (it != best.end()) {
            out.push_back(it->second.game);
        }
    }
    return out;
}

std::optional<std::string> resolveRomPath(const Run& run, const std::vector<DetectedGame>& detected) {
    std::error_code ec;
    if (std::filesystem::is_regular_file(run.romPath, ec)) {
        return run.romPath;
    }
    for (const DetectedGame& game : detected) {
        if (game.gameId == run.gameId) {
            return game.romPath;
        }
    }
    return std::nullopt;
}

}
