#pragma once

#include "emu/Buttons.hpp"

#include <SDL3/SDL_scancode.h>
#include <cstdint>
#include <string>

namespace emulocke {

inline constexpr int kKeySlotCount = 12;

enum class KeySlot : int {
    Up = 0,
    Down,
    Left,
    Right,
    B,
    A,
    Y,
    X,
    L,
    R,
    Start,
    Select,
};

struct KeyMap {
    SDL_Scancode codes[kKeySlotCount] = {
        SDL_SCANCODE_UP,
        SDL_SCANCODE_DOWN,
        SDL_SCANCODE_LEFT,
        SDL_SCANCODE_RIGHT,
        SDL_SCANCODE_Z,
        SDL_SCANCODE_X,
        SDL_SCANCODE_A,
        SDL_SCANCODE_S,
        SDL_SCANCODE_Q,
        SDL_SCANCODE_W,
        SDL_SCANCODE_RETURN,
        SDL_SCANCODE_RSHIFT,
    };
};

inline constexpr Button kKeySlotButton[kKeySlotCount] = {
    Button::Up,
    Button::Down,
    Button::Left,
    Button::Right,
    Button::B,
    Button::A,
    Button::Y,
    Button::X,
    Button::L,
    Button::R,
    Button::Start,
    Button::Select,
};

const char* keySlotId(int slot);
const char* keySlotLabel(int slot);
const char* scancodeLabel(SDL_Scancode code);
int keySlotFromId(const std::string& id);
SDL_Scancode parseScancode(const std::string& value);
bool reservedScancode(SDL_Scancode code);
bool bindKey(KeyMap& map, int slot, SDL_Scancode code);
uint32_t keyboardButtons(const bool* keyboard, const KeyMap& map);

}