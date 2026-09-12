#include "emu/Paths.hpp"

#include <SDL3/SDL.h>
#include <filesystem>

namespace emulocke {

std::string assetPath(const char* relative) {
    std::string suffix = std::string("assets/") + relative;
    if (const char* base = SDL_GetBasePath()) {
        std::string p = std::string(base) + suffix;
        if (std::filesystem::exists(p)) {
            return p;
        }
    }
    if (std::filesystem::exists(suffix)) {
        return suffix;
    }
    return suffix;
}

std::filesystem::path prefDir() {
    std::filesystem::path dir;
    if (char* pref = SDL_GetPrefPath("emulocke", "emulocke")) {
        dir = pref;
        SDL_free(pref);
    } else {
        dir = std::filesystem::current_path();
    }
    std::error_code ec;
    std::filesystem::create_directories(dir, ec);
    return dir;
}

std::string localDataPath(const std::string& filename) {
    return (prefDir() / filename).string();
}

std::filesystem::path runsRoot() {
    return prefDir() / "runs";
}

std::filesystem::path exeRomsDir() {
    if (const char* base = SDL_GetBasePath()) {
        return std::filesystem::path(base) / "roms";
    }
    return std::filesystem::current_path() / "roms";
}

std::vector<std::filesystem::path> romsScanDirs() {
    return {exeRomsDir(), std::filesystem::current_path() / "roms"};
}

void ensureRomsDir() {
    std::error_code ec;
    std::filesystem::create_directories(exeRomsDir(), ec);
}

}