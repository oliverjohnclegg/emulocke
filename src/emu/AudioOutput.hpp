#pragma once

#include <atomic>
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
    void setMuted(bool mute);
    void setVolume(int volume);
    void setDropping(bool drop);
    void clear();
    int queuedBytes() const;

private:
    void applyGain();
    SDL_AudioStream* stream_{};
    int sourceHz_{48000};
    std::atomic<bool> muted_{false};
    std::atomic<int> volume_{100};
    std::atomic<bool> dropping_{false};
};

}
