#pragma once

#include <cstdint>

struct SDL_Gamepad;

namespace emulocke {

class Input {
public:
    Input();
    ~Input();
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;
    void attach();
    uint32_t poll(const bool* keyboard) const;
    void handleAdded(int joystickIndex);
    void handleRemoved(int instanceId);

private:
    SDL_Gamepad* gamepad_{};
};

}