#include "emu/Paths.hpp"

#include <SDL3/SDL.h>
#include <filesystem>
#include <string>
#include <string_view>

namespace emulocke {

std::string assetPath(const char* relative) {
    return (assetsDir() / relative).string();
}

std::filesystem::path assetsDir() {
    if (const char* base = SDL_GetBasePath()) {
        const std::filesystem::path dir = pathFromUtf8(base) / "assets";
        if (std::filesystem::exists(dir)) {
            return dir;
        }
    }
    if (std::filesystem::exists("assets")) {
        return "assets";
    }
    return "assets";
}

std::filesystem::path prefDir() {
    std::filesystem::path dir;
    if (char* pref = SDL_GetPrefPath("emulocke", "emulocke")) {
        dir = pathFromUtf8(pref);
        SDL_free(pref);
    } else {
        dir = std::filesystem::current_path();
    }
    std::error_code ec;
    std::filesystem::create_directories(dir, ec);
    return dir;
}

std::filesystem::path pathFromUtf8(std::string_view utf8) {
#ifdef _WIN32
    return {std::u8string(utf8.begin(), utf8.end())};
#else
    return {utf8};
#endif
}

std::string localDataPath(const std::string& filename) {
    return (prefDir() / filename).string();
}

std::filesystem::path runsRoot() {
    return prefDir() / "runs";
}

std::filesystem::path romsRoot() {
    return prefDir() / "roms";
}

}