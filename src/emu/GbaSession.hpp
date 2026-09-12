#pragma once

#include "emu/EmuSession.hpp"

#include <memory>
#include <mutex>
#include <string>
#include <vector>

struct mCore;
struct mAudioBuffer;

namespace emulocke {

class GbaSession final : public EmuSession {
public:
    static std::unique_ptr<GbaSession> open(const std::string& romPath);
    ~GbaSession() override;
    ConsoleKind kind() const override { return ConsoleKind::Gba; }
    int screenCount() const override { return 1; }
    int screenWidth(int) const override { return static_cast<int>(width_); }
    int screenHeight(int) const override { return static_cast<int>(height_); }
    void copyScreen(int index, void* dest, int pitchBytes) const override;
    void runFrame() override;
    void reset() override;
    void setButtons(uint32_t pressed) override;
    void setTouch(bool, uint16_t, uint16_t) override {}
    void drainAudio(AudioOutput& audio) override;
    const std::string& romName() const override { return romName_; }
    void flushSave();

private:
    GbaSession() = default;
    mCore* core_{};
    std::vector<uint32_t> pixels_;
    unsigned width_{};
    unsigned height_{};
    std::string romName_;
    std::string savePath_;
    mutable std::mutex frameMutex_;
};

}