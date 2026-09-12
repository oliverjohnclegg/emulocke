#pragma once

struct SDL_Window;
struct SDL_Renderer;

namespace emulocke {

class Host {
public:
    bool create();
    void destroy();
    SDL_Window* window() const { return window_; }
    SDL_Renderer* renderer() const { return renderer_; }

private:
    SDL_Window* window_{};
    SDL_Renderer* renderer_{};
};

}
