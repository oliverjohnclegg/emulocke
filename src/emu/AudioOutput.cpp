#include "emu/AudioOutput.hpp"

#include <SDL3/SDL.h>

namespace emulocke {

AudioOutput::AudioOutput() = default;

AudioOutput::~AudioOutput() {
    close();
}

bool AudioOutput::open() {
    SDL_AudioSpec spec;
    spec.format = SDL_AUDIO_S16;
    spec.channels = 2;
    spec.freq = 48000;
    stream_ = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr);
    if (!stream_) {
        return false;
    }
    SDL_ResumeAudioStreamDevice(stream_);
    return true;
}

void AudioOutput::close() {
    if (stream_) {
        SDL_DestroyAudioStream(stream_);
        stream_ = nullptr;
    }
}

void AudioOutput::push(const int16_t* interleavedStereo, int frames, int sourceHz) {
    if (!stream_ || frames <= 0) {
        return;
    }
    if (sourceHz != sourceHz_) {
        SDL_AudioSpec in;
        in.format = SDL_AUDIO_S16;
        in.channels = 2;
        in.freq = sourceHz;
        SDL_SetAudioStreamFormat(stream_, &in, nullptr);
        sourceHz_ = sourceHz;
    }
    SDL_PutAudioStreamData(stream_, interleavedStereo, frames * 4);
}

int AudioOutput::queuedBytes() const {
    if (!stream_) {
        return 0;
    }
    const int queued = SDL_GetAudioStreamQueued(stream_);
    return queued > 0 ? queued : 0;
}

}