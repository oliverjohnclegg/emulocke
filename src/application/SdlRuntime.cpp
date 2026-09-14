#include "application/SdlRuntime.hpp"

#include <SDL3/SDL.h>

namespace emulocke {

SdlRuntime::SdlRuntime() : ok_(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD)) {
    if (ok_) {
        SDL_InitSubSystem(SDL_INIT_AUDIO);
    }
}

SdlRuntime::~SdlRuntime() {
    SDL_Quit();
}

}
