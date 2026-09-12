#pragma once

#include <cstddef>
#include <cstdint>

struct SDL_AudioStream;

namespace emulocke {

class AudioOutput {
public:
    AudioOutput();
    ~AudioOutput();
    AudioOutput(const AudioOutput&) = delete;
    AudioOutput& operator=(const AudioOutput&) = delete;
    bool open();
    void close();
    void push(const int16_t* interleavedStereo, int frames, int sourceHz);
    int queuedBytes() const;

private:
    SDL_AudioStream* stream_{};
    int sourceHz_{48000};
};

}