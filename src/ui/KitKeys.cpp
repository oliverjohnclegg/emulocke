#include "ui/KitKeys.hpp"

#include <SDL3/SDL.h>

namespace emulocke {
namespace {

struct Repeat {
    bool held{};
    uint32_t start{};
    uint32_t last{};
};

bool pulse(bool down, Repeat& st, uint32_t now) {
    if (!down) {
        st = {};
        return false;
    }
    if (!st.held) {
        st.held = true;
        st.start = now;
        st.last = now;
        return true;
    }
    if (now - st.start < 350) {
        return false;
    }
    if (now - st.last < 50) {
        return false;
    }
    st.last = now;
    return true;
}

bool was[SDL_SCANCODE_COUNT]{};
Repeat left{};
Repeat right{};
Repeat up{};
Repeat down{};

bool edge(const bool* keys, SDL_Scancode code) {
    return keys[code] && !was[code];
}

void remember(const bool* keys, SDL_Scancode code) {
    was[code] = keys[code];
}

const SDL_Scancode kCodes[] = {
    SDL_SCANCODE_ESCAPE,
    SDL_SCANCODE_GRAVE,
    SDL_SCANCODE_1,
    SDL_SCANCODE_2,
    SDL_SCANCODE_3,
    SDL_SCANCODE_4,
    SDL_SCANCODE_5,
    SDL_SCANCODE_E,
    SDL_SCANCODE_R,
    SDL_SCANCODE_T,
    SDL_SCANCODE_D,
    SDL_SCANCODE_F,
    SDL_SCANCODE_G,
    SDL_SCANCODE_V,
    SDL_SCANCODE_BACKSPACE,
};

}  // namespace

KitFrame pollKit(const bool* keys, bool textInput, bool blocked) {
    KitFrame out{};
    if (!keys) {
        return out;
    }
    const uint32_t now = SDL_GetTicks();
    if (!blocked) {
        out.pause = edge(keys, SDL_SCANCODE_ESCAPE);
        if (!textInput) {
            out.act = edge(keys, SDL_SCANCODE_F);
            out.snap = edge(keys, SDL_SCANCODE_E);
            out.search = edge(keys, SDL_SCANCODE_T);
            out.pane = edge(keys, SDL_SCANCODE_GRAVE);
            out.backspace = edge(keys, SDL_SCANCODE_BACKSPACE);
            out.left = pulse(keys[SDL_SCANCODE_D], left, now);
            out.right = pulse(keys[SDL_SCANCODE_G], right, now);
            out.up = pulse(keys[SDL_SCANCODE_R], up, now);
            out.down = pulse(keys[SDL_SCANCODE_V], down, now);
            for (int i = 0; i < 5; ++i) {
                if (edge(keys, static_cast<SDL_Scancode>(SDL_SCANCODE_1 + i))) {
                    out.tab = i + 1;
                }
            }
        }
    }
    if (textInput || blocked) {
        left = {};
        right = {};
        up = {};
        down = {};
    }
    for (SDL_Scancode code : kCodes) {
        remember(keys, code);
    }
    return out;
}

}
