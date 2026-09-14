#include "emu/Buttons.hpp"
#include "emu/KeyMap.hpp"

#include <SDL3/SDL_scancode.h>
#include <cstdio>
#include <cstring>

int testInput() {
    int fails = 0;
    auto expect = [&](bool cond, const char* msg) {
        if (!cond) {
            std::fprintf(stderr, "FAIL %s\n", msg);
            ++fails;
        }
    };

    const emulocke::KeyMap map{};
    expect(map.codes[static_cast<int>(emulocke::KeySlot::B)] == SDL_SCANCODE_Z, "B is Z");
    expect(map.codes[static_cast<int>(emulocke::KeySlot::A)] == SDL_SCANCODE_X, "A is X");
    expect(map.codes[static_cast<int>(emulocke::KeySlot::Y)] == SDL_SCANCODE_A, "Y is A");
    expect(map.codes[static_cast<int>(emulocke::KeySlot::X)] == SDL_SCANCODE_S, "X is S");
    expect(map.codes[static_cast<int>(emulocke::KeySlot::L)] == SDL_SCANCODE_Q, "L is Q");
    expect(map.codes[static_cast<int>(emulocke::KeySlot::R)] == SDL_SCANCODE_W, "R is W");
    expect(map.codes[static_cast<int>(emulocke::KeySlot::Start)] == SDL_SCANCODE_RETURN, "Start is Enter");
    expect(map.codes[static_cast<int>(emulocke::KeySlot::Select)] == SDL_SCANCODE_RSHIFT, "Select is RShift");
    expect(map.codes[static_cast<int>(emulocke::KeySlot::Up)] == SDL_SCANCODE_UP, "D-pad Up");

    bool keys[SDL_SCANCODE_COUNT]{};
    auto press = [&](SDL_Scancode code, emulocke::Button button, const char* msg) {
        std::memset(keys, 0, sizeof(keys));
        keys[code] = true;
        const uint32_t pressed = emulocke::keyboardButtons(keys, map);
        expect(pressed == static_cast<uint32_t>(button), msg);
    };
    press(SDL_SCANCODE_X, emulocke::Button::A, "X presses A");
    press(SDL_SCANCODE_Z, emulocke::Button::B, "Z presses B");
    press(SDL_SCANCODE_A, emulocke::Button::Y, "A presses Y not L");
    press(SDL_SCANCODE_S, emulocke::Button::X, "S presses X");
    press(SDL_SCANCODE_Q, emulocke::Button::L, "Q presses L");
    press(SDL_SCANCODE_W, emulocke::Button::R, "W presses R");
    press(SDL_SCANCODE_RETURN, emulocke::Button::Start, "Enter presses Start");
    press(SDL_SCANCODE_RSHIFT, emulocke::Button::Select, "RShift presses Select");
    press(SDL_SCANCODE_UP, emulocke::Button::Up, "Up presses D-pad");
    std::memset(keys, 0, sizeof(keys));
    keys[SDL_SCANCODE_LSHIFT] = true;
    expect(emulocke::keyboardButtons(keys, map) == 0, "LShift is not Select");

    emulocke::KeyMap swapped = map;
    expect(emulocke::bindKey(swapped, static_cast<int>(emulocke::KeySlot::A), SDL_SCANCODE_Z), "bind A to Z");
    expect(swapped.codes[static_cast<int>(emulocke::KeySlot::A)] == SDL_SCANCODE_Z, "A stole Z");
    expect(swapped.codes[static_cast<int>(emulocke::KeySlot::B)] == SDL_SCANCODE_X, "B took A's old key");
    expect(!emulocke::bindKey(swapped, static_cast<int>(emulocke::KeySlot::B), SDL_SCANCODE_TAB), "Tab stays host");
    expect(swapped.codes[static_cast<int>(emulocke::KeySlot::B)] == SDL_SCANCODE_X, "Tab leaves B");
    expect(emulocke::parseScancode("RShift") == SDL_SCANCODE_RSHIFT, "parse RShift");
    expect(emulocke::parseScancode("Enter") == SDL_SCANCODE_RETURN, "parse Enter");
    expect(std::strcmp(emulocke::scancodeLabel(SDL_SCANCODE_RSHIFT), "RShift") == 0, "label RShift");
    expect(emulocke::keySlotFromId("select") == static_cast<int>(emulocke::KeySlot::Select), "slot id");
    return fails;
}