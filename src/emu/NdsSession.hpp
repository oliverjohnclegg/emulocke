#pragma once

#include "emu/EmuSession.hpp"

#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace melonDS {
class NDS;
}

namespace emulocke {

class NdsSession final : public EmuSession {
public:
    static std::unique_ptr<NdsSession> open(const std::string& romPath);
    ~NdsSession() override;
    ConsoleKind kind() const override { return ConsoleKind::Nds; }
    int screenCount() const override { return 2; }
    int screenWidth(int) const override { return 256; }
    int screenHeight(int) const override { return 192; }
    void copyScreen(int index, void* dest, int pitchBytes) const override;
    void runFrame() override;
    void reset() override;
    void setButtons(uint32_t pressed) override;
    void setTouch(bool down, uint16_t x, uint16_t y) override;
    void drainAudio(AudioOutput& audio) override;
    const std::string& romName() const override { return romName_; }
    void writeSave(const uint8_t* data, uint32_t length);

private:
    NdsSession() = default;
    std::unique_ptr<melonDS::NDS> nds_;
    std::string romPath_;
    std::string savePath_;
    std::string romName_;
    std::vector<uint32_t> top_;
    std::vector<uint32_t> bottom_;
    mutable std::mutex frameMutex_;
};

}