#include "emu/AudioOutput.hpp"

#include <SDL3/SDL.h>
#include <algorithm>

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
    applyGain();
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

void AudioOutput::setMuted(bool mute) {
    muted_ = mute;
    applyGain();
}

void AudioOutput::setVolume(int volume) {
    volume_ = std::clamp(volume, 0, 100);
    applyGain();
}

void AudioOutput::applyGain() {
    if (!stream_) {
        return;
    }
    SDL_SetAudioStreamGain(stream_, muted_ ? 0.f : volume_ * 0.01f);
}

}
