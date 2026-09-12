#include "application/Application.hpp"

#include <SDL3/SDL.h>
#include <cstdio>

int main(int argc, char** argv) {
    emulocke::Application app;
    if (!app.start(argc, argv)) {
        std::fprintf(stderr, "Emulocke failed to start: %s\n", SDL_GetError());
        return 1;
    }
    app.run();
    app.shutdown();
    return 0;
}
