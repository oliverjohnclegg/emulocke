#pragma once

#include "application/Prefs.hpp"

#include <memory>

struct SDL_Window;
struct SDL_Renderer;

namespace emulocke {

struct SdlWindowDeleter {
    void operator()(SDL_Window* window) const;
};

struct SdlRendererDeleter {
    void operator()(SDL_Renderer* renderer) const;
};

class Host {
public:
    Host() = default;
    ~Host();
    Host(const Host&) = delete;
    Host& operator=(const Host&) = delete;
    bool create(const Prefs& prefs);
    void destroy();
    SDL_Window* window() const { return window_.get(); }
    SDL_Renderer* renderer() const { return renderer_.get(); }
    void setFullscreen(bool on);
    bool fullscreen() const;
    void restoreDefaultSize();
    void adjustWidth(int delta);
    void setWindowSize(int w, int h);
    void sizeToContent(int logicalW, int logicalH);
    void contentWindowSize(int logicalW, int logicalH, int& w, int& h) const;
    void captureWindowed(Prefs& prefs) const;
    void setTitle(const char* title);

private:
    std::unique_ptr<SDL_Window, SdlWindowDeleter> window_;
    std::unique_ptr<SDL_Renderer, SdlRendererDeleter> renderer_;
    bool imguiReady_{false};
};

}
