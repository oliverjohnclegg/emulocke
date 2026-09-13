#include "cart/GameIndex.hpp"

#include "poke/SpriteIndex.hpp"

#include <string>

namespace emulocke {

std::string gameArtSlug(std::string_view catalogSlug) {
    const std::string key = normalizeSlug(catalogSlug);
    if (key.starts_with("black2")) {
        return "black-2";
    }
    if (key.starts_with("white2")) {
        return "white-2";
    }
    if (key.starts_with("blaze-black")) {
        return "blaze-black";
    }
    if (key.starts_with("volt-white-2")) {
        return "volt-white-2";
    }
    if (key.starts_with("volt-white")) {
        return "volt-white";
    }
    if (key.starts_with("fire-red-omega")) {
        return "fire-red-omega";
    }
    if (key.starts_with("sacred-gold")) {
        return "sacred-gold";
    }
    if (key.starts_with("platinum-kaizo")) {
        return "platinum-kaizo";
    }
    if (key.starts_with("renegade-platinum")) {
        return "renegade-platinum";
    }
    if (key.starts_with("radical-red")) {
        return "radical-red";
    }
    if (key.starts_with("unbound")) {
        return "unbound";
    }
    if (key.starts_with("run-and-bun")) {
        return "run-and-bun";
    }
    if (key.starts_with("inclement-emerald")) {
        return "inclement-emerald";
    }
    if (key.starts_with("emerald-kaizo")) {
        return "emerald-kaizo";
    }
    const auto us = key.find("-us");
    if (us != std::string::npos) {
        return key.substr(0, us);
    }
    return key;
}

}
