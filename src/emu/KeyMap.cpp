#include "emu/KeyMap.hpp"

#include <SDL3/SDL.h>

namespace emulocke {
namespace {

const char* kIds[kKeySlotCount] = {
    "up", "down", "left", "right", "b", "a", "y", "x", "l", "r", "start", "select"};
const char* kLabels[kKeySlotCount] = {
    "Up", "Down", "Left", "Right", "B", "A", "Y", "X", "L", "R", "START", "SELECT"};

struct Alias {
    const char* name;
    SDL_Scancode code;
};

const Alias kAliases[] = {
    {"Enter", SDL_SCANCODE_RETURN},
    {"RShift", SDL_SCANCODE_RSHIFT},
    {"LShift", SDL_SCANCODE_LSHIFT},
    {"LCtrl", SDL_SCANCODE_LCTRL},
    {"RCtrl", SDL_SCANCODE_RCTRL},
    {"LAlt", SDL_SCANCODE_LALT},
    {"RAlt", SDL_SCANCODE_RALT},
    {"Space", SDL_SCANCODE_SPACE},
};

}  // namespace

const char* keySlotId(int slot) {
    return (slot < 0 || slot >= kKeySlotCount) ? "" : kIds[slot];
}

const char* keySlotLabel(int slot) {
    return (slot < 0 || slot >= kKeySlotCount) ? "" : kLabels[slot];
}

int keySlotFromId(const std::string& id) {
    for (int i = 0; i < kKeySlotCount; ++i) {
        if (id == kIds[i]) {
            return i;
        }
    }
    return -1;
}

const char* scancodeLabel(SDL_Scancode code) {
    for (const Alias& alias : kAliases) {
        if (alias.code == code) {
            return alias.name;
        }
    }
    const char* name = SDL_GetScancodeName(code);
    return (name && name[0]) ? name : "None";
}

SDL_Scancode parseScancode(const std::string& value) {
    for (const Alias& alias : kAliases) {
        if (value == alias.name) {
            return alias.code;
        }
    }
    return SDL_GetScancodeFromName(value.c_str());
}

bool reservedScancode(SDL_Scancode code) {
    return code == SDL_SCANCODE_UNKNOWN || code == SDL_SCANCODE_ESCAPE || code == SDL_SCANCODE_TAB ||
        code == SDL_SCANCODE_F8;
}

bool bindKey(KeyMap& map, int slot, SDL_Scancode code) {
    if (slot < 0 || slot >= kKeySlotCount || reservedScancode(code)) {
        return false;
    }
    const SDL_Scancode old = map.codes[slot];
    for (int i = 0; i < kKeySlotCount; ++i) {
        if (i != slot && map.codes[i] == code) {
            map.codes[i] = old;
            break;
        }
    }
    map.codes[slot] = code;
    return true;
}

uint32_t keyboardButtons(const bool* keyboard, const KeyMap& map) {
    uint32_t pressed = 0;
    if (!keyboard) {
        return 0;
    }
    for (int i = 0; i < kKeySlotCount; ++i) {
        const int code = static_cast<int>(map.codes[i]);
        if (code > 0 && code < SDL_SCANCODE_COUNT && keyboard[code]) {
            pressed |= static_cast<uint32_t>(kKeySlotButton[i]);
        }
    }
    return pressed;
}

}