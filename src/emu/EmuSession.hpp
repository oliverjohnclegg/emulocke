#pragma once

#include "adapter/Cartridge.hpp"
#include "adapter/LiveMemory.hpp"
#include "emu/Buttons.hpp"

#include <cstdint>
#include <optional>
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
    virtual const LiveMemory* liveMemory() const { return nullptr; }
    virtual std::optional<Cartridge> cartridge() const { return std::nullopt; }
};

}