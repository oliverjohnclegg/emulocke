#pragma once

#include "application/Prefs.hpp"

struct SDL_Window;
struct SDL_Renderer;

namespace emulocke {

class Host {
public:
    bool create(const Prefs& prefs);
    void destroy();
    SDL_Window* window() const { return window_; }
    SDL_Renderer* renderer() const { return renderer_; }
    void setFullscreen(bool on);
    bool fullscreen() const;
    void restoreDefaultSize();
    void adjustWidth(int delta);
    void setWindowSize(int w, int h);
    void captureWindowed(Prefs& prefs) const;
    void setTitle(const char* title);

private:
    SDL_Window* window_{};
    SDL_Renderer* renderer_{};
};

}