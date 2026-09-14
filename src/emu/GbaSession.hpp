#pragma once

#include "adapter/LiveMemory.hpp"
#include "emu/EmuSession.hpp"

#include <memory>
#include <mutex>
#include <optional>
#include <span>
#include <string>
#include <vector>

struct mCore;
struct mAudioBuffer;

namespace emulocke {

class GbaSession final : public EmuSession, public LiveMemory {
public:
    static std::unique_ptr<GbaSession> open(const std::string& romPath, const std::string& savePath);
    ~GbaSession() override;
    GbaSession(const GbaSession&) = delete;
    GbaSession& operator=(const GbaSession&) = delete;
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
    const LiveMemory* liveMemory() const override { return this; }
    std::optional<Cartridge> cartridge() const override { return cart_; }
    bool read(uint32_t addr, std::span<uint8_t> out) const override;
    bool write(uint32_t addr, std::span<const uint8_t> in);
    void flushSave();

private:
    GbaSession() = default;
    mCore* core_{};
    std::vector<uint32_t> pixels_;
    std::vector<uint32_t> display_;
    std::vector<int16_t> audioScratch_;
    unsigned width_{};
    unsigned height_{};
    std::string romName_;
    std::string savePath_;
    Cartridge cart_{};
    mutable std::mutex frameMutex_;
};

}