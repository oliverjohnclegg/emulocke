#include "application/BuildId.hpp"

#ifndef EMULOCKE_VERSION
#define EMULOCKE_VERSION "0.0.0"
#endif
#ifndef EMULOCKE_GIT_HASH
#define EMULOCKE_GIT_HASH "unknown"
#endif

namespace emulocke {

ReleaseChannel buildChannel() {
#ifdef EMULOCKE_STABLE
    return ReleaseChannel::Stable;
#else
    return ReleaseChannel::Vanguard;
#endif
}

const char* buildVersion() {
    return EMULOCKE_VERSION;
}

const char* buildHash() {
    return EMULOCKE_GIT_HASH;
}

std::string windowTitle(ReleaseChannel channel, std::string_view version, std::string_view hash,
    std::string_view gameTitle) {
    std::string title = "Emulocke ";
    if (channel == ReleaseChannel::Stable) {
        title += 'v';
        title += version;
    } else {
        title += "VANGUARD [";
        title += hash;
        title += ']';
    }
    if (!gameTitle.empty()) {
        title += " - ";
        constexpr std::string_view pokemon = "Pokemon";
        if (gameTitle.size() >= pokemon.size() && gameTitle.substr(0, pokemon.size()) == pokemon) {
            title += "Pok\u00E9mon";
            title += gameTitle.substr(pokemon.size());
        } else {
            title += gameTitle;
        }
    }
    return title;
}

std::string artifactFileName(ReleaseChannel channel, DistOs os, std::string_view version,
    std::string_view hash) {
    std::string name = "emulocke-";
    if (channel == ReleaseChannel::Stable) {
        name += 'v';
        name += version;
    } else {
        name += "vanguard-";
        name += hash;
    }
    if (os == DistOs::WinX64) {
        name += "-win-x64.exe";
    } else {
        name += "-linux-x64";
    }
    return name;
}

const char* windowIconBmp(ReleaseChannel channel) {
    if (channel == ReleaseChannel::Stable) {
        return "icons/emulocke.bmp";
    }
    return "icons/emulocke-vanguard.bmp";
}

}
