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

std::string savePathBesideRom(const std::string& romPath) {
    return std::filesystem::path(romPath).replace_extension(".sav").string();
}

std::string localDataPath(const std::string& filename) {
    std::filesystem::path dir;
    if (char* pref = SDL_GetPrefPath("emulocke", "emulocke")) {
        dir = pref;
        SDL_free(pref);
    } else {
        dir = std::filesystem::current_path();
    }
    std::error_code ec;
    std::filesystem::create_directories(dir, ec);
    return (dir / filename).string();
}

}