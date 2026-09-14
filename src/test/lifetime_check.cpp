#include "application/Host.hpp"
#include "application/SdlRuntime.hpp"
#include "emu/AudioOutput.hpp"
#include "emu/ScreenTexture.hpp"
#include "test/Check.hpp"

#include <SDL3/SDL.h>
#include <cstdio>

namespace {

emulocke::Prefs windowedPrefs() {
    emulocke::Prefs prefs;
    prefs.windowW = 640;
    prefs.windowH = 480;
    return prefs;
}

void checkHostAndTexturesOutliveNothing() {
    emulocke::Host host;
    REQUIRE(host.create(windowedPrefs()));
    REQUIRE(host.window() != nullptr && host.renderer() != nullptr);
    emulocke::ScreenTexture screen;
    REQUIRE(screen.ensure(host.renderer(), 240, 160, SDL_PIXELFORMAT_ABGR8888));
    REQUIRE(screen.texture() != nullptr);
}

void checkRendererFailureReleasesWindow() {
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "no-such-render-driver");
    {
        emulocke::Host host;
        REQUIRE(!host.create(windowedPrefs()));
        REQUIRE(host.renderer() == nullptr);
    }
    SDL_ResetHint(SDL_HINT_RENDER_DRIVER);
}

void checkAudioOpenClose() {
    emulocke::AudioOutput audio;
    REQUIRE(audio.open());
    audio.setVolume(50);
    audio.setMuted(true);
    audio.setDropping(false);
    const int16_t silence[64]{};
    audio.push(silence, 16, 32768);
    REQUIRE(audio.queuedBytes() >= 0);
    audio.clear();
    audio.close();
}

}  // namespace

int main() {
    SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
    SDL_SetHint(SDL_HINT_AUDIO_DRIVER, "dummy");
    {
        emulocke::SdlRuntime sdl;
        REQUIRE(sdl.ok());
        REQUIRE(SDL_WasInit(SDL_INIT_VIDEO) != 0);
        checkHostAndTexturesOutliveNothing();
        checkRendererFailureReleasesWindow();
        checkAudioOpenClose();
        testLocalFilePaths();
    }
    REQUIRE(SDL_WasInit(SDL_INIT_VIDEO) == 0);
    std::printf("lifetime check ok\n");
    return 0;
}
