#pragma once

#include "emu/Buttons.hpp"

#include <cstdint>
#include <string>

namespace emulocke {

class AudioOutput;

class EmuSession {
public:
    virtual ~EmuSession() = default;
    virtual ConsoleKind kind() const = 0;
    virtual int screenCount() const = 0;
    virtual int screenWidth(int index) const = 0;
    virtual int screenHeight(int index) const = 0;
    virtual void copyScreen(int index, void* dest, int pitchBytes) const = 0;
    virtual void runFrame() = 0;
    virtual void reset() = 0;
    virtual void setButtons(uint32_t pressed) = 0;
    virtual void setTouch(bool down, uint16_t x, uint16_t y) = 0;
    virtual void drainAudio(AudioOutput& audio) = 0;
    virtual const std::string& romName() const = 0;
};

}