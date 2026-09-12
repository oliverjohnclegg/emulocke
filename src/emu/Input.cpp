#include "emu/Input.hpp"

#include "emu/Buttons.hpp"

#include <SDL3/SDL.h>

namespace emulocke {

Input::Input() = default;

void Input::attach() {
    if (gamepad_) {
        return;
    }
    int count = 0;
    SDL_JoystickID* ids = SDL_GetGamepads(&count);
    if (ids && count > 0) {
        gamepad_ = SDL_OpenGamepad(ids[0]);
    }
    SDL_free(ids);
}

Input::~Input() {
    if (gamepad_) {
        SDL_CloseGamepad(gamepad_);
    }
}

void Input::handleAdded(int joystickIndex) {
    if (!gamepad_) {
        gamepad_ = SDL_OpenGamepad(joystickIndex);
    }
}

void Input::handleRemoved(int instanceId) {
    if (gamepad_ && SDL_GetGamepadID(gamepad_) == static_cast<SDL_JoystickID>(instanceId)) {
        SDL_CloseGamepad(gamepad_);
        gamepad_ = nullptr;
    }
}

uint32_t Input::poll(const bool* keyboard) const {
    uint32_t pressed = 0;
    if (keyboard) {
        if (keyboard[SDL_SCANCODE_X]) pressed |= static_cast<uint32_t>(Button::A);
        if (keyboard[SDL_SCANCODE_Z]) pressed |= static_cast<uint32_t>(Button::B);
        if (keyboard[SDL_SCANCODE_RSHIFT] || keyboard[SDL_SCANCODE_LSHIFT]) {
            pressed |= static_cast<uint32_t>(Button::Select);
        }
        if (keyboard[SDL_SCANCODE_RETURN]) pressed |= static_cast<uint32_t>(Button::Start);
        if (keyboard[SDL_SCANCODE_RIGHT]) pressed |= static_cast<uint32_t>(Button::Right);
        if (keyboard[SDL_SCANCODE_LEFT]) pressed |= static_cast<uint32_t>(Button::Left);
        if (keyboard[SDL_SCANCODE_UP]) pressed |= static_cast<uint32_t>(Button::Up);
        if (keyboard[SDL_SCANCODE_DOWN]) pressed |= static_cast<uint32_t>(Button::Down);
        if (keyboard[SDL_SCANCODE_S]) pressed |= static_cast<uint32_t>(Button::R);
        if (keyboard[SDL_SCANCODE_A]) pressed |= static_cast<uint32_t>(Button::L);
    }
    if (gamepad_) {
        if (SDL_GetGamepadButton(gamepad_, SDL_GAMEPAD_BUTTON_EAST)) pressed |= static_cast<uint32_t>(Button::A);
        if (SDL_GetGamepadButton(gamepad_, SDL_GAMEPAD_BUTTON_SOUTH)) pressed |= static_cast<uint32_t>(Button::B);
        if (SDL_GetGamepadButton(gamepad_, SDL_GAMEPAD_BUTTON_BACK)) pressed |= static_cast<uint32_t>(Button::Select);
        if (SDL_GetGamepadButton(gamepad_, SDL_GAMEPAD_BUTTON_START)) pressed |= static_cast<uint32_t>(Button::Start);
        if (SDL_GetGamepadButton(gamepad_, SDL_GAMEPAD_BUTTON_DPAD_RIGHT)) pressed |= static_cast<uint32_t>(Button::Right);
        if (SDL_GetGamepadButton(gamepad_, SDL_GAMEPAD_BUTTON_DPAD_LEFT)) pressed |= static_cast<uint32_t>(Button::Left);
        if (SDL_GetGamepadButton(gamepad_, SDL_GAMEPAD_BUTTON_DPAD_UP)) pressed |= static_cast<uint32_t>(Button::Up);
        if (SDL_GetGamepadButton(gamepad_, SDL_GAMEPAD_BUTTON_DPAD_DOWN)) pressed |= static_cast<uint32_t>(Button::Down);
        if (SDL_GetGamepadButton(gamepad_, SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER)) pressed |= static_cast<uint32_t>(Button::R);
        if (SDL_GetGamepadButton(gamepad_, SDL_GAMEPAD_BUTTON_LEFT_SHOULDER)) pressed |= static_cast<uint32_t>(Button::L);
        if (SDL_GetGamepadButton(gamepad_, SDL_GAMEPAD_BUTTON_NORTH)) pressed |= static_cast<uint32_t>(Button::X);
        if (SDL_GetGamepadButton(gamepad_, SDL_GAMEPAD_BUTTON_WEST)) pressed |= static_cast<uint32_t>(Button::Y);
    }
    return pressed;
}

}